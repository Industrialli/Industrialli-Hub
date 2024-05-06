#include "modbus/industrialli_modbus_rtu_client.h"
#include <HardwareSerial.h>
#include <Arduino.h>

void IndustrialliModbusRTUClient::create_register(uint16_t address, uint16_t value){
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

void IndustrialliModbusRTUClient::set_register(uint16_t _address, uint16_t _value){
    Register *reg = search_register(_address);
    reg->value = _value;
}

uint16_t IndustrialliModbusRTUClient::get_register(uint16_t _address){
    Register *reg = search_register(_address);
    return reg->value;
}

Register* IndustrialliModbusRTUClient::search_register(uint16_t address){
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

void IndustrialliModbusRTUClient::process_response_read_coils(){

}

void IndustrialliModbusRTUClient::process_response_read_input_coils(){

}

void IndustrialliModbusRTUClient::process_response_read_holding_register(){

}

void IndustrialliModbusRTUClient::process_response_read_input_register(){

}

void IndustrialliModbusRTUClient::process_response_write_single_coil(){

}

void IndustrialliModbusRTUClient::process_response_write_single_register(){

}

void IndustrialliModbusRTUClient::process_response_write_multiple_coils(){

}

void IndustrialliModbusRTUClient::process_response_write_multiple_registers(){
    
}

void IndustrialliModbusRTUClient::read_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
    frame[0] = _address;
    frame[1] = FC_READ_COILS;
    frame[2] = _starting_address >> 8;
    frame[3] = _starting_address & 0xFF;
    frame[4] = _quantity_of_coils >> 8;
    frame[5] = _quantity_of_coils & 0xFF;

    uint16_t frame_crc = crc(_address, &frame[1], 5);

    frame[6] = frame_crc >> 8;
    frame[7] = frame_crc & 0xFF;

    frame_size = 8;

    send_request();

    if(receive_response()){
        process_response();
    }
}

void IndustrialliModbusRTUClient::read_input_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
    frame[0] = _address;
    frame[1] = FC_READ_INPUT_COILS;
    frame[2] = _starting_address >> 8;
    frame[3] = _starting_address & 0xFF;
    frame[4] = _quantity_of_coils >> 8;
    frame[5] = _quantity_of_coils & 0xFF;

    uint16_t frame_crc = crc(_address, &frame[1], 5);

    frame[6] = frame_crc >> 8;
    frame[7] = frame_crc & 0xFF;

    frame_size = 8;

    send_request();
    
    if(receive_response()){
        process_response();
    }
}

void IndustrialliModbusRTUClient::read_holding_register(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
    frame[0] = _address;
    frame[1] = FC_READ_HOLDING_REGISTERS;
    frame[2] = _starting_address >> 8;
    frame[3] = _starting_address & 0xFF;
    frame[4] = _quantity_of_coils >> 8;
    frame[5] = _quantity_of_coils & 0xFF;

    uint16_t frame_crc = crc(_address, &frame[1], 5);

    frame[6] = frame_crc >> 8;
    frame[7] = frame_crc & 0xFF;

    frame_size = 8;

    send_request();
    
    if(receive_response()){
        process_response();
    }
}

void IndustrialliModbusRTUClient::read_input_register(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
    frame[0] = _address;
    frame[1] = FC_READ_INPUT_REGISTERS;
    frame[2] = _starting_address >> 8;
    frame[3] = _starting_address & 0xFF;
    frame[4] = _quantity_of_coils >> 8;
    frame[5] = _quantity_of_coils & 0xFF;

    uint16_t frame_crc = crc(_address, &frame[1], 5);

    frame[6] = frame_crc >> 8;
    frame[7] = frame_crc & 0xFF;

    frame_size = 8;

    send_request();
    
    if(receive_response()){
        process_response();
    }
}

void IndustrialliModbusRTUClient::write_single_coil(uint8_t _address, uint16_t _coil_address, uint16_t _value){
    frame[0] = _address;
    frame[1] = FC_WRITE_SINGLE_COIL;
    frame[2] = _coil_address >> 8;
    frame[3] = _coil_address & 0xFF;
    frame[4] = _value >> 8;
    frame[5] = _value & 0xFF;

    uint16_t frame_crc = crc(_address, &frame[1], 5);

    frame[6] = frame_crc >> 8;
    frame[7] = frame_crc & 0xFF;

    frame_size = 8;

    send_request();
    
    if(receive_response()){
        process_response();
    }
}

void IndustrialliModbusRTUClient::write_single_register(uint8_t _address, uint16_t _register_address, uint16_t _value){
    frame[0] = _address;
    frame[1] = FC_WRITE_SINGLE_REGISTER;
    frame[2] = _register_address >> 8;
    frame[3] = _register_address & 0xFF;
    frame[4] = _value >> 8;
    frame[5] = _value & 0xFF;

    uint16_t frame_crc = crc(_address, &frame[1], 5);

    frame[6] = frame_crc >> 8;
    frame[7] = frame_crc & 0xFF;

    frame_size = 8;

    send_request();
    
    if(receive_response()){
        process_response();
    }
}

void IndustrialliModbusRTUClient::write_multiple_coils(uint8_t _address, uint16_t _starting_address, uint16_t* _values, uint16_t _quantity_of_coils){
    frame[0] = _address;
    frame[1] = FC_WRITE_MULTIPLE_COILS;
    frame[2] = _starting_address >> 8;
    frame[3] = _starting_address & 0xFF;
    frame[4] = _quantity_of_coils >> 8;
    frame[5] = _quantity_of_coils & 0xFF;
    frame[6] = ceil(_quantity_of_coils / 8.0);

    for (uint16_t i = 0; i < _quantity_of_coils; i++) {
        bitWrite(frame[7 + (i >> 3)], i & 7, _values[i]);
    }

    for (uint16_t i = _quantity_of_coils; i < (frame[6] * 8); i++) {
        bitClear(frame[7 + (i >> 3)], i & 7);
    }

    uint16_t frame_crc = crc(_address, &frame[1], 6 + frame[6]);

    frame[7 + frame[6]] = frame_crc >> 8;
    frame[8 + frame[6]] = frame_crc & 0xFF;

    frame_size = 9 + frame[6];

    send_request();
    
    if(receive_response()){
        process_response();
    }
}

void IndustrialliModbusRTUClient::write_multiple_registers(uint8_t _address, uint16_t _starting_address, uint16_t* _values, uint16_t _quantity_of_registers){
    frame[0] = _address;
    frame[1] = FC_WRITE_MULTIPLE_REGISTERS;
    frame[2] = _starting_address >> 8;
    frame[3] = _starting_address & 0xFF;
    frame[4] = _quantity_of_registers >> 8;
    frame[5] = _quantity_of_registers & 0xFF;
    frame[6] = _quantity_of_registers * 2;

    for (int i = 0; i < _quantity_of_registers; i++){
        frame[7 + (2 * i)] = _values[i] >> 8;
        frame[8 + (2 * i)] = _values[i] & 0xFF;
    }
    
    uint16_t frame_crc = crc(_address, &frame[1], 6 + frame[6]);

    frame[7 + frame[6]] = frame_crc >> 8;
    frame[8 + frame[6]] = frame_crc & 0xFF;

    frame_size = 9 + frame[6];

    send_request();
    
    if(receive_response()){
        process_response();
    }
}

uint16_t IndustrialliModbusRTUClient::crc(uint8_t _address, uint8_t *_pdu, int _pdu_size){
    uint8_t uchCRCHi = 0xFF;
    uint8_t uchCRCLo = 0xFF;
    uint8_t uIndex;

    uIndex   = uchCRCLo ^ _address;
    uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex];
    uchCRCHi = auchCRCLo[uIndex];
    
    while(_pdu_size--){
        uIndex   = uchCRCLo ^ *_pdu++;
        uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex];
        uchCRCHi = auchCRCLo[uIndex];
    }

    return (uchCRCHi << 8 | uchCRCLo);
}

void IndustrialliModbusRTUClient::begin(HardwareSerial *_serial){
    serial = _serial;
    registers_head = NULL;
    registers_last = NULL;

    t15 = 16500000/9600; 
    t35 = t15 * 2;
}

void IndustrialliModbusRTUClient::send_request(){
    serial->write(frame, frame_size);
    serial->flush();

    delayMicroseconds(t35);
}

bool IndustrialliModbusRTUClient::receive_response(){
    frame_size = 0;

    if(serial->available()){
        while (serial->available()){
            frame[frame_size++] = serial->read();
            delayMicroseconds(t15);
        }

        uint16_t crc_frame = (frame[frame_size - 2] << 8) | (frame[frame_size - 1]);

        if(crc_frame == crc(frame[0], &frame[1], frame_size - 3)){
            return true;
        }
    }

    return false;
}

void IndustrialliModbusRTUClient::process_response(){
    uint8_t _address = frame[0];
    uint8_t function = frame[1];
    uint16_t field_1 = (frame[2] << 8) | frame[3];
    uint16_t field_2 = (frame[4] << 8) | frame[5];
   
    switch (function){
        case FC_READ_COILS:
            process_response_read_coils();
            break;

        case FC_READ_INPUT_COILS:
            process_response_read_input_coils();
            break;

        case FC_READ_HOLDING_REGISTERS:
            process_response_read_holding_register();
            break;

        case FC_READ_INPUT_REGISTERS:
            process_response_read_input_register();
            break;

        case FC_WRITE_SINGLE_COIL:
            process_response_write_single_coil();
            break;

        case FC_WRITE_SINGLE_REGISTER:
            process_response_write_single_register();
            break;

        case FC_WRITE_MULTIPLE_COILS:
            process_response_write_multiple_coils();
            break;

        case FC_WRITE_MULTIPLE_REGISTERS:
            process_response_write_multiple_registers();
            break;
            
        default:
            break;
    }
}

void IndustrialliModbusRTUClient::create_status_coil(uint16_t _address, bool _value){
    create_register(_address + 1, _value);
}

void IndustrialliModbusRTUClient::create_input_coil(uint16_t _address, bool _value){
    create_register(_address + 10001, _value);
}

void IndustrialliModbusRTUClient::create_input_register(uint16_t _address, uint16_t _value){
    create_register(_address + 30001, _value);
}

void IndustrialliModbusRTUClient::create_holding_register(uint16_t _address, uint16_t _value){
    create_register(_address + 40001, _value);
}

void IndustrialliModbusRTUClient::set_status_coil(uint16_t _address, bool _value){
    set_register(_address + 1, _value);
}

void IndustrialliModbusRTUClient::set_input_coil(uint16_t _address, bool _value){
    set_register(_address + 10001, _value);
}

void IndustrialliModbusRTUClient::set_input_register(uint16_t _address, uint16_t _value){
    set_register(_address + 30001, _value);
}

void IndustrialliModbusRTUClient::set_holding_register(uint16_t _address, uint16_t _value){
    set_register(_address + 40001, _value);
}

bool IndustrialliModbusRTUClient::get_status_coil(uint16_t _address){
    return get_register(_address + 1);
}

bool IndustrialliModbusRTUClient::get_input_coil(uint16_t _address){
    return get_register(_address + 10001);
}

uint16_t IndustrialliModbusRTUClient::get_input_register(uint16_t _address){
    return get_register(_address + 30001);
}

uint16_t IndustrialliModbusRTUClient::get_holding_register(uint16_t _address){
    return get_register(_address + 40001);
}