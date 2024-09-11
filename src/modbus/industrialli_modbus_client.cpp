#include "modbus/industrialli_modbus_client.h"

void Industrialli_Modbus_Client::process_response_read_coils(uint16_t _start_address, uint16_t _n_coils){
    for (int reg = 0, bitpos = 0; reg < _n_coils; reg++, bitpos++, _start_address++){
        if(bitpos == 8) bitpos = 0;
        set_status_coil(_start_address, bitRead(adu[(3 + reg/8)], bitpos));
    }
}

void Industrialli_Modbus_Client::process_response_read_input_coils(uint16_t _start_address, uint16_t _n_coils){
    for (int reg = 0, bitpos = 0; reg < _n_coils; reg++, bitpos++, _start_address++){
        if(bitpos == 8) bitpos = 0;
        set_input_coil(_start_address, bitRead(adu[(3 + reg/8)], bitpos));
    }
}

void Industrialli_Modbus_Client::process_response_read_holding_registers(uint16_t _start_address, uint16_t _n_of_registers){
    for (uint16_t address = 3, index = 0; index < _n_of_registers; address += 2, index++){
        set_holding_register(_start_address + index, (adu[address] << 8) | adu[address + 1]);
    }
}

void Industrialli_Modbus_Client::process_response_read_input_registers(uint16_t _start_address, uint16_t _n_of_registers){
for (uint16_t address = 3, index = 0; index < _n_of_registers; address += 2, index++){
        set_input_register(_start_address + index, (adu[address] << 8) | adu[address + 1]);
    }
}

bool Industrialli_Modbus_Client::is_exception_response(uint8_t _function_code){
    return adu[1] == _function_code + 0x80;
}

uint8_t Industrialli_Modbus_Client::get_last_exception_response(){
    return last_exception_response;
}

void Industrialli_Modbus_Client::read_input_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
    adu[0] = _address;
    adu[1] = FC_READ_INPUT_COILS;
    adu[2] = _starting_address >> 8;
    adu[3] = _starting_address & 0xFF;
    adu[4] = _quantity_of_coils >> 8;
    adu[5] = _quantity_of_coils & 0xFF;

    uint16_t frame_crc = crc(_address, &adu[1], 5);

    adu[6] = frame_crc >> 8;
    adu[7] = frame_crc & 0xFF;

    adu_size = 8;

    send_request();
    
    if(receive_response()){
        if(is_exception_response(FC_READ_INPUT_COILS)){
            last_exception_response = adu[2];
        }else {
            process_response_read_input_coils(_starting_address, _quantity_of_coils);
        }
    }
}

void Industrialli_Modbus_Client::read_holding_registers(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
    adu[0] = _address;
    adu[1] = FC_READ_HOLDING_REGISTERS;
    adu[2] = _starting_address >> 8;
    adu[3] = _starting_address & 0xFF;
    adu[4] = _quantity_of_coils >> 8;
    adu[5] = _quantity_of_coils & 0xFF;

    uint16_t frame_crc = crc(_address, &adu[1], 5);

    adu[6] = frame_crc >> 8;
    adu[7] = frame_crc & 0xFF;

    adu_size = 8;

    send_request();
    
    if(receive_response()){
        if(is_exception_response(FC_READ_HOLDING_REGISTERS)){
            last_exception_response = adu[2];
        }else {
            process_response_read_holding_registers(_starting_address, _quantity_of_coils);
        }
    }
}

void Industrialli_Modbus_Client::read_input_registers(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
    adu[0] = _address;
    adu[1] = FC_READ_INPUT_REGISTERS;
    adu[2] = _starting_address >> 8;
    adu[3] = _starting_address & 0xFF;
    adu[4] = _quantity_of_coils >> 8;
    adu[5] = _quantity_of_coils & 0xFF;

    uint16_t frame_crc = crc(_address, &adu[1], 5);

    adu[6] = frame_crc >> 8;
    adu[7] = frame_crc & 0xFF;

    adu_size = 8;

    send_request();
    
    if(receive_response()){
        if(is_exception_response(FC_READ_INPUT_REGISTERS)){
            last_exception_response = adu[2];
        }else {
            process_response_read_input_registers(_starting_address, _quantity_of_coils);
        }
    }
}

void Industrialli_Modbus_Client::write_single_coil(uint8_t _address, uint16_t _coil_address, uint16_t _value){
    adu[0] = _address;
    adu[1] = FC_WRITE_SINGLE_COIL;
    adu[2] = _coil_address >> 8;
    adu[3] = _coil_address & 0xFF;
    adu[4] = _value >> 8;
    adu[5] = _value & 0xFF;

    uint16_t frame_crc = crc(_address, &adu[1], 5);

    adu[6] = frame_crc >> 8;
    adu[7] = frame_crc & 0xFF;

    adu_size = 8;

    send_request();
    
    if(receive_response()){
        if(is_exception_response(FC_WRITE_SINGLE_COIL)){
            last_exception_response = adu[2];
        }
    }
}

void Industrialli_Modbus_Client::write_single_register(uint8_t _address, uint16_t _register_address, uint16_t _value){
    adu[0] = _address;
    adu[1] = FC_WRITE_SINGLE_REGISTER;
    adu[2] = _register_address >> 8;
    adu[3] = _register_address & 0xFF;
    adu[4] = _value >> 8;
    adu[5] = _value & 0xFF;

    uint16_t frame_crc = crc(_address, &adu[1], 5);

    adu[6] = frame_crc >> 8;
    adu[7] = frame_crc & 0xFF;

    adu_size = 8;

    send_request();

    if(receive_response()){
        if(is_exception_response(FC_WRITE_SINGLE_REGISTER)){
            last_exception_response = adu[2];
        }
    }
}

void Industrialli_Modbus_Client::write_multiple_coils(uint8_t _address, uint16_t _starting_address, uint8_t* _values, uint16_t _quantity_of_coils){
    adu[0] = _address;
    adu[1] = FC_WRITE_MULTIPLE_COILS;
    adu[2] = _starting_address >> 8;
    adu[3] = _starting_address & 0xFF;
    adu[4] = _quantity_of_coils >> 8;
    adu[5] = _quantity_of_coils & 0xFF;
    adu[6] = ceil(_quantity_of_coils / 8.0);

    for (uint16_t i = 0; i < _quantity_of_coils; i++) {
        bitWrite(adu[7 + (i >> 3)], i & 7, _values[i]);
    }

    for (uint16_t i = _quantity_of_coils; i < (adu[6] * 8); i++) {
        bitClear(adu[7 + (i >> 3)], i & 7);
    }

    uint16_t frame_crc = crc(_address, &adu[1], 6 + adu[6]);

    adu[7 + adu[6]] = frame_crc >> 8;
    adu[8 + adu[6]] = frame_crc & 0xFF;

    adu_size = 9 + adu[6];

    send_request();

    if(receive_response()){
        if(is_exception_response(FC_WRITE_MULTIPLE_COILS)){
            last_exception_response = adu[2];
        }
    }
}

void Industrialli_Modbus_Client::write_multiple_registers(uint8_t _address, uint16_t _starting_address, uint16_t* _values, uint16_t _quantity_of_registers){
    adu[0] = _address;
    adu[1] = FC_WRITE_MULTIPLE_REGISTERS;
    adu[2] = _starting_address >> 8;
    adu[3] = _starting_address & 0xFF;
    adu[4] = _quantity_of_registers >> 8;
    adu[5] = _quantity_of_registers & 0xFF;
    adu[6] = _quantity_of_registers * 2;

    for (int i = 0; i < _quantity_of_registers * 2; i += 2){
        adu[7 + i] = _values[i/2] >> 8;
        adu[8 + i] = _values[i/2] & 0xFF;
    }
    
    uint16_t frame_crc = crc(_address, &adu[1], 6 + adu[6]);

    adu[7 + adu[6]] = frame_crc >> 8;
    adu[8 + adu[6]] = frame_crc & 0xFF;

    adu_size = 9 + adu[6];

    send_request();

    if(receive_response()){
        if(is_exception_response(FC_WRITE_MULTIPLE_REGISTERS)){
            last_exception_response = adu[2];
        }
    }
}