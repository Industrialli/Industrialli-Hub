#ifndef INDUSTRIALLI_MODBUS_CLIENT_H
#define INDUSTRIALLI_MODBUS_CLIENT_H

#include <Arduino.h>

#include "industrialli_modbus.h"

class Industrialli_Modbus_Client : public Industrialli_Modbus{
protected:
    uint8_t adu[256];
    uint8_t adu_size;

    uint8_t last_exception_response;

    void process_response_read_coils(uint16_t _start_address, uint16_t _n_coils);
    void process_response_read_input_coils(uint16_t _start_address, uint16_t _n_coils);
    void process_response_read_holding_registers(uint16_t _start_address, uint16_t _n_of_registers);
    void process_response_read_input_registers(uint16_t _start_address, uint16_t _n_of_registers);

    void read_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils);
    void read_input_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils);
    void read_holding_registers(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_registers);
    void read_input_registers(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_registers);
    void write_single_coil(uint8_t _address, uint16_t _coil_address, uint16_t _value);
    void write_single_register(uint8_t _address, uint16_t _register_address, uint16_t _value);
    void write_multiple_coils(uint8_t _address, uint16_t _starting_address, uint8_t* _values, uint16_t _quantity_of_coils);
    void write_multiple_registers(uint8_t _address, uint16_t _starting_address, uint16_t* _values, uint16_t _quantity_of_registers);

    bool is_exception_response(uint8_t _function_code);
    uint8_t get_last_exception_response();
};

#endif