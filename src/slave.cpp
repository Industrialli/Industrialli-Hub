#include "industrialli_hub.hpp"

industrialli_hub hub;

void setup(){
	hub.begin();
	
    digInHub.begin();
	digInHub.begin_encoder_counting(0, PNP);
    digInHub.begin_digital_input_counting(I03, NPN, UP);
	digInHub.begin_digital_input_counting(I04, PNP, UP);

    // anlgInHub.begin();  
    // anlgInHub.setAnalogResolution(BITS_12);
    // anlgInHub.setReadMode(A01, READ_020);

	// lora.begin();
	// lora.setnetworkId((uint16_t)1);
	// lora.config_bps(BW500, SF_LoRa_7, CR4_5);
	// lora.config_class(LoRa_CLASS_C, LoRa_WINDOW_15s);
	// lora.setpassword(22);
}

void loop() {
	// uint16_t id_request;
    // uint8_t cmd_request;
	// uint8_t payload_request[MAX_PAYLOAD_SIZE];
	// uint8_t size_request;

	digInHub.update_leds();

	// if(lora.ReceivePacketCommand(&id_request, &cmd_request, payload_request, &size_request, 10)){
	// 	if(cmd_request == 0x05){
    //         uint8_t payload_response[2] = {digInHub.get_count(I03), (uint8_t)(anlgInHub.get020mA(A01) * 10)};

			Serial.println("#########################################");
			Serial.println(digInHub.get_pulses_encoder(0));
			Serial.println(digInHub.get_encoder_sense(0));
			Serial.println(digInHub.get_encoder_velocity(0));
			Serial.println("#########################################");
			

    //         lora.PrepareFrameCommand(0, 0x05, payload_response, 2);
    //         lora.SendPacket();
    //     }
	// }
    
    
    leds.update();
	delay(100);
}