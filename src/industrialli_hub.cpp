#include "industrialli_hub.h"

void industrialli_hub::begin(){
    pinMode(DEBUG_LED, OUTPUT);
    pinMode(RS485_TER_SEL, OUTPUT);

    leds.begin();

	iso.begin();
	iso.enable();
}