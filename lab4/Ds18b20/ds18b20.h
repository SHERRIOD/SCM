#ifndef DS18B20_H_
#define DS18B20_H_

#include<reg51.h>
sfr P4 = 0xe8;

sbit 		DQ = P4^0;			
#define 	DQ_H	DQ = 1;
#define 	DQ_L	DQ = 0;

void reset_ds18b20(void);
void write_byte(unsigned char dat);
unsigned char read_byte(void);
int GetTemp();

#endif