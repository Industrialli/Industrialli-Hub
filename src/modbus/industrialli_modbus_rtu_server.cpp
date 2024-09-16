#include "modbus/industrialli_modbus_rtu_server.h"

bool Industrialli_Modbus_RTU_Server::receive_request(){
    clear_pdu();
    unsigned long startTime = 0;
    
    if(serial->available()){
        do{
            if (serial->available()) {
                startTime = micros();
                pdu[pdu_size++] = serial->read();
            }
        
        }while (micros() - startTime <= t15 && pdu_size < 256);
        
        while (micros() - startTime < t35);

        if(pdu_size == 0) return false;

        uint16_t expected_crc   = (pdu[pdu_size - 2] << 8) | (pdu[pdu_size - 1]);
        uint16_t calculated_crc = crc(pdu[0], &pdu[1], pdu_size - 3);

        if(expected_crc == calculated_crc && (pdu[0] == get_server_address() || pdu[0] == 0x00)){
            return true;
        }
    }
    
    return false;
}

void Industrialli_Modbus_RTU_Server::process_request(){
    uint8_t _address = pdu[0];
    uint8_t function = pdu[1];
    uint16_t field_1 = (pdu[2] << 8) | pdu[3];
    uint16_t field_2 = (pdu[4] << 8) | pdu[5];

    pdu      = pdu + 1;
    pdu_size = pdu_size - 3;
   
    switch (function){
        case FC_READ_COILS:
            process_request_read_coils(field_1, field_2);
            break;

        case FC_READ_INPUT_COILS:
            process_request_read_input_coils(field_1, field_2);
            break;

        case FC_READ_HOLDING_REGISTERS:
            process_request_read_holding_registers(field_1, field_2);
            break;

        case FC_READ_INPUT_REGISTERS:
            process_request_read_input_registers(field_1, field_2);
            break;

        case FC_WRITE_SINGLE_COIL:
            process_request_write_single_coil(field_1, field_2);
            break;

        case FC_WRITE_SINGLE_REGISTER:
            process_request_write_single_register(field_1, field_2);
            break;

        case FC_WRITE_MULTIPLE_COILS:
            process_request_write_multiple_coils(pdu, field_1, field_2);
            break;

        case FC_WRITE_MULTIPLE_REGISTERS:
            process_request_write_multiple_registers(pdu, field_1, field_2);
            break;
            
        default:
            exception_response(_address, EX_ILLEGAL_FUNCTION);
            break;
    }
}

void Industrialli_Modbus_RTU_Server::send_normal_response(){
    digitalWrite(de_pin, HIGH);

    uint16_t crc_value = crc(get_server_address(), pdu, pdu_size);
        
    serial->write(get_server_address());
    serial->write(pdu, pdu_size);
    serial->write(crc_value >> 8);
    serial->write(crc_value & 0xFF);

    serial->flush();

    delayMicroseconds(t35);

    digitalWrite(de_pin, LOW);
}

void Industrialli_Modbus_RTU_Server::send_echo_response(){
    digitalWrite(de_pin, HIGH);

    serial->write(pdu, pdu_size);
    serial->flush();

    delayMicroseconds(t35);

    digitalWrite(de_pin, LOW);
}

void Industrialli_Modbus_RTU_Server::clear_rx_buffer(){
    unsigned long start_time = micros();
        
    do {
        if (serial->available()) {
            start_time = micros();
            serial->read();
        }
    }while (micros() - start_time < t35);
}

uint16_t Industrialli_Modbus_RTU_Server::crc(uint8_t _address, uint8_t *_pdu, int _pdu_size){
    uint8_t uchCRCHi = 0xFF;
    uint8_t uchCRCLo = 0xFF;
    uint8_t index;

    index   = uchCRCLo ^ _address;
    uchCRCLo = uchCRCHi ^ auchCRCHi[index];
    uchCRCHi = auchCRCLo[index];
    
    while(_pdu_size--){
        index   = uchCRCLo ^ *_pdu++;
        uchCRCLo = uchCRCHi ^ auchCRCHi[index];
        uchCRCHi = auchCRCLo[index];
    }

    return (uchCRCHi << 8 | uchCRCLo);
}

Industrialli_Modbus_RTU_Server::Industrialli_Modbus_RTU_Server(HardwareSerial *_serial){
    serial = _serial;
}

void Industrialli_Modbus_RTU_Server::begin(){
    pdu      = (uint8_t *)malloc(256);
    pdu_ptr  = pdu;
    pdu_size = 256;

    registers_head = NULL;
    registers_last = NULL;
    de_pin         = PD4;

    pinMode(de_pin, OUTPUT);
    digitalWrite(de_pin, LOW);

    t15 = 15000000/9600; 
    t35 = 35000000/9600;

    clear_rx_buffer();
}

void Industrialli_Modbus_RTU_Server::set_server_address(uint8_t _server_address){
    server_address = _server_address;
}

uint8_t Industrialli_Modbus_RTU_Server::get_server_address(){
    return server_address;
}

void Industrialli_Modbus_RTU_Server::task(){
    if(receive_request()){
        process_request();

        if(pdu_reply_type == R_REPLY_NORMAL){
            send_normal_response();
        }

        if(pdu_reply_type == R_REPLY_ECHO){
            send_echo_response();
        }
    }
}