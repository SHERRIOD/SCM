#include"ds18b20.h"

#include<intrins.h>


void delay_10us(unsigned char n){
	unsigned char i;
	for(i=n; i>0; --i){
		_nop_();
		//_nop_(); //???12MHz
	}
}

void reset_ds18b20(void){
  	DQ_H;          		//  DQ???
	delay_10us(10);     //  ??
  	DQ_L;             	//  ??????
	delay_10us(60);     //  ??(480us - 960us)
  	DQ_H;          		//  ?????
	delay_10us(24);     //  DS18B20???????,??60-240us
}

void write_byte(unsigned char dat){ 
	unsigned char i=0; 		
	for (i = 8; i > 0; i--){
		//??????????????,???????
		if(dat & 0x01)
        {
			DQ_L;
			_nop_(); _nop_(); //?? 2us
            DQ_H;   //????
			delay_10us(6);
        }
        else
        {
			DQ_L;
			delay_10us(6);
            DQ_H;
			_nop_(); _nop_(); //?? 2us
        }
		dat>>=1;
	}
	delay_10us(3);
}


unsigned char read_byte(void)  			
{
	unsigned char i = 0; 		
	unsigned char dat = 0;
	bit b;
    //????????
    for (i = 8; i > 0; i--)  		
	{
		DQ_L;
		_nop_(); _nop_(); //?? 2us
		DQ_H;  //????
		dat >>= 1;  //???15us????, ???????????
		b= DQ;

    	if (DQ){
            dat|=0x80;
        }

		delay_10us(6);
	}
    return(dat);
}

int GetTemp(){
    unsigned char tempL;
	short tempH;
    int k;
    reset_ds18b20();
	write_byte(0xcc);
	write_byte(0x44);
	reset_ds18b20();
	write_byte(0xcc);
	write_byte(0xbe);
	tempL=read_byte();
	tempH=read_byte();
	tempH=(tempH<<8)| tempL;
	if((tempH|0xf800)==0xf800)
		tempH=~tempH+1;	
	k=tempH*0.625;
    return k;
}
