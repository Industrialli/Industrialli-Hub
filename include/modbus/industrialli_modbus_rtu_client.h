#ifndef INDUSTRIALLI_MODBUS_RTU_CLIENT_H
#define INDUSTRIALLI_MODBUS_RTU_CLIENT_H

#include <HardwareSerial.h>
#include "industrialli_modbus_client.h"

class Industrialli_Modbus_RTU_Client : public Industrialli_Modbus_Client {
private:
    HardwareSerial *serial;

    uint32_t t15;
    uint32_t t35;
    uint32_t de_pin;
    uint32_t response_timeout;
    
    void clear_rx_buffer();
    uint16_t crc(uint8_t _address, uint8_t *_pdu, uint8_t _pdu_size);

    void send_request(uint8_t _address);
    bool receive_response();

public:
    Industrialli_Modbus_RTU_Client(HardwareSerial *_serial);
    void begin();
    void end();

    void read_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils);
    void read_input_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils);
    void read_holding_registers(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_registers);
    void read_input_registers(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_registers);
    void write_single_coil(uint8_t _address, uint16_t _coil_address, bool _value);
    void write_single_register(uint8_t _address, uint16_t _register_address, uint16_t _value);
    void write_multiple_coils(uint8_t _address, uint16_t _starting_address, uint8_t* _values, uint16_t _quantity_of_coils);
    void write_multiple_registers(uint8_t _address, uint16_t _starting_address, uint16_t* _values, uint16_t _quantity_of_registers);
};

#endif