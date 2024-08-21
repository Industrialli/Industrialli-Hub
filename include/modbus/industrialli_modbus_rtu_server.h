#ifndef INDUSTRIALLI_MODBUS_RTU_SERVER_H
#define INDUSTRIALLI_MODBUS_RTU_SERVER_H

#include <Arduino.h>
#include <HardwareSerial.h>

#include "industrialli_modbus_rtu.h"

class Industrialli_Modbus_RTU_Server : public Industrialli_Modbus_RTU{
private:
    uint8_t server_address;

    HardwareSerial *serial;
    uint16_t t15;
    uint16_t t35;

    uint8_t de_pin;

    uint8_t frame[256];
    uint8_t frame_size;
    uint8_t frame_reply_type;
    
    void process_request_read_coils(uint16_t _start_address, uint16_t _n_coils);
    void process_request_read_input_coils(uint16_t _start_address, uint16_t _n_coils);
    void process_request_read_holding_registers(uint16_t _start_address, uint16_t _n_registers);
    void process_request_read_input_registers(uint16_t _start_address, uint16_t _n_registers);
    void process_request_write_single_coil(uint16_t _address, uint16_t _value);
    void process_request_write_single_register(uint16_t _address, uint16_t _value);
    void process_request_write_multiple_coils(uint8_t *_frame, uint16_t _start_address, uint16_t _n_coils);
    void process_request_write_multiple_registers(uint8_t *_frame, uint16_t _start_address, uint16_t _n_registers);

    bool receive_request();
    void process_request();
    void exception_response(uint8_t _error_code, uint8_t _exception_code);
    void send_normal_response();
    void send_echo_response();
    
    void clear_rx_buffer();
    uint16_t crc(uint8_t _address, uint8_t *_pdu, int _pdu_size);

public:
    void begin(HardwareSerial *_serial, long _baud, int _de_pin);

    void set_server_address(uint8_t _server_address);
    uint8_t get_server_address();
    
    void task();
};

#endif