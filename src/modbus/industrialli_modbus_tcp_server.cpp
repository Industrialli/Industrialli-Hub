#include "modbus/industrialli_modbus_tcp_server.h"

bool Industrialli_Modbus_TCP_Server::receive_request(EthernetClient *_client){
    if(_client){
        if(_client->connected()){
            int i = 0;

            while(_client->available()){
                MBAP[i] = _client->read();
                i++;
                if (i==7) break;
            }

            clear_pdu();
            pdu_size =  (MBAP[4] << 8 | MBAP[5]) - 1;

            if(MBAP[2] != 0 || MBAP[3] != 0) return false;
            if(pdu_size > 200) return false;

            i = 0;
            while(_client->available()){
                pdu[i++] = _client->read();
                if (i == pdu_size) break;
            }

            return true;
        }
    }

    return false;
}

void Industrialli_Modbus_TCP_Server::process_request(){
    uint8_t function = pdu[0];
    uint16_t field_1 = (pdu[1] << 8) | pdu[2];
    uint16_t field_2 = (pdu[3] << 8) | pdu[4];
   
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
    }
}

void Industrialli_Modbus_TCP_Server::send_normal_response(EthernetClient *_client){
    MBAP[4] = (pdu_size + 1) >> 8;  
    MBAP[5] = (pdu_size + 1) & 0x00FF;

    _client->write(MBAP, 7);
    _client->write(pdu, pdu_size);

    _client->flush();
    // _client->stop();
}

void Industrialli_Modbus_TCP_Server::begin(EthernetServer *_server){
    pdu      = (uint8_t *)malloc(256);
    pdu_ptr  = pdu;
    pdu_size = 256;

    registers_head = NULL;
    registers_last = NULL;

    server = _server;
}

void Industrialli_Modbus_TCP_Server::task(){
    EthernetClient client = server->available();

    if(receive_request(&client)){
        process_request();

        if(pdu_reply_type == R_REPLY_NORMAL){
            send_normal_response(&client);
        }
    }
}