// #include "industrialli_hub.hpp"

// industrialli_hub hub;

// void setup(){
// 	hub.begin();

//     modbus_client.begin();
// }

// void loop(){
//     uint8_t v[8] = {0,1,1,1,0,1,0,1};
//     modbus_client.write_multiple_coils(10, 3, v, 8);
//     delay(100);

//     uint16_t v2[8] = {2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010};

//     modbus_client.write_multiple_registers(10, 3, v2, 8);
    
//     delay(500);
// }