#include "industrialli_hubInit.h"

void industrialli_hubInit::begin(){
    pinMode(DEBUG_LED, OUTPUT);
    pinMode(RS485_TER_SEL, OUTPUT);
}