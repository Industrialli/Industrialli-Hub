#include "modbus/industrialli_modbus_tcp_client.h"

void Industrialli_Modbus_TCP_Client::send_request(){
    MBAP[4] = (pdu_size + 1) >> 8;  
    MBAP[5] = (pdu_size + 1) & 0xFF;

    uint8_t adu[7 + pdu_size];
    
    for(int i = 0; i < 7; i++){
        adu[i] = MBAP[i];
    }

    for(int i = 0; i < pdu_size; i++){
        adu[i + 7] = pdu[i];
    }

    client->write(adu, 7 + pdu_size);
    client->flush();
}

bool Industrialli_Modbus_TCP_Client::receive_response(){
    clear_pdu();

    if(client->available()){
        if(client->connected()){
            int i = 0;

            while(client->available()){
                MBAP[i] = client->read();
                i++;
                if (i==7) break;
            }

            clear_pdu();
            pdu_size =  (MBAP[4] << 8 | MBAP[5]) - 1;

            if(MBAP[2] != 0 || MBAP[3] != 0) return false;
            if(pdu_size > 200) return false;

            i = 0;
            while(client->available()){
                pdu[i++] = client->read();
                if (i == pdu_size) break;
            }

            return true;
        }
    }

    return false;
}

void Industrialli_Modbus_TCP_Client::begin(EthernetClient *_client){
    pdu      = (uint8_t *)malloc(256);
    pdu_ptr  = pdu;
    pdu_size = 256;

    registers_head   = NULL;
    registers_last   = NULL;
    response_timeout = 100;
    transaction_id   = 0;
    last_exception_response = 0;

    client = _client;
}

void Industrialli_Modbus_TCP_Client::end(){
    free(pdu_ptr);
    free_registers();
}

void Industrialli_Modbus_TCP_Client::read_coils(uint16_t _starting_address, uint16_t _quantity_of_coils){
    if(transaction_id + 1 == 0xFFFF){
        transaction_id = 0;
    }else {
        transaction_id++;
    }
    
    MBAP[0] = transaction_id >> 8;
    MBAP[1] = transaction_id & 0xFF;
    MBAP[2] = 0x00;
    MBAP[3] = 0x00;
    MBAP[6] = 0xFF;

    pdu[0] = FC_READ_COILS;
    pdu[1] = _starting_address >> 8;
    pdu[2] = _starting_address & 0xFF;
    pdu[3] = _quantity_of_coils >> 8;
    pdu[4] = _quantity_of_coils & 0xFF;

    pdu_size = 5;

    send_request();

    if(receive_response()){
         if(is_exception_response(FC_READ_COILS)){
            last_exception_response = pdu[1];
        }else {
            process_response_read_coils(_starting_address, _quantity_of_coils);
        }
    }
}

void Industrialli_Modbus_TCP_Client::read_input_coils(uint16_t _starting_address, uint16_t _quantity_of_coils){
    if(transaction_id + 1 == 0xFFFF){
        transaction_id = 0;
    }else {
        transaction_id++;
    }
    
    MBAP[0] = transaction_id >> 8;
    MBAP[1] = transaction_id & 0xFF;
    MBAP[2] = 0x00;
    MBAP[3] = 0x00;
    MBAP[6] = 0xFF;

    pdu[0] = FC_READ_INPUT_COILS;
    pdu[1] = _starting_address >> 8;
    pdu[2] = _starting_address & 0xFF;
    pdu[3] = _quantity_of_coils >> 8;
    pdu[4] = _quantity_of_coils & 0xFF;

    pdu_size = 5;

    send_request();

    if(receive_response()){
         if(is_exception_response(FC_READ_INPUT_COILS)){
            last_exception_response = pdu[1];
        }else {
            process_response_read_input_coils(_starting_address, _quantity_of_coils);
        }
    }
}

void Industrialli_Modbus_TCP_Client::read_holding_registers(uint16_t _starting_address, uint16_t _quantity_of_registers){
    if(transaction_id + 1 == 0xFFFF){
        transaction_id = 0;
    }else {
        transaction_id++;
    }
    
    MBAP[0] = transaction_id >> 8;
    MBAP[1] = transaction_id & 0xFF;
    MBAP[2] = 0x00;
    MBAP[3] = 0x00;
    MBAP[6] = 0xFF;

    pdu[0] = FC_READ_HOLDING_REGISTERS;
    pdu[1] = _starting_address >> 8;
    pdu[2] = _starting_address & 0xFF;
    pdu[3] = _quantity_of_registers >> 8;
    pdu[4] = _quantity_of_registers & 0xFF;

    pdu_size = 5;

    send_request();

    if(receive_response()){
         if(is_exception_response(FC_READ_HOLDING_REGISTERS)){
            last_exception_response = pdu[1];
        }else {
            process_response_read_holding_registers(_starting_address, _quantity_of_registers);
        }
    }
}

void Industrialli_Modbus_TCP_Client::read_input_registers(uint16_t _starting_address, uint16_t _quantity_of_registers){
    if(transaction_id + 1 == 0xFFFF){
        transaction_id = 0;
    }else {
        transaction_id++;
    }
    
    MBAP[0] = transaction_id >> 8;
    MBAP[1] = transaction_id & 0xFF;
    MBAP[2] = 0x00;
    MBAP[3] = 0x00;
    MBAP[6] = 0xFF;

    pdu[0] = FC_READ_INPUT_REGISTERS;
    pdu[1] = _starting_address >> 8;
    pdu[2] = _starting_address & 0xFF;
    pdu[3] = _quantity_of_registers >> 8;
    pdu[4] = _quantity_of_registers & 0xFF;

    pdu_size = 5;

    send_request();

    if(receive_response()){
         if(is_exception_response(FC_READ_INPUT_REGISTERS)){
            last_exception_response = pdu[1];
        }else {
            process_response_read_input_registers(_starting_address, _quantity_of_registers);
        }
    }
}

void Industrialli_Modbus_TCP_Client::write_single_coil(uint16_t _coil_address, bool _value){
    if(transaction_id + 1 == 0xFFFF){
        transaction_id = 0;
    }else {
        transaction_id++;
    }
    
    MBAP[0] = transaction_id >> 8;
    MBAP[1] = transaction_id & 0xFF;
    MBAP[2] = 0x00;
    MBAP[3] = 0x00;
    MBAP[6] = 0xFF;

    pdu[0] = FC_WRITE_SINGLE_COIL;
    pdu[1] = _coil_address >> 8;
    pdu[2] = _coil_address & 0xFF;

    if(_value){
        pdu[3] = 0xFF;
        pdu[4] = 0x00;

    }else {
        pdu[3] = 0x00;
        pdu[4] = 0x00;
    }

    pdu_size = 5;

    send_request();

    if(receive_response()){
         if(is_exception_response(FC_WRITE_SINGLE_COIL)){
            last_exception_response = pdu[1];
        }
    }
}

void Industrialli_Modbus_TCP_Client::write_single_register(uint16_t _register_address, uint16_t _value){
    if(transaction_id + 1 == 0xFFFF){
        transaction_id = 0;
    }else {
        transaction_id++;
    }
    
    MBAP[0] = transaction_id >> 8;
    MBAP[1] = transaction_id & 0xFF;
    MBAP[2] = 0x00;
    MBAP[3] = 0x00;
    MBAP[6] = 0xFF;

    pdu[0] = FC_WRITE_SINGLE_REGISTER;
    pdu[1] = _register_address >> 8;
    pdu[2] = _register_address & 0xFF;
    pdu[3] = _value >> 8;
    pdu[4] = _value & 0xFF;

    pdu_size = 5;

    send_request();

    if(receive_response()){
         if(is_exception_response(FC_WRITE_SINGLE_REGISTER)){
            last_exception_response = pdu[1];
        }
    }
}

void Industrialli_Modbus_TCP_Client::write_multiple_coils(uint16_t _starting_address, uint8_t* _values, uint16_t _quantity_of_coils){
    if(transaction_id + 1 == 0xFFFF){
        transaction_id = 0;
    }else {
        transaction_id++;
    }
    
    MBAP[0] = transaction_id >> 8;
    MBAP[1] = transaction_id & 0xFF;
    MBAP[2] = 0x00;
    MBAP[3] = 0x00;
    MBAP[6] = 0xFF;

    pdu[0] = FC_WRITE_MULTIPLE_COILS;
    pdu[1] = _starting_address >> 8;
    pdu[2] = _starting_address & 0xFF;
    pdu[3] = _quantity_of_coils >> 8;
    pdu[4] = _quantity_of_coils & 0xFF;
    pdu[5] = ceil(_quantity_of_coils / 8.0);

    for (uint16_t i = 0; i < _quantity_of_coils; i++) {
        bitWrite(pdu[6 + (i >> 3)], i & 7, _values[i]);
    }

    for (uint16_t i = _quantity_of_coils; i < (pdu[5] * 8); i++) {
        bitClear(pdu[6 + (i >> 3)], i & 7);
    }

    pdu_size = 6 + pdu[5];

    send_request();

    if(receive_response()){
         if(is_exception_response(FC_WRITE_MULTIPLE_COILS)){
            last_exception_response = pdu[1];
        }
    }
}

void Industrialli_Modbus_TCP_Client::write_multiple_registers(uint16_t _starting_address, uint16_t* _values, uint16_t _quantity_of_registers){
    if(transaction_id + 1 == 0xFFFF){
        transaction_id = 0;
    }else {
        transaction_id++;
    }
    
    MBAP[0] = transaction_id >> 8;
    MBAP[1] = transaction_id & 0xFF;
    MBAP[2] = 0x00;
    MBAP[3] = 0x00;
    MBAP[6] = 0xFF;

    pdu[0] = FC_WRITE_MULTIPLE_REGISTERS;
    pdu[1] = _starting_address >> 8;
    pdu[2] = _starting_address & 0xFF;
    pdu[3] = _quantity_of_registers >> 8;
    pdu[4] = _quantity_of_registers & 0xFF;
    pdu[5] = _quantity_of_registers * 2;

    for (int i = 0; i < _quantity_of_registers * 2; i += 2){
        pdu[6 + i] = _values[i/2] >> 8;
        pdu[7 + i] = _values[i/2] & 0xFF;
    }

    pdu_size = 6 + pdu[5];

    send_request();

    if(receive_response()){
         if(is_exception_response(FC_WRITE_MULTIPLE_REGISTERS)){
            last_exception_response = pdu[1];
        }
    }
}