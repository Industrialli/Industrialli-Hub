#include "industrialli_hub.hpp"

industrialli_hub hub;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetServer server(502);

void setup(){
	hub.begin();

    Ethernet.init();
    Ethernet.begin(mac);

    modbus_server.begin(&server);

    modbus_server.create_status_coil(0, 1);
    modbus_server.create_status_coil(1, 0);
    modbus_server.create_status_coil(2, 1);
    modbus_server.create_status_coil(3, 0);
    modbus_server.create_status_coil(4, 1);
    modbus_server.create_status_coil(5, 1);
    modbus_server.create_status_coil(6, 1);
    modbus_server.create_status_coil(7, 0);
    modbus_server.create_status_coil(8, 1);
    modbus_server.create_status_coil(9, 0);
    modbus_server.create_status_coil(10, 1);

    modbus_server.create_holding_register(0, 2000);
    modbus_server.create_holding_register(1, 2001);
    modbus_server.create_holding_register(2, 2002);
    modbus_server.create_holding_register(3, 2003);
    modbus_server.create_holding_register(4, 2004);
    modbus_server.create_holding_register(5, 2005);
    modbus_server.create_holding_register(6, 2006);
    modbus_server.create_holding_register(7, 2007);
    modbus_server.create_holding_register(8, 2008);
    modbus_server.create_holding_register(9, 2009);
    modbus_server.create_holding_register(10, 2010);
}

void loop(){
	modbus_server.task();
}