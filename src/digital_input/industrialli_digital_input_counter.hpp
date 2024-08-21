#ifndef INDUSTRIALLI_DIGITAL_INPUT_COUNTER_H
#define INDUSTRIALLI_DIGITAL_INPUT_COUNTER_H

#include <Arduino.h>

volatile int i01_count = 0;
volatile int i02_count = 0;
volatile int i03_count = 0;
volatile int i04_count = 0;
volatile int i05_count = 0;
volatile int i06_count = 0;
volatile int i07_count = 0;
volatile int i08_count = 0;

void I01_COUNTING_UP_CALLBACK(){
    noInterrupts();
    i01_count++;
    interrupts();
}

void I02_COUNTING_UP_CALLBACK(){
    noInterrupts();
    i02_count++;
    interrupts();
}

void I03_COUNTING_UP_CALLBACK(){
    noInterrupts();
    i03_count++;
    interrupts();
}

void I04_COUNTING_UP_CALLBACK(){
    noInterrupts();
    i04_count++;
    interrupts();
}

void I05_COUNTING_UP_CALLBACK(){
    noInterrupts();
    i05_count++;
    interrupts();
}

void I06_COUNTING_UP_CALLBACK(){
    noInterrupts();
    i06_count++;
    interrupts();
}

void I07_COUNTING_UP_CALLBACK(){
    noInterrupts();
    i07_count++;
    interrupts();
}

void I08_COUNTING_UP_CALLBACK(){
    noInterrupts();
    i08_count++;
    interrupts();
}

void I01_COUNTING_DOWN_CALLBACK(){
    noInterrupts();
    i01_count--;
    interrupts();
}

void I02_COUNTING_DOWN_CALLBACK(){
    noInterrupts();
    i02_count--;
    interrupts();
}

void I03_COUNTING_DOWN_CALLBACK(){
    noInterrupts();
    i03_count--;
    interrupts();
}

void I04_COUNTING_DOWN_CALLBACK(){
    noInterrupts();
    i04_count--;
    interrupts();
}

void I05_COUNTING_DOWN_CALLBACK(){
    noInterrupts();
    i05_count--;
    interrupts();
}

void I06_COUNTING_DOWN_CALLBACK(){
    noInterrupts();
    i06_count--;
    interrupts();
}

void I07_COUNTING_DOWN_CALLBACK(){
    noInterrupts();
    i07_count--;
    interrupts();
}

void I08_COUNTING_DOWN_CALLBACK(){
    noInterrupts();
    i08_count--;
    interrupts();
}

#endif