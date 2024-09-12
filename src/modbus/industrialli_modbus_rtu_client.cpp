#include "modbus/industrialli_modbus_rtu_client.h"

void Industrialli_Modbus_RTU_Client::clear_rx_buffer(){
    unsigned long start_time = micros();
        
    do {
        if (serial->available()) {
            start_time = micros();
            serial->read();
        }
    }while (micros() - start_time < t35);
}

uint16_t Industrialli_Modbus_RTU_Client::crc(uint8_t _address, uint8_t *_adu, int _adu_size){
    uint8_t uchCRCHi = 0xFF;
    uint8_t uchCRCLo = 0xFF;
    uint8_t index;

    index   = uchCRCLo ^ _address;
    uchCRCLo = uchCRCHi ^ auchCRCHi[index];
    uchCRCHi = auchCRCLo[index];
    
    while(_adu_size--){
        index   = uchCRCLo ^ *_adu++;
        uchCRCLo = uchCRCHi ^ auchCRCHi[index];
        uchCRCHi = auchCRCLo[index];
    }

    return (uchCRCHi << 8 | uchCRCLo);
}

void Industrialli_Modbus_RTU_Client::send_request(uint8_t _address){
    digitalWrite(de_pin, HIGH);

    uint16_t pdu_crc = crc(_address, pdu, pdu_size);

    serial->write(_address);
    serial->write(pdu, pdu_size);
    serial->write(pdu_crc >> 8);
    serial->write(pdu_crc & 0xFF);
    serial->flush();

    delayMicroseconds(t35);

    digitalWrite(de_pin, LOW);
}

bool Industrialli_Modbus_RTU_Client::receive_response(){
    pdu_size = 0;
    unsigned long startTime = millis();

    while (!serial->available()) {
        if (millis() - startTime >= response_timeout) {
            return false;
        }
    }
    
    if(serial->available()){

        do{
            if (serial->available()) {
                startTime = micros();
                pdu[pdu_size++] = serial->read();
            }
        
        }while (micros() - startTime <= t15 && pdu_size < 256);

        while (micros() - startTime < t35);

        if(pdu_size == 0) return false;

        uint16_t crc_frame = (pdu[pdu_size - 2] << 8) | (pdu[pdu_size - 1]);

        if(crc_frame == crc(pdu[0], &pdu[1], pdu_size - 3)){
            pdu      = pdu + 1;
            pdu_size = pdu_size - 2;

            return true;
        }
    }
    
    return false;
}

void Industrialli_Modbus_RTU_Client::begin(HardwareSerial *_serial){
    pdu      = (uint8_t *)malloc(256);
    pdu_ptr  = pdu;
    pdu_size = 256;

    registers_head   = NULL;
    registers_last   = NULL;
    de_pin           = PD4;
    serial           = _serial;
    response_timeout = 100;
    last_exception_response = 0;

    pinMode(de_pin, OUTPUT);
    digitalWrite(de_pin, HIGH);

    t15 = 15000000/9600; 
    t35 = 35000000/9600;

    clear_rx_buffer();
}

void Industrialli_Modbus_RTU_Client::end(){
    free(pdu_ptr);
}

void Industrialli_Modbus_RTU_Client::read_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
    pdu[0] = FC_READ_COILS;
    pdu[1] = _starting_address >> 8;
    pdu[2] = _starting_address & 0xFF;
    pdu[3] = _quantity_of_coils >> 8;
    pdu[4] = _quantity_of_coils & 0xFF;

    pdu_size = 5;

    send_request(_address);

    if(receive_response()){
        if(is_exception_response(FC_READ_COILS)){
            last_exception_response = pdu[1];
        }else {
            process_response_read_coils(_starting_address, _quantity_of_coils);
        }
    }
}

void Industrialli_Modbus_RTU_Client::read_input_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
    pdu[0] = FC_READ_INPUT_COILS;
    pdu[1] = _starting_address >> 8;
    pdu[2] = _starting_address & 0xFF;
    pdu[3] = _quantity_of_coils >> 8;
    pdu[4] = _quantity_of_coils & 0xFF;

    pdu_size = 5;

    send_request(_address);
    
    if(receive_response()){
        if(is_exception_response(FC_READ_INPUT_COILS)){
            last_exception_response = pdu[1];
        }else {
            process_response_read_input_coils(_starting_address, _quantity_of_coils);
        }
    }
}

void Industrialli_Modbus_RTU_Client::read_holding_registers(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
    pdu[0] = FC_READ_HOLDING_REGISTERS;
    pdu[1] = _starting_address >> 8;
    pdu[2] = _starting_address & 0xFF;
    pdu[3] = _quantity_of_coils >> 8;
    pdu[4] = _quantity_of_coils & 0xFF;

    pdu_size = 5;

    send_request(_address);
    
    if(receive_response()){
        if(is_exception_response(FC_READ_HOLDING_REGISTERS)){
            last_exception_response = pdu[1];
        }else {
            process_response_read_holding_registers(_starting_address, _quantity_of_coils);
        }
    }
}

void Industrialli_Modbus_RTU_Client::read_input_registers(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
    pdu[0] = FC_READ_INPUT_REGISTERS;
    pdu[1] = _starting_address >> 8;
    pdu[2] = _starting_address & 0xFF;
    pdu[3] = _quantity_of_coils >> 8;
    pdu[4] = _quantity_of_coils & 0xFF;

    pdu_size = 5;

    send_request(_address);
    
    if(receive_response()){
        if(is_exception_response(FC_READ_INPUT_REGISTERS)){
            last_exception_response = pdu[1];
        }else {
            process_response_read_input_registers(_starting_address, _quantity_of_coils);
        }
    }
}

void Industrialli_Modbus_RTU_Client::write_single_coil(uint8_t _address, uint16_t _coil_address, uint16_t _value){
    pdu[0] = FC_WRITE_SINGLE_COIL;
    pdu[1] = _coil_address >> 8;
    pdu[2] = _coil_address & 0xFF;
    pdu[3] = _value >> 8;
    pdu[4] = _value & 0xFF;

    pdu_size = 5;

    send_request(_address);
    
    if(receive_response()){
        if(is_exception_response(FC_WRITE_SINGLE_COIL)){
            last_exception_response = pdu[1];
        }
    }
}

void Industrialli_Modbus_RTU_Client::write_single_register(uint8_t _address, uint16_t _register_address, uint16_t _value){
    pdu[0] = FC_WRITE_SINGLE_REGISTER;
    pdu[1] = _register_address >> 8;
    pdu[2] = _register_address & 0xFF;
    pdu[3] = _value >> 8;
    pdu[4] = _value & 0xFF;

    pdu_size = 5;

    send_request(_address);

    if(receive_response()){
        if(is_exception_response(FC_WRITE_SINGLE_REGISTER)){
            last_exception_response = pdu[1];
        }
    }
}

void Industrialli_Modbus_RTU_Client::write_multiple_coils(uint8_t _address, uint16_t _starting_address, uint8_t* _values, uint16_t _quantity_of_coils){
    pdu[0] = FC_WRITE_MULTIPLE_COILS;
    pdu[1] = _starting_address >> 8;
    pdu[2] = _starting_address & 0xFF;
    pdu[3] = _quantity_of_coils >> 8;
    pdu[4] = _quantity_of_coils & 0xFF;
    pdu[5] = ceil(_quantity_of_coils / 8.0);

    for (uint16_t i = 0; i < _quantity_of_coils; i++) {
        bitWrite(pdu[6 + (i >> 3)], i & 7, _values[i]);
    }

    for (uint16_t i = _quantity_of_coils; i < (pdu[6] * 8); i++) {
        bitClear(pdu[6 + (i >> 3)], i & 7);
    }

    uint16_t frame_crc = crc(_address, &frame[1], 6 + frame[6]);

    frame[7 + frame[6]] = frame_crc >> 8;
    frame[8 + frame[6]] = frame_crc & 0xFF;

    frame_size = 9 + frame[6];

    send_request();

    if(receive_response()){
        if(is_exception_response(FC_WRITE_MULTIPLE_COILS)){
            last_exception_response = frame[2];
        }
    }
}

void Industrialli_Modbus_RTU_Client::write_multiple_registers(uint8_t _address, uint16_t _starting_address, uint16_t* _values, uint16_t _quantity_of_registers){
    frame[0] = _address;
    frame[1] = FC_WRITE_MULTIPLE_REGISTERS;
    frame[2] = _starting_address >> 8;
    frame[3] = _starting_address & 0xFF;
    frame[4] = _quantity_of_registers >> 8;
    frame[5] = _quantity_of_registers & 0xFF;
    frame[6] = _quantity_of_registers * 2;

    for (int i = 0; i < _quantity_of_registers * 2; i += 2){
        frame[7 + i] = _values[i/2] >> 8;
        frame[8 + i] = _values[i/2] & 0xFF;
    }
    
    uint16_t frame_crc = crc(_address, &frame[1], 6 + frame[6]);

    frame[7 + frame[6]] = frame_crc >> 8;
    frame[8 + frame[6]] = frame_crc & 0xFF;

    frame_size = 9 + frame[6];

    send_request();

    if(receive_response()){
        if(is_exception_response(FC_WRITE_MULTIPLE_REGISTERS)){
            last_exception_response = frame[2];
        }
    }
}