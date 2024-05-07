#include "modbus/industrialli_modbus_rtu_client.h"
#include <HardwareSerial.h>
#include <Arduino.h>

void Industrialli_Modbus_RTU_Client::process_response_read_coils(uint16_t _start_address, uint16_t _n_coils){
    for(int reg = _n_coils - 1, bitpos = 0; reg >= 0; reg--, _start_address++, bitpos++){
        if(bitpos == 8) bitpos = 0;
        set_status_coil(_start_address, bitRead(frame[(3 + (_n_coils-reg)/8)], bitpos));
    }
}

void Industrialli_Modbus_RTU_Client::process_response_read_input_coils(uint16_t _start_address, uint16_t _n_coils){
    for(int reg = _n_coils - 1, bitpos = 0; reg >= 0; reg--, _start_address++, bitpos++){
        if(bitpos == 8) bitpos = 0;
        set_input_coil(_start_address, bitRead(frame[(3 + (_n_coils-reg)/8)], bitpos));
    }
}

void Industrialli_Modbus_RTU_Client::process_response_read_holding_register(uint16_t _start_address, uint16_t _n_of_registers){
    for (uint16_t address = 3, index = 0; index < _n_of_registers; address += 2, index++){
        set_holding_register(_start_address + index, (frame[address] << 8) | frame[address + 1]);
    }
}

void Industrialli_Modbus_RTU_Client::process_response_read_input_register(uint16_t _start_address, uint16_t _n_of_registers){
for (uint16_t address = 3, index = 0; index < _n_of_registers; address += 2, index++){
        set_input_register(_start_address + index, (frame[address] << 8) | frame[address + 1]);
    }
}

uint16_t Industrialli_Modbus_RTU_Client::crc(uint8_t _address, uint8_t *_pdu, int _pdu_size){
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

void Industrialli_Modbus_RTU_Client::begin(HardwareSerial *_serial){
    serial = _serial;
    registers_head = NULL;
    registers_last = NULL;

    t15 = 16500000/9600; 
    t35 = t15 * 2;
}

void Industrialli_Modbus_RTU_Client::send_request(){
    for (size_t i = 0; i < frame_size; i++){
        SerialUSB.println(frame[i]);
    }

    serial->write(frame, frame_size);
    serial->flush();

    delayMicroseconds(t35);
}

bool Industrialli_Modbus_RTU_Client::receive_response(){
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

void Industrialli_Modbus_RTU_Client::read_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
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
        process_response_read_coils(_starting_address, _quantity_of_coils);
    }
}

void Industrialli_Modbus_RTU_Client::read_input_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
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
        process_response_read_input_coils(_starting_address, _quantity_of_coils);
    }
}

void Industrialli_Modbus_RTU_Client::read_holding_register(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
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
        process_response_read_holding_register(_starting_address, _quantity_of_coils);
    }
}

void Industrialli_Modbus_RTU_Client::read_input_register(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
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
        process_response_read_input_register(_starting_address, _quantity_of_coils);
    }
}

void Industrialli_Modbus_RTU_Client::write_single_coil(uint8_t _address, uint16_t _coil_address, uint16_t _value){
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
}

void Industrialli_Modbus_RTU_Client::write_single_register(uint8_t _address, uint16_t _register_address, uint16_t _value){
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
}

void Industrialli_Modbus_RTU_Client::write_multiple_coils(uint8_t _address, uint16_t _starting_address, uint8_t* _values, uint16_t _quantity_of_coils){
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
}

void Industrialli_Modbus_RTU_Client::write_multiple_registers(uint8_t _address, uint16_t _starting_address, uint16_t* _values, uint16_t _quantity_of_registers){
    frame[0] = _address;
    frame[1] = FC_WRITE_MULTIPLE_REGISTERS;
    frame[2] = _starting_address >> 8;
    frame[3] = _starting_address & 0xFF;
    frame[4] = _quantity_of_registers >> 8;
    frame[5] = _quantity_of_registers & 0xFF;
    frame[6] = _quantity_of_registers * 2;

    for (int i = 0; i < _quantity_of_registers * 2; i += 2){
        frame[7 + i] = _values[i/2] >> 8;
        frame[8 + i] = _values[i/2] & 0xFF;
    }
    
    uint16_t frame_crc = crc(_address, &frame[1], 6 + frame[6]);

    frame[7 + frame[6]] = frame_crc >> 8;
    frame[8 + frame[6]] = frame_crc & 0xFF;

    frame_size = 9 + frame[6];

    send_request();
}