#include "industrialli_modbus_rtu.h"
#include <HardwareSerial.h>
#include <Arduino.h>

void IndustrialliModbusRTU::begin(HardwareSerial *_serial){
    serial = _serial;
    registers_head = NULL;
    registers_last = NULL;

    t15    = 15000000/9600; 
    t35    = 35000000/9600;
}

void IndustrialliModbusRTU::set_slave_id(uint8_t _address){
    address = _address;
}

void IndustrialliModbusRTU::create_register(uint16_t address, uint16_t value){
    Register *new_register;

	new_register = (Register *) malloc(sizeof(Register));
	new_register->address = address;
	new_register->value	  = value;
	new_register->next	  = NULL;

	if(registers_head == NULL) {
        registers_head = new_register;
        registers_last = registers_head;
    } else {
        registers_last->next = new_register;
        registers_last = new_register;
    }
}

Register* IndustrialliModbusRTU::search_register(uint16_t address){
    Register *registers = registers_head;

    if(registers == NULL){
        return NULL;
    }
    
    do {
        if (registers->address == address){
            return(registers);
        }
        
        registers = registers->next;
	} while(registers != NULL);
	
    return NULL;
}

void IndustrialliModbusRTU::send(uint8_t _address, uint8_t *_pdu, int _pdusize){
    serial->write(_address);

    for (int i = 0; i < _pdusize; i++){
        serial->write(_pdu[i]);
    }

    uint16_t crc_value = crc(_address, _pdu, _pdusize);

    serial->write(crc_value >> 8);
    serial->write(crc_value & 0xFF);

    delay(t35);

    serial->flush();
}

uint8_t* IndustrialliModbusRTU::receive(){
    frame = (uint8_t *)malloc(framesize);
    
    for (int i = 0; i < framesize; i++){
        frame[i] = serial->read();
    }

    uint16_t crc_frame = (frame[framesize - 2] << 8) | (frame[framesize - 1]);

    if(crc_frame == crc(frame[0], &frame[1], framesize - 2)){
        return frame;
    }
}

//essa função recebe um frame e cria outro como resposta XD
uint8_t* process_frame(uint8_t *_frame){
    uint8_t address  = _frame[0];
    uint8_t function = _frame[1];
    uint16_t field_1 = (_frame[2] << 8) | _frame[3];
    uint16_t field_2 = (_frame[3] << 8) | _frame[4];
   
    switch (function){
        case FC_READ_COILS:
            // read_coils(field_1, field_2);

            break;
        case FC_READ_DISCRETE_INPUTS:
            break;
        case FC_READ_HOLDING_REGISTERS:
            break;
        case FC_READ_INPUT_REGISTERS:
            break;
        case FC_WRITE_SINGLE_COIL:
            break;
        case FC_WRITE_SINGLE_REGISTER:
            break;
        case FC_WRITE_MULTIPLE_COILS:
            break;
        case FC_WRITE_MULTIPLE_REGISTERS:
            break;
        
        default:
            break;
    }

    
}

void IndustrialliModbusRTU::task(){
    frame = receive();
    frame = process_frame(frame);
    send(frame[0], &frame[1], framesize - 2);
}

uint16_t IndustrialliModbusRTU::crc(uint8_t address, uint8_t *pdu, int pdusize){
    uint8_t uchCRCHi = 0xFF;
    uint8_t uchCRCLo = 0xFF;
    uint8_t uIndex;

    uIndex   = uchCRCLo ^ address;
    uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex];
    uchCRCHi = auchCRCLo[uIndex];
    
    while(pdusize--){
        uIndex   = uchCRCLo ^ *pdu++;
        uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex];
        uchCRCHi = auchCRCLo[uIndex];
    }

    return (uchCRCHi << 8 | uchCRCLo);
}

void IndustrialliModbusRTU::clear_frame(){
    free(frame);
    framesize = 0;
}