#include "industrialli_hub.hpp"
#include "digital_input/industrialli_digital_input_counter.hpp"

industrialli_hub hub;

void setup(){
	hub.begin();

    digital_input.begin();
    digital_input.attach_interrupt(I01, I01_COUNTING_UP_CALLBACK, NPN);
}

void loop(){
    Serial.prinln(i01_count);
}