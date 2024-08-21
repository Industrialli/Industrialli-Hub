#include "industrialli_hub.hpp"
#include "digital_input/industrialli_digital_input_counter.hpp"

industrialli_hub hub;

void setup(){
	hub.begin();

	digital_input.begin();
	digital_input.attach_interrupt(I01, I01_COUNTING_UP_CALLBACK, PNP);

    analog_input.begin();
    analog_input.set_resolution(12);
    analog_input.set_read_mode(A01, READ_20mA);

	lora.begin(false);
	lora.setnetworkId((uint16_t)1);
	lora.config_bps(BW500, SF_LoRa_7, CR4_5);
	lora.config_class(LoRa_CLASS_C, LoRa_WINDOW_15s);
	lora.setpassword(22);
}

void loop() {
	uint16_t id_request;
    uint8_t cmd_request;
	uint8_t payload_request[MAX_PAYLOAD_SIZE];
	uint8_t size_request;

	if(lora.ReceivePacketCommand(&id_request, &cmd_request, payload_request, &size_request, 10)){
		if(cmd_request == 0x05){
            
			uint8_t payload_response[2] = {
				i01_count, 
				(uint8_t)(analog_input.analog_read(A01) * 10)
			};
            
			lora.PrepareFrameCommand(0, 0x05, payload_response, 2);
            lora.SendPacket();
        }
	}
    
	digital_input.update_leds();
	leds.update();
}