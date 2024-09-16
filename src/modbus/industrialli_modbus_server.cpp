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
    
    clear_pdu();
    
    pdu[0] = FC_READ_COILS;
    pdu[1] = ceil(_n_coils / 8.0);

    for (int reg = 0, bitpos = 0; reg < _n_coils; reg++, bitpos++, _start_address++){
        if(bitpos == 8) bitpos = 0;
        
        if(get_status_coil(_start_address)){
            bitSet(pdu[(2 + reg/8)], bitpos);
        }else {
            bitClear(pdu[(2 + reg/8)], bitpos);
        }
    }

    pdu_size       = ceil(_n_coils / 8.0) + 2;
    pdu_reply_type = R_REPLY_NORMAL;
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

    clear_pdu();

    pdu[0] = FC_READ_INPUT_COILS;
    pdu[1] = ceil(_n_coils / 8.0);

    for (int reg = 0, bitpos = 0; reg < _n_coils; reg++, bitpos++, _start_address++){
        if(bitpos == 8) bitpos = 0;
        
        if(get_input_coil(_start_address)){
            bitSet(pdu[(2 + reg/8)], bitpos);
        }else {
            bitClear(pdu[(2 + reg/8)], bitpos);
        }
    }

    pdu_size       = ceil(_n_coils / 8.0) + 2;
    pdu_reply_type = R_REPLY_NORMAL;
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

    clear_pdu();

    uint16_t value;

    pdu[0] = FC_READ_HOLDING_REGISTERS;
    pdu[1] = 2 * _n_registers;
    
    for (int i = 0; i < _n_registers; i++){
        value = get_holding_register(_start_address + i);
        pdu[2 + (2 * i)] = value >> 8;
        pdu[3 + (2 * i)] = value & 0xFF;
    }

    pdu_size       = 2 * _n_registers + 2;
    pdu_reply_type = R_REPLY_NORMAL;
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

    clear_pdu();

    uint16_t value;

    pdu[0] = FC_READ_INPUT_REGISTERS;
    pdu[1] = 2 * _n_registers ;
    
    for (int i = 0; i < _n_registers; i++){
        value = get_input_register(_start_address + i);
        pdu[2 + (2 * i)] = value >> 8;
        pdu[3 + (2 * i)] = value & 0xFF;
    }

    pdu_size       = 2 * _n_registers + 2;
    pdu_reply_type = R_REPLY_NORMAL;
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

    if(_value == 0xFF00){
        set_status_coil(_address, HIGH);
    }else {
        set_status_coil(_address, LOW);
    }

    pdu_reply_type = R_REPLY_ECHO;
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
    pdu_reply_type = R_REPLY_ECHO;
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

    pdu[0] = FC_WRITE_MULTIPLE_COILS;
    pdu[1] = _start_address >> 8;
    pdu[2] = _start_address & 0xFF;
    pdu[3] = _n_coils >> 8;
    pdu[4] = _n_coils & 0xFF;

    for (int reg = 0, bitpos = 0; reg < _n_coils; reg++, bitpos++, _start_address++){
        if(bitpos == 8) bitpos = 0;
        set_status_coil(_start_address, bitRead(pdu[(6 + reg/8)], bitpos));
    }

    pdu_size       = 5;
    pdu_reply_type = R_REPLY_NORMAL;
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

    pdu[0] = FC_WRITE_MULTIPLE_REGISTERS;
    pdu[1] = _start_address >> 8;
    pdu[2] = _start_address & 0xFF;
    pdu[3] = _n_registers >> 8;
    pdu[4] = _n_registers & 0xFF;
    
    for (uint16_t address = 6, index = 0; index < _n_registers; address += 2, index++){
        set_holding_register(_start_address + index, (_frame[address] << 8) | _frame[address + 1]);
    }

    pdu_size       = 5;
    pdu_reply_type = R_REPLY_NORMAL;
}

void Industrialli_Modbus_Server::exception_response(uint8_t _error_code, uint8_t _exception_code){
    pdu[0] = _error_code + 0x80;
    pdu[1] = _exception_code;

    pdu_size       = 2;
    pdu_reply_type = R_REPLY_NORMAL;
}

void Industrialli_Modbus_Server::clear_pdu(){
    pdu      = pdu_ptr;
    pdu_size = 0;
}