// #include "industrialli_hub.hpp"

// #include <Adafruit_MQTT.h>
// #include <Adafruit_MQTT_Client.h>

// #define AIO_SERVER      "io.adafruit.com"
// #define AIO_SERVERPORT  1883
// #define AIO_USERNAME    "opallace"
// #define AIO_KEY         "aio_nYnX78rnCd3h025W6nC5hXiTR0mU"

// uint8_t mac_address[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// EthernetClient client;

// Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
// Adafruit_MQTT_Subscribe throttle  = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/throttle");
// Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt,  AIO_USERNAME "/feeds/temperature");
// Adafruit_MQTT_Publish counter     = Adafruit_MQTT_Publish(&mqtt,  AIO_USERNAME "/feeds/counter");

// industrialli_hub hub;

// uint8_t payload[MAX_PAYLOAD_SIZE];

// void nextion_task(void *p);
// void leds_task(void *p);
// void ethernet_task(void *p);
// void lora_task(void *p);
// void semaphore_task(void *p);

// void MQTT_connect();

// void setup(){
// 	hub.begin();

//     ethernet.begin();
//     Ethernet.begin(mac_address);

//     nextion.begin();
//     nextion.writeNum("n0.val", 0);
//     nextion.writeNum("x0.val", 0);
//     nextion.writeNum("j0.val", 0);

//     digital_output.begin();
//     digital_output.enable();
//     digital_output.update_power_leds_status();

//     lora.begin(false);
// 	lora.setnetworkId(0);
// 	lora.config_bps(BW500, SF_LoRa_7, CR4_5);
// 	lora.config_class(LoRa_CLASS_C, LoRa_WINDOW_15s);
// 	lora.setpassword(22);
    
//     mqtt.subscribe(&throttle);

//     xTaskCreate(lora_task, "lora_task", 2048, NULL, 2, NULL);
//     xTaskCreate(nextion_task, "nextion_task", 2048, NULL, 1, NULL);
//     xTaskCreate(leds_task, "leds_task", 2048, NULL, 0, NULL);
//     xTaskCreate(ethernet_task, "ethernet_task", 2048, NULL, 0, NULL);
//     xTaskCreate(semaphore_task, "semaphore_task", 2048, NULL, 0, NULL);

//     vTaskStartScheduler();
// }

// void loop() {}

// void MQTT_connect() {
//   int8_t ret;

//   if(mqtt.connected()) {
//     return;
//   }

//   Serial.print("Connecting to MQTT... ");

//   while((ret = mqtt.connect()) != 0) {
//        Serial.println(mqtt.connectErrorString(ret));
//        Serial.println("Retrying MQTT connection in 5 seconds...");
//        mqtt.disconnect();
//        delay(5000);
//   }
//   Serial.println("MQTT Connected!");
// }

// void nextion_task(void *p){
//     while(1){
//         float temp = payload[1] / 10.0;
//         float tempSensor0150C = (((temp - 4.00) / (16.0)) * 200.00) * 10;

//         nextion.writeNum("n0.val", payload[0]);
//         nextion.writeNum("x0.val", tempSensor0150C);
//         nextion.writeNum("j0.val", (int)(tempSensor0150C / 10));
        
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//     }
    
// }

// void leds_task(void *p){
//     while (1){
//         digital_output.update();
// 	    leds.update();
//         vTaskDelay(10 / portTICK_PERIOD_MS);
//     }
// }

// void ethernet_task(void *p){
//     while(1){
//         MQTT_connect();

//         Adafruit_MQTT_Subscribe *subscription;

//         while((subscription = mqtt.readSubscription(5000))) {
//             if(subscription == &throttle){
//                 Serial.println((char *)throttle.lastread);
//             }
//         }

//         temperature.publish((float)((((((payload[1] / 10.0) - 4.00) / (16.0)) * 200.00) * 10) / 10));
//         vTaskDelay(1500 / portTICK_PERIOD_MS);
//         counter.publish((uint32_t)payload[0]);

//         if(!mqtt.ping()) {
//             mqtt.disconnect();
//         }

//         vTaskDelay(1500 / portTICK_PERIOD_MS);
//     }
// }

// void lora_task(void *p){
//     while(1){
        
//         uint8_t payload_request[2] = {0,0};

//         lora.PrepareFrameCommand(1, 0x05, payload_request, 2);
//         lora.SendPacket();

//         uint16_t id;
//         uint8_t payload_response[MAX_PAYLOAD_SIZE];
//         uint8_t cmd;
//         uint8_t size;

//         if(lora.ReceivePacketCommand(&id, &cmd, payload_response, &size, 10)){
//             if(payload_response[0] != 0){
//                 memcpy(payload, payload_response, MAX_PAYLOAD_SIZE);
//             }
//         }

//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//     }
// }

// void semaphore_task(void *p){
//     while(1){
//         digital_output.write(Q01, HIGH);
//         vTaskDelay(250);
//         digital_output.write(Q01, LOW);
//         vTaskDelay(250);

//         digital_output.write(Q02, HIGH);
//         vTaskDelay(250);
//         digital_output.write(Q02, LOW);
//         vTaskDelay(250);

//         digital_output.write(Q03, HIGH);
//         vTaskDelay(250);
//         digital_output.write(Q03, LOW);
//         vTaskDelay(250);
//     }
// }