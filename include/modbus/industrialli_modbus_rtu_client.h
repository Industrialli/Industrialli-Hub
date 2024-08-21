#ifndef INDUSTRIALLI_MODBUS_RTU_CLIENT_H
#define INDUSTRIALLI_MODBUS_RTU_CLIENT_H

#include <Arduino.h>
#include <HardwareSerial.h>

#include "industrialli_modbus_rtu.h"

class Industrialli_Modbus_RTU_Client : public Industrialli_Modbus_RTU{
private:
    HardwareSerial *serial;
    uint16_t t15;
    uint16_t t35;
    uint8_t response_timeout;

    uint8_t de_pin;

    uint8_t frame[256];
    uint8_t frame_size;

    uint8_t last_exception_response;

    void process_response_read_coils(uint16_t _start_address, uint16_t _n_coils);
    void process_response_read_input_coils(uint16_t _start_address, uint16_t _n_coils);
    void process_response_read_holding_registers(uint16_t _start_address, uint16_t _n_of_registers);
    void process_response_read_input_registers(uint16_t _start_address, uint16_t _n_of_registers);

    void send_request();
    bool receive_response();
    bool is_exception_response(uint8_t _function_code);
    
    void clear_rx_buffer();
    uint16_t crc(uint8_t _address, uint8_t *_pdu, int _pdu_size);

public:
    void begin(HardwareSerial *_seria, long _baud, int _de_pin);

    uint8_t get_last_exception_response();

    void read_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils);
    void read_input_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils);
    void read_holding_registers(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_registers);
    void read_input_registers(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_registers);
    void write_single_coil(uint8_t _address, uint16_t _coil_address, uint16_t _value);
    void write_single_register(uint8_t _address, uint16_t _register_address, uint16_t _value);
    void write_multiple_coils(uint8_t _address, uint16_t _starting_address, uint8_t* _values, uint16_t _quantity_of_coils);
    void write_multiple_registers(uint8_t _address, uint16_t _starting_address, uint16_t* _values, uint16_t _quantity_of_registers);
};

#endif