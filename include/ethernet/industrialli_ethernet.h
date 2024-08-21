#ifndef INDUSTRIALLI_ETHERNET_H
#define INDUSTRIALLI_ETHERNET_H

#include <Ethernet2.h>
#include <SPI.h>

extern SPIClass spi_ethernet;

class industrialli_ethernet {
public:
    void begin();
};

#endif