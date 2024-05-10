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

void Industrialli_Modbus_RTU_Client::process_response_read_holding_registers(uint16_t _start_address, uint16_t _n_of_registers){
    for (uint16_t address = 3, index = 0; index < _n_of_registers; address += 2, index++){
        set_holding_register(_start_address + index, (frame[address] << 8) | frame[address + 1]);
    }
}

void Industrialli_Modbus_RTU_Client::process_response_read_input_registers(uint16_t _start_address, uint16_t _n_of_registers){
for (uint16_t address = 3, index = 0; index < _n_of_registers; address += 2, index++){
        set_input_register(_start_address + index, (frame[address] << 8) | frame[address + 1]);
    }
}

void Industrialli_Modbus_RTU_Client::send_request(){
    digitalWrite(re_de_pin, HIGH);

    serial->write(frame, frame_size);
    serial->flush();

    delayMicroseconds(t35);

    digitalWrite(re_de_pin, LOW);
}

bool Industrialli_Modbus_RTU_Client::receive_response(){
    frame_size = 0;
    unsigned long startTime = millis();

    while (!serial->available()) {
        if (millis() - startTime >= response_timeout) {
            return false;
        }
    }
    
    if(serial->available()){

        do{
            if (serial->available()) {
                startTime = micros();
                frame[frame_size++] = serial->read();
                
            }
        
        }while (micros() - startTime <= t15 && frame_size < 256);

        while (micros() - startTime < t35);

        if(frame_size == 0) return false;

        uint16_t crc_frame = (frame[frame_size - 2] << 8) | (frame[frame_size - 1]);

        if(crc_frame == crc(frame[0], &frame[1], frame_size - 3)){
            return true;
        }
    }
    
    return false;
}

bool Industrialli_Modbus_RTU_Client::is_exception_response(uint8_t _function_code){
    return frame[1] == _function_code + 0x80;
}

void Industrialli_Modbus_RTU_Client::clear_rx_buffer(){
    unsigned long start_time = micros();
        
    do {
        if (serial->available()) {
            start_time = micros();
            serial->read();
        }
    }while (micros() - start_time < t35);
}

uint16_t Industrialli_Modbus_RTU_Client::crc(uint8_t _address, uint8_t *_pdu, int _pdu_size){
    uint8_t uchCRCHi = 0xFF;
    uint8_t uchCRCLo = 0xFF;
    uint8_t index;

    index   = uchCRCLo ^ _address;
    uchCRCLo = uchCRCHi ^ auchCRCHi[index];
    uchCRCHi = auchCRCLo[index];
    
    while(_pdu_size--){
        index   = uchCRCLo ^ *_pdu++;
        uchCRCLo = uchCRCHi ^ auchCRCHi[index];
        uchCRCHi = auchCRCLo[index];
    }

    return (uchCRCHi << 8 | uchCRCLo);
}

void Industrialli_Modbus_RTU_Client::begin(HardwareSerial *_serial, uint8_t _re_de_pin){
    serial         = _serial;
    registers_head = NULL;
    registers_last = NULL;
    re_de_pin      = _re_de_pin;
    last_exception_response = 0;

    t15 = 15000000/9600; 
    t35 = 35000000/9600;
    response_timeout = 100;

    clear_rx_buffer();
}

uint8_t Industrialli_Modbus_RTU_Client::get_last_exception_response(){
    return last_exception_response;
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
        if(is_exception_response(FC_READ_COILS)){
            last_exception_response = frame[2];
        }else {
            process_response_read_coils(_starting_address, _quantity_of_coils);
        }
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
        if(is_exception_response(FC_READ_INPUT_COILS)){
            last_exception_response = frame[2];
        }else {
            process_response_read_input_coils(_starting_address, _quantity_of_coils);
        }
    }
}

void Industrialli_Modbus_RTU_Client::read_holding_registers(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
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
        if(is_exception_response(FC_READ_HOLDING_REGISTERS)){
            last_exception_response = frame[2];
        }else {
            process_response_read_holding_registers(_starting_address, _quantity_of_coils);
        }
    }
}

void Industrialli_Modbus_RTU_Client::read_input_registers(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
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
        if(is_exception_response(FC_READ_INPUT_REGISTERS)){
            last_exception_response = frame[2];
        }else {
            process_response_read_input_registers(_starting_address, _quantity_of_coils);
        }
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
    
    if(receive_response()){
        if(is_exception_response(FC_WRITE_SINGLE_COIL)){
            last_exception_response = frame[2];
        }
    }
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

    if(receive_response()){
        if(is_exception_response(FC_WRITE_SINGLE_REGISTER)){
            last_exception_response = frame[2];
        }
    }
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

    if(receive_response()){
        if(is_exception_response(FC_WRITE_MULTIPLE_COILS)){
            last_exception_response = frame[2];
        }
    }
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

    if(receive_response()){
        if(is_exception_response(FC_WRITE_MULTIPLE_REGISTERS)){
            last_exception_response = frame[2];
        }
    }
}