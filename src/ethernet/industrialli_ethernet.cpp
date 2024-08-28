#include "ethernet/industrialli_ethernet.h"

void industrialli_ethernet::begin(){
    pinMode(PD7, OUTPUT);

    digitalWrite(PD7, LOW);
    delay(10);
    digitalWrite(PD7, HIGH);
    delay(10);

    spi_ethernet.setMISO(PB14);
    spi_ethernet.setMOSI(PB15);
    spi_ethernet.setSCLK(PB13);

    Ethernet.init(PB12);
}

//reset ic