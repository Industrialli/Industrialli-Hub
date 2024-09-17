#include "modbus/industrialli_modbus_tcp_client.h"

void Industrialli_Modbus_TCP_Client::send_request(){
    MBAP[4] = (pdu_size + 1) >> 8;  
    MBAP[5] = (pdu_size + 1) & 0x00FF;

    client->write(MBAP, 7);
    client->write(pdu, pdu_size);

    client->flush();
    // client->stop();
}

bool Industrialli_Modbus_TCP_Client::receive_response(){
    clear_pdu();
}

void Industrialli_Modbus_TCP_Client::begin(EthernetClient *_client){
    pdu      = (uint8_t *)malloc(256);
    pdu_ptr  = pdu;
    pdu_size = 256;

    registers_head   = NULL;
    registers_last   = NULL;
    response_timeout = 100;
    last_exception_response = 0;

    client = _client;
}

void Industrialli_Modbus_TCP_Client::read_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
    MBAP[0] = 0x00;
    MBAP[1] = 0x01;
    MBAP[2] = 0x00;
    MBAP[3] = 0x00;
    MBAP[6] = _address;

    pdu[0] = FC_READ_COILS;
    pdu[1] = _starting_address >> 8;
    pdu[2] = _starting_address & 0xFF;
    pdu[3] = _quantity_of_coils >> 8;
    pdu[4] = _quantity_of_coils & 0xFF;

    pdu_size = 5;

    send_request();
}

void Industrialli_Modbus_TCP_Client::read_input_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
    MBAP[0] = 0x00;
    MBAP[1] = 0x01;
    MBAP[2] = 0x00;
    MBAP[3] = 0x00;
    MBAP[6] = _address;

    pdu[0] = FC_READ_INPUT_COILS;
    pdu[1] = _starting_address >> 8;
    pdu[2] = _starting_address & 0xFF;
    pdu[3] = _quantity_of_coils >> 8;
    pdu[4] = _quantity_of_coils & 0xFF;

    pdu_size = 5;

    send_request();
}

void Industrialli_Modbus_TCP_Client::read_holding_registers(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_registers){
    MBAP[0] = 0x00;
    MBAP[1] = 0x01;
    MBAP[2] = 0x00;
    MBAP[3] = 0x00;
    MBAP[6] = _address;

    pdu[0] = FC_READ_HOLDING_REGISTERS;
    pdu[1] = _starting_address >> 8;
    pdu[2] = _starting_address & 0xFF;
    pdu[3] = _quantity_of_registers >> 8;
    pdu[4] = _quantity_of_registers & 0xFF;

    pdu_size = 5;

    send_request();
}

void Industrialli_Modbus_TCP_Client::read_input_registers(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_registers){
    MBAP[0] = 0x00;
    MBAP[1] = 0x01;
    MBAP[2] = 0x00;
    MBAP[3] = 0x00;
    MBAP[6] = _address;

    pdu[0] = FC_READ_INPUT_REGISTERS;
    pdu[1] = _starting_address >> 8;
    pdu[2] = _starting_address & 0xFF;
    pdu[3] = _quantity_of_registers >> 8;
    pdu[4] = _quantity_of_registers & 0xFF;

    pdu_size = 5;

    send_request();
}

void Industrialli_Modbus_TCP_Client::write_single_coil(uint8_t _address, uint16_t _coil_address, bool _value){
    MBAP[0] = 0x00;
    MBAP[1] = 0x01;
    MBAP[2] = 0x00;
    MBAP[3] = 0x00;
    MBAP[6] = _address;

    pdu[0] = FC_WRITE_SINGLE_COIL;
    pdu[1] = _coil_address >> 8;
    pdu[2] = _coil_address & 0xFF;

    if(_value){
        pdu[3] = 0xFF;
        pdu[4] = 0x00;

    }else {
        pdu[3] = 0x00;
        pdu[4] = 0x00;
    }

    pdu_size = 5;

    send_request();
}

void Industrialli_Modbus_TCP_Client::write_single_register(uint8_t _address, uint16_t _register_address, uint16_t _value){
    MBAP[0] = 0x00;
    MBAP[1] = 0x01;
    MBAP[2] = 0x00;
    MBAP[3] = 0x00;
    MBAP[6] = _address;

    pdu[0] = FC_WRITE_SINGLE_REGISTER;
    pdu[1] = _register_address >> 8;
    pdu[2] = _register_address & 0xFF;
    pdu[3] = _value >> 8;
    pdu[4] = _value & 0xFF;

    pdu_size = 5;

    send_request();
}

void Industrialli_Modbus_TCP_Client::write_multiple_coils(uint8_t _address, uint16_t _starting_address, uint8_t* _values, uint16_t _quantity_of_coils){
    MBAP[0] = 0x00;
    MBAP[1] = 0x01;
    MBAP[2] = 0x00;
    MBAP[3] = 0x00;
    MBAP[6] = _address;

    pdu[0] = FC_WRITE_MULTIPLE_COILS;
    pdu[1] = _starting_address >> 8;
    pdu[2] = _starting_address & 0xFF;
    pdu[3] = _quantity_of_coils >> 8;
    pdu[4] = _quantity_of_coils & 0xFF;
    pdu[5] = ceil(_quantity_of_coils / 8.0);

    for (uint16_t i = 0; i < _quantity_of_coils; i++) {
        bitWrite(pdu[6 + (i >> 3)], i & 7, _values[i]);
    }

    for (uint16_t i = _quantity_of_coils; i < (pdu[5] * 8); i++) {
        bitClear(pdu[6 + (i >> 3)], i & 7);
    }

    pdu_size = 6 + pdu[5];

    send_request();
}

void Industrialli_Modbus_TCP_Client::write_multiple_registers(uint8_t _address, uint16_t _starting_address, uint16_t* _values, uint16_t _quantity_of_registers){
    MBAP[0] = 0x00;
    MBAP[1] = 0x01;
    MBAP[2] = 0x00;
    MBAP[3] = 0x00;
    MBAP[6] = _address;

    pdu[0] = FC_WRITE_MULTIPLE_REGISTERS;
    pdu[1] = _starting_address >> 8;
    pdu[2] = _starting_address & 0xFF;
    pdu[3] = _quantity_of_registers >> 8;
    pdu[4] = _quantity_of_registers & 0xFF;
    pdu[5] = _quantity_of_registers * 2;

    for (int i = 0; i < _quantity_of_registers * 2; i += 2){
        pdu[6 + i] = _values[i/2] >> 8;
        pdu[7 + i] = _values[i/2] & 0xFF;
    }

    pdu_size = 6 + pdu[5];

    send_request();
}