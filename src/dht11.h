#ifndef DHT11_H
#define DHT11_H


void inp(int x);
void start();
int detect();
int readbit();
uint8_t byte_creation();
void data(uint8_t *humint,uint8_t *humdec,uint8_t *tempint,uint8_t *tempdec);
#endif 