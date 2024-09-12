#ifndef INDUSTRIALLI_MODBUS_CLIENT_H
#define INDUSTRIALLI_MODBUS_CLIENT_H

#include <Arduino.h>

#include "industrialli_modbus.h"

class Industrialli_Modbus_Client : public Industrialli_Modbus{
protected:
    uint8_t *pdu;
    uint8_t *pdu_ptr;
    uint8_t pdu_size;

    uint8_t last_exception_response;

    void process_response_read_coils(uint16_t _start_address, uint16_t _n_coils);
    void process_response_read_input_coils(uint16_t _start_address, uint16_t _n_coils);
    void process_response_read_holding_registers(uint16_t _start_address, uint16_t _n_of_registers);
    void process_response_read_input_registers(uint16_t _start_address, uint16_t _n_of_registers);

    bool is_exception_response(uint8_t _function_code);
    uint8_t get_last_exception_response();
};

#endif