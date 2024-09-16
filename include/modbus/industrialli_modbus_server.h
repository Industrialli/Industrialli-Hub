#ifndef INDUSTRIALLI_MODBUS_SERVER_H
#define INDUSTRIALLI_MODBUS_SERVER_H

#include <Arduino.h>
#include <HardwareSerial.h>

#include "industrialli_modbus.h"

class Industrialli_Modbus_Server : public Industrialli_Modbus{
protected:
    uint8_t *pdu;
    uint8_t *pdu_ptr;
    uint16_t pdu_size;
    uint8_t pdu_reply_type;
    
    void process_request_read_coils(uint16_t _start_address, uint16_t _n_coils);
    void process_request_read_input_coils(uint16_t _start_address, uint16_t _n_coils);
    void process_request_read_holding_registers(uint16_t _start_address, uint16_t _n_registers);
    void process_request_read_input_registers(uint16_t _start_address, uint16_t _n_registers);
    void process_request_write_single_coil(uint16_t _address, uint16_t _value);
    void process_request_write_single_register(uint16_t _address, uint16_t _value);
    void process_request_write_multiple_coils(uint8_t *_pdu, uint16_t _start_address, uint16_t _n_coils);
    void process_request_write_multiple_registers(uint8_t *_pdu, uint16_t _start_address, uint16_t _n_registers);

    void exception_response(uint8_t _error_code, uint8_t _exception_code);

    void clear_pdu();
};

#endif