// #include "industrialli_hub.hpp"

// industrialli_hub hub;

// void setup(){
// 	hub.begin();

//     modbus_server.begin();
//     modbus_server.set_server_address(10);

//     modbus_server.create_status_coil(0, LOW);
//     modbus_server.create_status_coil(1, LOW);
//     modbus_server.create_status_coil(2, LOW);
//     modbus_server.create_status_coil(3, LOW);
//     modbus_server.create_status_coil(4, LOW);
//     modbus_server.create_status_coil(5, LOW);
//     modbus_server.create_status_coil(6, LOW);
//     modbus_server.create_status_coil(7, LOW);

//     digital_input.begin();
// }

// void loop(){
//     modbus_server.set_status_coil(0, digital_input.read(I01));
//     modbus_server.set_status_coil(1, digital_input.read(I02));
//     modbus_server.set_status_coil(2, digital_input.read(I03));
//     modbus_server.set_status_coil(3, digital_input.read(I04));
//     modbus_server.set_status_coil(4, digital_input.read(I05));
//     modbus_server.set_status_coil(5, digital_input.read(I06));
//     modbus_server.set_status_coil(6, digital_input.read(I07));
//     modbus_server.set_status_coil(7, digital_input.read(I08));

// 	modbus_server.task();

//     digital_input.update_leds();
//     leds.update();
// }