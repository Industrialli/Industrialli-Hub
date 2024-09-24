#ifndef INDUSTRIALLI_MODBUS_TCP_SERVER_H
#define INDUSTRIALLI_MODBUS_TCP_SERVER_H

#include <Ethernet2.h>
#include "industrialli_modbus_server.h"

class Industrialli_Modbus_TCP_Server : public Industrialli_Modbus_Server {
private:
    EthernetServer *server;

    uint8_t MBAP[7];

    bool receive_request(EthernetClient *_client);
    void process_request();

    void send_normal_response(EthernetClient *_client);

public:
    void begin(EthernetServer *_server);
    void end();

    void task();
};

#endif