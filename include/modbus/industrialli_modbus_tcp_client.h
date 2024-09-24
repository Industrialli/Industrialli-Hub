#ifndef INDUSTRIALLI_MODBUS_TCP_CLIENT_H
#define INDUSTRIALLI_MODBUS_TCP_CLIENT_H

#include <Ethernet2.h>
#include "industrialli_modbus_client.h"

class Industrialli_Modbus_TCP_Client : public Industrialli_Modbus_Client {
private:
    EthernetClient *client;

    uint32_t response_timeout;
    uint16_t transaction_id; 

    uint8_t MBAP[7];

    void send_request();
    bool receive_response();

public:
    void begin(EthernetClient *_client);
    void end();

    void read_coils(uint16_t _starting_address, uint16_t _quantity_of_coils);
    void read_input_coils(uint16_t _starting_address, uint16_t _quantity_of_coils);
    void read_holding_registers(uint16_t _starting_address, uint16_t _quantity_of_registers);
    void read_input_registers(uint16_t _starting_address, uint16_t _quantity_of_registers);
    void write_single_coil(uint16_t _coil_address, bool _value);
    void write_single_register(uint16_t _register_address, uint16_t _value);
    void write_multiple_coils(uint16_t _starting_address, uint8_t* _values, uint16_t _quantity_of_coils);
    void write_multiple_registers(uint16_t _starting_address, uint16_t* _values, uint16_t _quantity_of_registers);
};

#endif