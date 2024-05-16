#ifndef INDUSTRIALLI_ISOOUTHUB_H
#define INDUSTRIALLI_ISOOUTHUB_H

#include <Arduino.h>
#include <stdlib.h>
#include <SPI.h>
#include "industrialli_ledsHub.h"

#define SPI4_SCK_PE2 PE2
#define SPI4_NSS_PE4 PE4
#define SPI4_MOSI_PE6 PE6
#define SPI4_MISO_PE5 PE5
#define ISO_DIS_PE3 PE3
#define IC1_ISO_DIAG_PC0 PC0
#define IC2_ISO_DIAG_PC1 PC1

#define Q01 1
#define Q02 2
#define Q03 3
#define Q04 4
#define Q05 5
#define Q06 6
#define Q07 7
#define Q08 8

#define Q09 9
#define Q10 10
#define Q11 11
#define Q12 12
#define Q13 13
#define Q14 14
#define Q15 15
#define Q16 16

extern industrialli_ledsHubCtrl ledsCtrl;

class industrialli_isoOutHubCtrl
{
public:
    void begin(void);
    void writeDigitalOutput(uint8_t qNum, bool output);
    void getIsoOutLedsStatus(uint8_t led, uint8_t onOff);
    void enableOutputs(void);
    void disableOutputs(void);
    void getPowerLedsStaus(void);
    bool getOut1to8Status(void);
    bool getOut9to16Status(void);
    void test(bool onOff);

private:
    SPIClass *_spiPort;

    uint8_t _isoDigitalOutput[16] =
        {
            _isoDigitalOutput[0],
            _isoDigitalOutput[1],
            _isoDigitalOutput[2],
            _isoDigitalOutput[3],
            _isoDigitalOutput[4],
            _isoDigitalOutput[5],
            _isoDigitalOutput[6],
            _isoDigitalOutput[7],

            _isoDigitalOutput[8],
            _isoDigitalOutput[9],
            _isoDigitalOutput[10],
            _isoDigitalOutput[11],
            _isoDigitalOutput[12],
            _isoDigitalOutput[13],
            _isoDigitalOutput[14],
            _isoDigitalOutput[15]};

    uint8_t _transferIsoOut0to7 = 0;
    uint8_t _transferIsoOut8to15 = 0;
    uint8_t _qNum;
    bool _onOff = false;
    uint8_t _led;
  
};

#endif