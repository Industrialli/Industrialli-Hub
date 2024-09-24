#ifndef INDUSTRIALLI_MODBUS_RTU_SERVER_H
#define INDUSTRIALLI_MODBUS_RTU_SERVER_H

#include <Arduino.h>
#include <HardwareSerial.h>

#include "industrialli_modbus_server.h"

class Industrialli_Modbus_RTU_Server : public Industrialli_Modbus_Server{
private:
    uint8_t server_address;

    HardwareSerial *serial;
    uint32_t t15;
    uint32_t t35;

    uint32_t de_pin;
   
    bool receive_request();
    void process_request();

    void send_normal_response();
    void send_echo_response();

    void clear_rx_buffer();
    uint16_t crc(uint8_t _address, uint8_t *_pdu, int _pdu_size);

public:
    Industrialli_Modbus_RTU_Server(HardwareSerial *_serial);
    void begin();
    void end();

    void set_server_address(uint8_t _server_address);
    uint8_t get_server_address();
    
    void task();
};

#endif