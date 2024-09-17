// #include "industrialli_hub.hpp"

// industrialli_hub hub;

// byte mac[]    = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// IPAddress ip  = {172, 16, 83, 205};
// IPAddress subnet_mask = {255, 255, 252, 0};

// EthernetServer server(502);

// void setup(){
// 	hub.begin();

//     Ethernet.init();
//     Ethernet.begin(mac, ip, subnet_mask);

//     modbus_server.begin(&server);

//     modbus_server.create_status_coil(0, LOW);
//     modbus_server.create_status_coil(1, LOW);
//     modbus_server.create_status_coil(2, LOW);
//     modbus_server.create_status_coil(3, LOW);
//     modbus_server.create_status_coil(4, LOW);
//     modbus_server.create_status_coil(5, LOW);
//     modbus_server.create_status_coil(6, LOW);
//     modbus_server.create_status_coil(7, LOW);
//     modbus_server.create_status_coil(8, LOW);
//     modbus_server.create_status_coil(9, LOW);
//     modbus_server.create_status_coil(10, LOW);

//     modbus_server.create_holding_register(0, 0);
//     modbus_server.create_holding_register(1, 0);
//     modbus_server.create_holding_register(2, 0);
//     modbus_server.create_holding_register(3, 0);
//     modbus_server.create_holding_register(4, 0);
//     modbus_server.create_holding_register(5, 0);
//     modbus_server.create_holding_register(6, 0);
//     modbus_server.create_holding_register(7, 0);
//     modbus_server.create_holding_register(8, 0);
//     modbus_server.create_holding_register(9, 0);
//     modbus_server.create_holding_register(10, 0);
// }

// void loop(){
// 	modbus_server.task();

//     Serial.println(modbus_server.get_status_coil(0));
//     Serial.println(modbus_server.get_status_coil(1));
//     Serial.println(modbus_server.get_status_coil(2));
//     Serial.println(modbus_server.get_status_coil(3));
//     Serial.println(modbus_server.get_status_coil(4));
//     Serial.println(modbus_server.get_status_coil(5));
//     Serial.println(modbus_server.get_status_coil(6));
//     Serial.println(modbus_server.get_status_coil(7));
//     Serial.println(modbus_server.get_status_coil(8));
//     Serial.println(modbus_server.get_status_coil(9));
//     Serial.println(modbus_server.get_status_coil(10));

//     Serial.println(modbus_server.get_holding_register(0));
//     Serial.println(modbus_server.get_holding_register(1));
//     Serial.println(modbus_server.get_holding_register(2));
//     Serial.println(modbus_server.get_holding_register(3));
//     Serial.println(modbus_server.get_holding_register(4));
//     Serial.println(modbus_server.get_holding_register(5));
//     Serial.println(modbus_server.get_holding_register(6));
//     Serial.println(modbus_server.get_holding_register(7));
//     Serial.println(modbus_server.get_holding_register(8));
//     Serial.println(modbus_server.get_holding_register(9));
//     Serial.println(modbus_server.get_holding_register(10));

//     Serial.println("######################################");
// }