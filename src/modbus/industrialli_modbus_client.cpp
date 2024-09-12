#include "modbus/industrialli_modbus_client.h"

void Industrialli_Modbus_Client::process_response_read_coils(uint16_t _start_address, uint16_t _n_coils){
    for (int reg = 0, bitpos = 0; reg < _n_coils; reg++, bitpos++, _start_address++){
        if(bitpos == 8) bitpos = 0;
        set_status_coil(_start_address, bitRead(pdu[(3 + reg/8)], bitpos));
    }
}

void Industrialli_Modbus_Client::process_response_read_input_coils(uint16_t _start_address, uint16_t _n_coils){
    for (int reg = 0, bitpos = 0; reg < _n_coils; reg++, bitpos++, _start_address++){
        if(bitpos == 8) bitpos = 0;
        set_input_coil(_start_address, bitRead(pdu[(3 + reg/8)], bitpos));
    }
}

void Industrialli_Modbus_Client::process_response_read_holding_registers(uint16_t _start_address, uint16_t _n_of_registers){
    for (uint16_t address = 3, index = 0; index < _n_of_registers; address += 2, index++){
        set_holding_register(_start_address + index, (pdu[address] << 8) | pdu[address + 1]);
    }
}

void Industrialli_Modbus_Client::process_response_read_input_registers(uint16_t _start_address, uint16_t _n_of_registers){
for (uint16_t address = 3, index = 0; index < _n_of_registers; address += 2, index++){
        set_input_register(_start_address + index, (pdu[address] << 8) | pdu[address + 1]);
    }
}

bool Industrialli_Modbus_Client::is_exception_response(uint8_t _function_code){
    return pdu[0] == _function_code + 0x80;
}

uint8_t Industrialli_Modbus_Client::get_last_exception_response(){
    return last_exception_response;
}