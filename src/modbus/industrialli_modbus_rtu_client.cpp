#include "modbus/industrialli_modbus_rtu_client.h"

void Industrialli_Modbus_RTU_Client::create_pdu_read_coils(uint8_t _address){
    pdu[0] = _address;
    pdu[1] = adu[0];
    pdu[2] = adu[1];
    pdu[3] = adu[2];
    pdu[4] = adu[3];
    pdu[5] = adu[4];

    uint16_t adu_crc = crc(_address, adu, 5);

    pdu[6] = adu_crc >> 8;
    pdu[7] = adu_crc & 0xFF;

    pdu_size = 8;
};

void Industrialli_Modbus_RTU_Client::process_pdu_read_coils(){
    adu = pdu;
}

void Industrialli_Modbus_RTU_Client::read_coils(uint8_t _address, uint16_t _starting_address, uint16_t _quantity_of_coils){
    create_adu_read_coils(_address, _starting_address, _quantity_of_coils);
    create_pdu_read_coils(_address);

    send_request();

    if(receive_response()){
        if(is_exception_response(FC_READ_COILS)){
            last_exception_response = pdu[2];
        }else {
            process_adu_read_coils(_starting_address, _quantity_of_coils);
        }
    }
}

void Industrialli_Modbus_RTU_Client::send_request(){
    digitalWrite(de_pin, HIGH);
    delay(1);

    serial->write(pdu, pdu_size);
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
            return true;
        }
    }
    
    return false;
}

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

void Industrialli_Modbus_RTU_Client::begin(HardwareSerial *_serial){
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