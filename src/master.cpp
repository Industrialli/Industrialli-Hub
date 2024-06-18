// #include "industrialli_hub.hpp"

// industrialli_hub hub;

// void setup(){
// 	hub.begin();

//     nextion.begin();

//     lora.begin(false);
// 	lora.setnetworkId(0);
// 	lora.config_bps(BW500, SF_LoRa_7, CR4_5);
// 	lora.config_class(LoRa_CLASS_C, LoRa_WINDOW_15s);
// 	lora.setpassword(22);
// }

// void loop() {
// 	uint8_t payload_request[2] = {0,0};

// 	lora.PrepareFrameCommand(1, 0x05, payload_request, 2);
// 	lora.SendPacket();

//     uint16_t id;
// 	uint8_t payload[MAX_PAYLOAD_SIZE];
//     uint8_t cmd;
// 	uint8_t size;

//     if(lora.ReceivePacketCommand(&id, &cmd, payload, &size, 10)){

//         if(payload[0] != 0){
//             float temp = payload[1] / 10.0;

//             float tempSensor0150C = (((temp - 4.00) / (16.0)) * 200.00) * 10;

//             Serial.println(temp);
//             Serial.println(tempSensor0150C);

//             nextion.writeNum("n0.val", payload[0]);
//             nextion.writeNum("x0.val", tempSensor0150C);
//             nextion.writeNum("j0.val", (int)(tempSensor0150C / 10));
//         }
// 	}

//     delay(10);
// }