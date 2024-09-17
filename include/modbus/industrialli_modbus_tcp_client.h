#ifndef INDUSTRIALLI_MODBUS_TCP_CLIENT_H
#define INDUSTRIALLI_MODBUS_TCP_CLIENT_H

#include <Ethernet2.h>
#include "industrialli_modbus_client.h"

class Industrialli_Modbus_TCP_Client : public Industrialli_Modbus_Client {
private:
    EthernetClient *client;

    uint32_t response_timeout;

    uint8_t MBAP[7];

    void send_request();
    bool receive_response();//~ok

public:
    void begin(EthernetClient *_client);

    void read_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils);//~ok
    void read_input_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils);//~ok
    void read_holding_registers(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_registers);//~ok
    void read_input_registers(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_registers);//~ok
    void write_single_coil(uint8_t _address, uint16_t _coil_address, bool _value);
    void write_single_register(uint8_t _address, uint16_t _register_address, uint16_t _value);
    void write_multiple_coils(uint8_t _address, uint16_t _starting_address, uint8_t* _values, uint16_t _quantity_of_coils);
    void write_multiple_registers(uint8_t _address, uint16_t _starting_address, uint16_t* _values, uint16_t _quantity_of_registers);
};

#endif