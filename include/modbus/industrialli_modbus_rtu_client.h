#ifndef INDUSTRIALLI_MODBUS_RTU_CLIENT_H
#define INDUSTRIALLI_MODBUS_RTU_CLIENT_H

#include <HardwareSerial.h>
#include "modbus/industrialli_modbus_client.h"

class Industrialli_Modbus_RTU_Client : public Industrialli_Modbus_Client {
private:
    HardwareSerial *serial;
    uint32_t t15;
    uint32_t t35;
    uint32_t response_timeout;

    uint32_t de_pin;

    uint8_t pdu[256];
    uint8_t pdu_size;

    void clear_rx_buffer();
    uint16_t crc(uint8_t _address, uint8_t *_adu, int _adu_size);

    void create_pdu_read_coils(uint8_t _address);
    void create_pdu_read_input_coils();
    void create_pdu_read_holding_registers();
    void create_pdu_read_input_registers();
    void create_pdu_write_single_coil();
    void create_pdu_write_single_register();
    void create_pdu_write_multiple_coils();
    void create_pdu_write_multiple_registers();

    void process_pdu_read_coils();

    void send_request();
    bool receive_response();

public:
    void begin(HardwareSerial *_serial);

    void read_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils);

};

#endif