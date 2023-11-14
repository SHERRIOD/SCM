#include"nixie.h"
#include"delay.h"

#include<regx52.h>

unsigned char num[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x58,0x5e,0x79,0x71,0x00};

void NixieDisplay(unsigned char d[]){
	char mask;
	int i;
	mask=3;
	for(i=0;i<4;i++){
		P3&=0x8f;
		P0=num[d[i]];
		P3|=(mask<<4);
		Delay(3);
		mask--;
	}
	mask=7;
	for(i=4;i<8;i++){
		P3&=0x8f;
		P0=num[d[i]];
		P3|=(mask<<4);
		Delay(3);
		mask--;
	}
}