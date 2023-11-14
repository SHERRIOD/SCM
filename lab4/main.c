#define DEBUG 1

#include"delay.h"
#include"keyboard.h"
#include"nixie.h"
#include"timer.h"
#include"ds18b20.h"

#include<regx52.h>

void main(){
	int k;
	InitTimer0();
	
	while(1){
		key=GetKey();
        switch(state){
            case INIT: InitState();break;
            case PREPARE1: PrepareState1();break;
            case PREPARE2: PrepareState2();break;
            case PREPARE3: PrepareState3();break;
						case PREPAREWELL: PrepareWell();break;
            case CLOCK: ClockState();break;
            case FREEZE: FreezeState();break;
        }
		k=GetTemp();
		nixie_buf[5]=k/100;
		nixie_buf[6]=(k%100)/10;
		nixie_buf[7]=k%10;
		NixieDisplay(nixie_buf);
		Delay(5);
	}
	
}