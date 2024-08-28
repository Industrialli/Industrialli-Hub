#include "industrialli_hub.hpp"

#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

uint8_t mac_address[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
EthernetClient client;

Adafruit_MQTT_Client mqtt(&client, , , , );
Adafruit_MQTT_Subscribe throttle  = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/throttle");
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt,  AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish counter     = Adafruit_MQTT_Publish(&mqtt,  AIO_USERNAME "/feeds/counter");

industrialli_hub hub;

void MQTT_connect();

void setup(){
	hub.begin();

    ethernet.begin();
    Ethernet.begin(mac_address);

    nextion.begin();
    nextion.writeNum("n0.val", 0);
    nextion.writeNum("x0.val", 0);
    nextion.writeNum("j0.val", 0);

    lora.begin(false);
	lora.setnetworkId((uint16_t)0);
	lora.config_bps(BW500, SF_LoRa_7, CR4_5);
	lora.config_class(LoRa_CLASS_C, LoRa_WINDOW_15s);
	lora.setpassword(22);
    
    mqtt.subscribe(&throttle);
}

void loop() {
     uint8_t payload_request[2] = {0,0};

    lora.PrepareFrameCommand(1, 0x05, payload_request, 2);
    lora.SendPacket();

    uint16_t id;
    uint8_t payload_response[MAX_PAYLOAD_SIZE];
    uint8_t cmd;
    uint8_t size;

    if(lora.ReceivePacketCommand(&id, &cmd, payload_response, &size, 10)){
        if(payload_response[0] != 0){
            double mA = payload_response[1] / 10.0;
            double temp = analog_input.map(mA, 4, 20, 0, 200);

            nextion.writeNum("n0.val", payload_response[0]);
            nextion.writeNum("x0.val", temp * 10);
            nextion.writeNum("j0.val", temp);

            MQTT_connect();

            Adafruit_MQTT_Subscribe *subscription;

            while((subscription = mqtt.readSubscription(5000))) {
                if(subscription == &throttle){
                    Serial.println((char *)throttle.lastread);
                }
            }

            temperature.publish(temp);
            delay(1500);
            counter.publish((uint32_t)payload_response[0]);

            if(!mqtt.ping()) {
                mqtt.disconnect();
            }
        }
    }

    leds.update();
}

void MQTT_connect() {
  int8_t ret;

  if(mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  while((ret = mqtt.connect()) != 0) {
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);
  }
  Serial.println("MQTT Connected!");
}