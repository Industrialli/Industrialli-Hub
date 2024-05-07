#ifndef INDUSTRIALLI_MODBUS_H
#define INDUSTRIALLI_MODBUS_H

#include <cstdint>

typedef struct Register {
    uint16_t address;
    uint16_t value;
    struct Register* next;
} Register;

class Industrialli_Modbus{
protected:
    Register *registers_head;
    Register *registers_last;

    void create_register(uint16_t _address, uint16_t _value);
    void set_register(uint16_t _address, uint16_t _value);
    uint16_t get_register(uint16_t _address);
    Register* search_register(uint16_t _address);

public:
    void create_status_coil(uint16_t _address, bool _value);
    void create_input_coil(uint16_t _address, bool _value);
    void create_input_register(uint16_t _address, uint16_t _value);
    void create_holding_register(uint16_t _address, uint16_t _value);

    void set_status_coil(uint16_t _address, bool _value);
    void set_input_coil(uint16_t _address, bool _value);
    void set_input_register(uint16_t _address, uint16_t _value);
    void set_holding_register(uint16_t _address, uint16_t _value);

    bool get_status_coil(uint16_t _address);
    bool get_input_coil(uint16_t _address);
    uint16_t get_input_register(uint16_t _address);
    uint16_t get_holding_register(uint16_t _address);
};

#endif