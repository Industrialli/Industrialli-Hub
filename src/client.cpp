#include "industrialli_hub.hpp"

industrialli_hub hub;

void setup(){
	hub.begin();

    modbus_client.begin();

    modbus_client.create_status_coil(0, LOW);
    modbus_client.create_status_coil(1, LOW);
    modbus_client.create_status_coil(2, LOW);
    modbus_client.create_status_coil(3, LOW);
    modbus_client.create_status_coil(4, LOW);
    modbus_client.create_status_coil(5, LOW);
    modbus_client.create_status_coil(6, LOW);
    modbus_client.create_status_coil(7, LOW);
}

void loop(){
	modbus_client.read_coils(10, 0, 8);

    Serial.println(modbus_client.get_status_coil(0));
    Serial.println(modbus_client.get_status_coil(1));
    Serial.println(modbus_client.get_status_coil(2));
    Serial.println(modbus_client.get_status_coil(3));
    Serial.println(modbus_client.get_status_coil(4));
    Serial.println(modbus_client.get_status_coil(5));
    Serial.println(modbus_client.get_status_coil(6));
    Serial.println(modbus_client.get_status_coil(7));
    
    delay(500);
}