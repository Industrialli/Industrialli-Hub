#include "industrialli_isoOutHub.h"

void industrialli_isoOutHubCtrl::begin()
{

    pinMode(SPI4_NSS_PE4, OUTPUT);
    pinMode(ISO_DIS_PE3, OUTPUT);
    pinMode(IC1_ISO_DIAG_PC0, INPUT);
    pinMode(IC2_ISO_DIAG_PC1, INPUT);
    digitalWrite(ISO_DIS_PE3, LOW); // Inicia com as saidas desabilitadas
}

void industrialli_isoOutHubCtrl::writeDigitalOutput(uint8_t qNum, bool output) // Escreve o valor HIGH ou LOW em uma saida digital especifica
{
    if (output)
    {
        _qNum = qNum - 1;
        _isoDigitalOutput[_qNum] = 1;
    }
    else
    {
        _qNum = qNum - 1;
        _isoDigitalOutput[_qNum] = 0;
    }
    _spiPort = &SPI;
    _spiPort->setMISO(SPI4_MISO_PE5);
    _spiPort->setMOSI(SPI4_MOSI_PE6);
    _spiPort->setSCLK(SPI4_SCK_PE2);
    _spiPort->begin();
    _spiPort->beginTransaction(SPISettings(1000000UL, LSBFIRST, SPI_MODE3));

    for (int i = 0; i < 8; i++)
    {
        _transferIsoOut0to7 += (_isoDigitalOutput[i] << (7 - i));
        _transferIsoOut8to15 += (_isoDigitalOutput[8 + i] << (7 - i));
    }

    digitalWrite(SPI4_NSS_PE4, LOW);
    _spiPort->transfer(_transferIsoOut8to15); // LED8 -> LED15
    _spiPort->transfer(_transferIsoOut0to7);  // LED0 -> LED7
    _transferIsoOut0to7 = 0;
    _transferIsoOut8to15 = 0;
    digitalWrite(SPI4_NSS_PE4, HIGH);
    getIsoOutLedsStatus(_qNum, output);
    _spiPort->endTransaction();
    _spiPort->end();
}

void industrialli_isoOutHubCtrl::getIsoOutLedsStatus(uint8_t led, uint8_t onOff)//obtem o status dos leds das saidas 
{
    _led = led;
    _onOff = onOff;

    // Q1 -> LED12
    // Q2 -> LED13
    // Q3 -> LED14
    // Q4 -> LED15
    // Q5 -> LED16
    // Q6 -> LED17
    // Q7 -> LED18
    // Q8 -> LED19

switch (_led)
    {
    case 0: // Q1
        if (_onOff)
        {
            ledsCtrl.ledOn(12);
        }
        else
        {
            ledsCtrl.ledOff(12);
        }
        break;

    case 1: // Q2
        if (_onOff)
        {
            ledsCtrl.ledOn(13);
        }
        else
        {
            ledsCtrl.ledOff(13);
        }
        break;

    case 2: // Q3
        if (_onOff)
        {
            ledsCtrl.ledOn(14);
        }
        else
        {
            ledsCtrl.ledOff(14);
        }
        break;

    case 3: // Q4
        if (_onOff)
        {
            ledsCtrl.ledOn(15);
        }
        else
        {
            ledsCtrl.ledOff(15);
        }
        break;

    case 4: // Q5
        if (_onOff)
        {
            ledsCtrl.ledOn(16);
        }
        else
        {
            ledsCtrl.ledOff(16);
        }
        break;

    case 5: // Q6
        if (_onOff)
        {
            ledsCtrl.ledOn(17);
        }
        else
        {
            ledsCtrl.ledOff(17);
        }
        break;

    case 6: // Q7
        if (_onOff)
        {
            ledsCtrl.ledOn(18);
        }
        else
        {
            ledsCtrl.ledOff(18);
        }
        break;

    case 7: // Q8
        if (_onOff)
        {
            ledsCtrl.ledOn(19);
        }
        else
        {
            ledsCtrl.ledOff(19);
        }
        break;

        // Q9 -> LED24
        // Q10 -> LED25
        // Q11 -> LED26
        // Q12 -> LED27
        // Q13 -> LED28
        // Q14 -> LED29
        // Q15 -> LED30
        // Q16 -> LED31

    case 8: // Q9
        if (_onOff)
        {
            ledsCtrl.ledOn(24);
        }
        else
        {
            ledsCtrl.ledOff(24);
        }
        break;

    case 9: // Q10
        if (_onOff)
        {
            ledsCtrl.ledOn(25);
        }
        else
        {
            ledsCtrl.ledOff(25);
        }
        break;

    case 10: // Q11
        if (_onOff)
        {
            ledsCtrl.ledOn(26);
        }
        else
        {
            ledsCtrl.ledOff(26);
        }
        break;

    case 11: // Q12
        if (_onOff)
        {
            ledsCtrl.ledOn(27);
        }
        else
        {
            ledsCtrl.ledOff(27);
        }
        break;

    case 12: // Q13
        if (_onOff)
        {
            ledsCtrl.ledOn(28);
        }
        else
        {
            ledsCtrl.ledOff(28);
        }
        break;

    case 13: // Q14
        if (_onOff)
        {
            ledsCtrl.ledOn(29);
        }
        else
        {
            ledsCtrl.ledOff(29);
        }
        break;

    case 14: // Q15
        if (_onOff)
        {
            ledsCtrl.ledOn(30);
        }
        else
        {
            ledsCtrl.ledOff(30);
        }
        break;

    case 15: // Q16
        if (_onOff)
        {
            ledsCtrl.ledOn(31);
        }
        else
        {
            ledsCtrl.ledOff(31);
        }
        break;

    default:
        break;
    }



    
}

void industrialli_isoOutHubCtrl::enableOutputs(void)//Habilita as saidas
{ // Habilita as saidas digitais da Hub
    digitalWrite(ISO_DIS_PE3, HIGH);
}
void industrialli_isoOutHubCtrl::disableOutputs(void)//Desabilita as saidas
{ // Desabilita as saidas digitais da Hub
    digitalWrite(ISO_DIS_PE3, LOW);
}
void industrialli_isoOutHubCtrl::getPowerLedsStaus(void)//obtem status dos leds da alimentacao
{
    if (digitalRead(IC1_ISO_DIAG_PC0))
    {
        ledsCtrl.ledOn(22);
    }
    else
    {
        ledsCtrl.ledOff(22);
    }

    if (digitalRead(IC2_ISO_DIAG_PC1))
    {
        ledsCtrl.ledOn(23);
    }
    else
    {
        ledsCtrl.ledOff(23);
    }
}

bool industrialli_isoOutHubCtrl::getOut1to8Status(void)//Retorna verdadeiro para operacao nomal e falso pra anomalia (saidas 1~8)
{
    if (digitalRead(IC1_ISO_DIAG_PC0))
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool industrialli_isoOutHubCtrl::getOut9to16Status(void)//Retorna verdadeiro para operacao nomal e falso pra anomalia (saidas 9~16)
{
    if (digitalRead(IC2_ISO_DIAG_PC1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void industrialli_isoOutHubCtrl::test(bool onOff){
for(int i = 1; i < 17; i++){
    writeDigitalOutput(i, onOff);
}

}

