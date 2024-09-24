#include <cstdlib>
#include "modbus/industrialli_modbus.h"

void Industrialli_Modbus::create_register(uint16_t address, uint16_t value){
    Register *new_register;

	new_register = (Register *) malloc(sizeof(Register));
	new_register->address = address;
	new_register->value	  = value;
	new_register->next	  = NULL;

	if(registers_head == NULL) {
        registers_head = new_register;
        registers_last = registers_head;
    } else {
        registers_last->next = new_register;
        registers_last = new_register;
    }
}

void Industrialli_Modbus::free_registers(){
    while(registers_head != NULL){
        Register *to_delete = registers_head;
        registers_head = registers_head->next;

        free(to_delete);
    }
}

void Industrialli_Modbus::set_register(uint16_t _address, uint16_t _value){
    Register *reg = search_register(_address);
    reg->value = _value;
}

uint16_t Industrialli_Modbus::get_register(uint16_t _address){
    Register *reg = search_register(_address);
    return reg->value;
}

Register* Industrialli_Modbus::search_register(uint16_t address){
    Register *registers = registers_head;

    if(registers == NULL){
        return NULL;
    }
    
    do {
        if (registers->address == address){
            return registers;
        }
        
        registers = registers->next;
        
	} while(registers != NULL);
	
    return NULL;
}

void Industrialli_Modbus::create_status_coil(uint16_t _address, bool _value){
    create_register(_address + 1, _value);
}

void Industrialli_Modbus::create_input_coil(uint16_t _address, bool _value){
    create_register(_address + 10001, _value);
}

void Industrialli_Modbus::create_input_register(uint16_t _address, uint16_t _value){
    create_register(_address + 30001, _value);
}

void Industrialli_Modbus::create_holding_register(uint16_t _address, uint16_t _value){
    create_register(_address + 40001, _value);
}

void Industrialli_Modbus::set_status_coil(uint16_t _address, bool _value){
    set_register(_address + 1, _value);
}

void Industrialli_Modbus::set_input_coil(uint16_t _address, bool _value){
    set_register(_address + 10001, _value);
}

void Industrialli_Modbus::set_input_register(uint16_t _address, uint16_t _value){
    set_register(_address + 30001, _value);
}

void Industrialli_Modbus::set_holding_register(uint16_t _address, uint16_t _value){
    set_register(_address + 40001, _value);
}

bool Industrialli_Modbus::get_status_coil(uint16_t _address){
    return get_register(_address + 1);
}

bool Industrialli_Modbus::get_input_coil(uint16_t _address){
    return get_register(_address + 10001);
}

uint16_t Industrialli_Modbus::get_input_register(uint16_t _address){
    return get_register(_address + 30001);
}

uint16_t Industrialli_Modbus::get_holding_register(uint16_t _address){
    return get_register(_address + 40001);
}