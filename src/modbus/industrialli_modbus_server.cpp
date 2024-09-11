#include "modbus/industrialli_modbus_server.h"

void Industrialli_Modbus_Server::process_request_read_coils(uint16_t _start_address, uint16_t _n_coils){
    if(_n_coils < 0x01 || _n_coils > 0x7d0){
        exception_response(FC_READ_COILS, EX_ILLEGAL_VALUE);
        return;
    }

    for(int i = 0; i < _n_coils; i++){
        if(!search_register(_start_address + i + 1)){
            exception_response(FC_READ_COILS, EX_ILLEGAL_ADDRESS);
            return;
        }
    }
    
    frame[0] = FC_READ_COILS;
    frame[1] = ceil(_n_coils / 8);

    for(int reg = _n_coils - 1, bitpos = 0; reg >= 0; reg--, _start_address++, bitpos++){
        if(bitpos == 8) bitpos = 0;

        if(get_status_coil(_start_address)){
            bitSet(frame[(2 + (_n_coils-reg)/8)], bitpos);
        }else {
            bitClear(frame[(2 + (_n_coils-reg)/8)], bitpos);
        }
    }

    frame_size       = ceil(_n_coils / 8) + 2;
    frame_reply_type = R_REPLY_NORMAL;
}

void Industrialli_Modbus_Server::process_request_read_input_coils(uint16_t _start_address, uint16_t _n_coils){
    if(_n_coils < 0x01 || _n_coils > 0x7d0){
        exception_response(FC_READ_INPUT_COILS, EX_ILLEGAL_VALUE);
        return;
    }

    for(int i = 0; i < _n_coils; i++){
        if(!search_register(_start_address + i + 10001)){
            exception_response(FC_READ_INPUT_COILS, EX_ILLEGAL_ADDRESS);
            return;
        }
    }

    frame[0] = FC_READ_INPUT_COILS;
    frame[1] = ceil(_n_coils / 8);
    
    for(int reg = _n_coils - 1, bitpos = 0; reg >= 0; reg--, _start_address++, bitpos++){
        if(bitpos == 8) bitpos = 0;

        if(get_input_coil(_start_address)){
            bitSet(frame[(2 + (_n_coils-reg)/8)], bitpos);
        }else {
            bitClear(frame[(2 + (_n_coils-reg)/8)], bitpos);
        }
    }

    frame_size       = ceil(_n_coils / 8) + 2;
    frame_reply_type = R_REPLY_NORMAL;
}

void Industrialli_Modbus_Server::process_request_read_holding_registers(uint16_t _start_address, uint16_t _n_registers){
    if(_n_registers < 0x01 || _n_registers > 0x07d){
        exception_response(FC_READ_HOLDING_REGISTERS, EX_ILLEGAL_VALUE);
        return;
    }

    for(int i = 0; i < _n_registers; i++){
        if(!search_register(_start_address + i + 40001)){
            exception_response(FC_READ_HOLDING_REGISTERS, EX_ILLEGAL_ADDRESS);
            return;
        }
    }

    uint16_t value;

    frame[0] = FC_READ_HOLDING_REGISTERS;
    frame[1] = 2 * _n_registers;
    
    for (int i = 0; i < _n_registers; i++){
        value = get_holding_register(_start_address + i);
        frame[2 + (2 * i)] = value >> 8;
        frame[3 + (2 * i)] = value & 0xFF;
    }

    frame_size       = 2 * _n_registers + 2;
    frame_reply_type = R_REPLY_NORMAL;
}

void Industrialli_Modbus_Server::process_request_read_input_registers(uint16_t _start_address, uint16_t _n_registers){
    if(_n_registers < 0x01 || _n_registers > 0x07d){
        exception_response(FC_READ_INPUT_REGISTERS, EX_ILLEGAL_VALUE);
        return;
    }

    for(int i = 0; i < _n_registers; i++){
        if(!search_register(_start_address + i + 30001)){
            exception_response(FC_READ_INPUT_REGISTERS, EX_ILLEGAL_ADDRESS);
            return;
        }
    }

    uint16_t value;

    frame[0] = FC_READ_INPUT_REGISTERS;
    frame[1] = 2 * _n_registers ;
    
    for (int i = 0; i < _n_registers; i++){
        value = get_input_register(_start_address + i);
        frame[2 + (2 * i)] = value >> 8;
        frame[3 + (2 * i)] = value & 0xFF;
    }

    frame_size       = 2 * _n_registers + 2;
    frame_reply_type = R_REPLY_NORMAL;
}

void Industrialli_Modbus_Server::process_request_write_single_coil(uint16_t _address, uint16_t _value){
    if(_value != 0x0000 && _value != 0xFF00){
        exception_response(FC_WRITE_SINGLE_COIL, EX_ILLEGAL_VALUE);
        return;
    }

    if(!search_register(_address + 1)){
        exception_response(FC_WRITE_SINGLE_COIL, EX_ILLEGAL_ADDRESS);
        return;
    }

    set_status_coil(_address, (bool)_value);
    frame_reply_type = R_REPLY_ECHO;
}



void Industrialli_Modbus_Server::process_request_write_single_register(uint16_t _address, uint16_t _value){
    if(_value < 0x00 || _value > 0xFFFF){
        exception_response(FC_WRITE_SINGLE_REGISTER, EX_ILLEGAL_VALUE);
        return;
    }

    if(!search_register(_address + 40001)){
        exception_response(FC_WRITE_SINGLE_REGISTER, EX_ILLEGAL_ADDRESS);
        return;
    }

    set_holding_register(_address, _value);
    frame_reply_type = R_REPLY_ECHO;
}

void Industrialli_Modbus_Server::process_request_write_multiple_coils(uint8_t *_frame, uint16_t _start_address, uint16_t _n_coils){
    if(_n_coils < 0x01 || _n_coils > 0x07b0){
        exception_response(FC_WRITE_MULTIPLE_COILS, EX_ILLEGAL_VALUE);
        return;
    }

    for (size_t i = 0; i < _n_coils; i++){
        if(!search_register(_start_address + i + 1)){
            exception_response(FC_WRITE_MULTIPLE_COILS, EX_ILLEGAL_ADDRESS);
            return;
        }
    } 

    frame[0] = FC_WRITE_MULTIPLE_COILS;
    frame[1] = _start_address >> 8;
    frame[2] = _start_address & 0xFF;
    frame[3] = _n_coils >> 8;
    frame[4] = _n_coils & 0xFF;
    
    for(int reg = _n_coils, bitpos = 0; reg >= 0; reg--, _start_address++, bitpos++){
        if(bitpos == 8) bitpos = 0;
        set_status_coil(_start_address, bitRead(_frame[(7 + (_n_coils-reg)/8)], bitpos));
    }

    frame_size       = 5;
    frame_reply_type = R_REPLY_NORMAL;
}

void Industrialli_Modbus_Server::process_request_write_multiple_registers(uint8_t *_frame, uint16_t _start_address, uint16_t _n_registers){
    if(_n_registers < 0x01 || _n_registers > 0x07b){
        exception_response(FC_WRITE_MULTIPLE_REGISTERS, EX_ILLEGAL_VALUE);
        return;
    }

    for (size_t i = 0; i < _n_registers; i++){
        if(!search_register(_start_address + i + 40001)){
            exception_response(FC_WRITE_MULTIPLE_REGISTERS, EX_ILLEGAL_ADDRESS);
            return;
        }
    }

    frame[0] = FC_WRITE_MULTIPLE_REGISTERS;
    frame[1] = _start_address >> 8;
    frame[2] = _start_address & 0xFF;
    frame[3] = _n_registers >> 8;
    frame[4] = _n_registers & 0xFF;
    
    for (uint16_t address = 7, index = 0; index < _n_registers; address += 2, index++){
        set_holding_register(_start_address + index, (_frame[address] << 8) | _frame[address + 1]);
    }

    frame_size       = 5;
    frame_reply_type = R_REPLY_NORMAL;
}

bool Industrialli_Modbus_Server::receive_request(){
    frame_size = 0;
    unsigned long startTime = 0;
    
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

        if(crc_frame == crc(frame[0], &frame[1], frame_size - 3) && (frame[0] == get_server_address() || frame[0] == 0x00)){
            return true;
        }
    }
    
    return false;
}

void Industrialli_Modbus_Server::process_request(){
    uint8_t _address = frame[0];
    uint8_t function = frame[1];
    uint16_t field_1 = (frame[2] << 8) | frame[3];
    uint16_t field_2 = (frame[4] << 8) | frame[5];
   
    switch (function){
        case FC_READ_COILS:
            process_request_read_coils(field_1, field_2);
            break;

        case FC_READ_INPUT_COILS:
            process_request_read_input_coils(field_1, field_2);
            break;

        case FC_READ_HOLDING_REGISTERS:
            process_request_read_holding_registers(field_1, field_2);
            break;

        case FC_READ_INPUT_REGISTERS:
            process_request_read_input_registers(field_1, field_2);
            break;

        case FC_WRITE_SINGLE_COIL:
            process_request_write_single_coil(field_1, field_2);
            break;

        case FC_WRITE_SINGLE_REGISTER:
            process_request_write_single_register(field_1, field_2);
            break;

        case FC_WRITE_MULTIPLE_COILS:
            process_request_write_multiple_coils(frame, field_1, field_2);
            break;

        case FC_WRITE_MULTIPLE_REGISTERS:
            process_request_write_multiple_registers(frame, field_1, field_2);
            break;
            
        default:
            exception_response(_address, EX_ILLEGAL_FUNCTION);
            break;
    }
}

void Industrialli_Modbus_Server::exception_response(uint8_t _error_code, uint8_t _exception_code){
    frame[0] = _error_code + 0x80;
    frame[1] = _exception_code;

    frame_size       = 2;
    frame_reply_type = R_REPLY_NORMAL;
}

void Industrialli_Modbus_Server::send_normal_response(){
    digitalWrite(de_pin, HIGH);
    delay(5);
        
    serial->write(get_server_address());
    serial->write(frame, frame_size);

    uint16_t crc_value = crc(get_server_address(), frame, frame_size);

    serial->write(crc_value >> 8);
    serial->write(crc_value & 0xFF);

    serial->flush();

    delayMicroseconds(t35);

    digitalWrite(de_pin, LOW);
}

void Industrialli_Modbus_Server::send_echo_response(){
    digitalWrite(de_pin, HIGH);
    delay(5);

    serial->write(frame, frame_size);
    serial->flush();

    delayMicroseconds(t35);

    digitalWrite(de_pin, LOW);
}

void Industrialli_Modbus_Server::clear_rx_buffer(){
    unsigned long start_time = micros();
        
    do {
        if (serial->available()) {
            start_time = micros();
            serial->read();
        }
    }while (micros() - start_time < t35);
}

uint16_t Industrialli_Modbus_Server::crc(uint8_t _address, uint8_t *_pdu, int _pdu_size){
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

Industrialli_Modbus_Server::Industrialli_Modbus_Server(HardwareSerial *_serial){
    serial = _serial;
}

void Industrialli_Modbus_Server::begin(){
    registers_head = NULL;
    registers_last = NULL;
    de_pin         = PD4;

    pinMode(de_pin, OUTPUT);
    digitalWrite(de_pin, LOW);

    t15 = 15000000/9600; 
    t35 = 35000000/9600;

    clear_rx_buffer();
}

void Industrialli_Modbus_Server::set_server_address(uint8_t _server_address){
    server_address = _server_address;
}

uint8_t Industrialli_Modbus_Server::get_server_address(){
    return server_address;
}

void Industrialli_Modbus_Server::task(){
    if(receive_request()){
        process_request();

        if(frame_reply_type == R_REPLY_NORMAL){
            send_normal_response();
        }

        if(frame_reply_type == R_REPLY_ECHO){
            send_echo_response();
        }
    }
}