#include "industrialli_hubInit.h"

void industrialli_hubInit::begin(void)
{
    pinMode(DEBUG_LED, OUTPUT);
    pinMode(RS485_TER_SEL, OUTPUT);
}