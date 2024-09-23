#include "industrialli_hub.hpp"
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

industrialli_hub hub;
EthernetClient client_adafruit;
EthernetClient client;



uint8_t mac[]  = {0xDE, 0xAD, 0xBE, 0x68, 0x68, 0x6C};

void setup(){
	hub.begin();

    Ethernet.init();
    Ethernet.begin(mac);

    client.connect("172.16.82.40", 502);

    modbus_client.begin(&client);
    modbus_client.create_holding_register(121, 0);

    analog_input.begin();
    analog_input.set_read_mode(A01, READ_10V);
    analog_input.set_read_mode(A02, READ_10V);
}

void loop(){
    if(mqtt.connected()){
        modbus_client.write_single_register(121, 100);
        delay(5000);

        modbus_client.read_holding_registers(121, 1);
        hz.publish((double)modbus_client.get_holding_register(121)/10.0);
        
        modbus_client.write_single_register(121, 300);
        delay(5000);
        
        modbus_client.read_holding_registers(121, 1);
        hz.publish((double)modbus_client.get_holding_register(121)/10.0);
        
        modbus_client.write_single_register(121, 600);
        delay(5000);

        modbus_client.read_holding_registers(121, 1);
        hz.publish((double)modbus_client.get_holding_register(121)/10.0);

        delay(2000);
        temperature.publish(analog_input.map_pin(A01, 0, 10, -40, 80));
        delay(2000);
        vibration.publish(analog_input.map_pin(A02, 0, 10, 10, 1600));

    }else {
        while(mqtt.connect()) {
            mqtt.disconnect();
            delay(5000);
        }
    }

}