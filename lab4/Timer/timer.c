#include"timer.h"
#include"nixie.h"
#include"delay.h"

#include<regx52.h>


int state=INIT;
int time_min=0;
int time_s=0;

int time=20;
unsigned char key=0xff;

unsigned char nixie_buf[8]={SEGNONE};


void InitTimer0()
{
	TMOD=0x01;
	TH0=0x3c;
	TL0=0xb0;
	ET0=1;
	EA=1;
}

void RefreshNixie(){
	int i;
	for(i=0;i<8;i++){
		nixie_buf[i]=SEGNONE;
	}
}

// 0
void InitState(){
	RefreshNixie();
	time=20;
	time_min=0;
	time_s=0;
	TR0=0;
	#ifdef DEBUG
	nixie_buf[7]=INIT;
  #endif
	
	if(key==SETTIME) state = PREPARE1;
}

// 1
void PrepareState1(){
	RefreshNixie();
	#ifdef DEBUG
	nixie_buf[7]=PREPARE1;
  #endif
    if(key!=0xff){
			if(key<0x0a&&key>=0x00){
        time_min=key;
				nixie_buf[2]=time_min;
        state=PREPARE2;
			}
			else if(key==END) state=INIT;
    }
}

// 2
void PrepareState2(){
	RefreshNixie();
	nixie_buf[2]=time_min;
	#ifdef DEBUG
	nixie_buf[7]=PREPARE2;
  #endif
    if(key!=0xff){
        if(key<=0x06 && key>=0x00){
            time_s=key;
					nixie_buf[1]=time_min;
					nixie_buf[2]=time_s;
            state=PREPARE3;
        }
				else if(key==END) state=INIT;
    }
}

// 3
void PrepareState3(){
	RefreshNixie();
	nixie_buf[1]=time_min;
	nixie_buf[2]=time_s;
	#ifdef DEBUG
	nixie_buf[7]=PREPARE3;
  #endif
    if(key!=0xff){
        if(key<0x0a && key>=0x00){
            time_s=time_s*10 + key;
            state=PREPAREWELL;
        }
				else if(key==END) state=INIT;
    }
}

// 6
void PrepareWell(){
		RefreshNixie();
	nixie_buf[0]=time_min;
	nixie_buf[1]=time_s/10;
	nixie_buf[2]=time_s%10;
	#ifdef DEBUG
	nixie_buf[7]=PREPAREWELL;
  #endif
	if(key!=0xff){
    if(key==START){
        TR0=1;
        state=CLOCK;
    }
		else if(key==END) state=INIT;
	}
}

// 4
void ClockState(){
		RefreshNixie();
	nixie_buf[0]=time_min;
	nixie_buf[1]=time_s/10;
	nixie_buf[2]=time_s%10;
	#ifdef DEBUG
	nixie_buf[7]=CLOCK;
  #endif
	if(key!=0xff){
    if(key==PAUSE){
        TR0=0;
        state=FREEZE;
    }
    else if(key==END) state=INIT;
	}
}

// 5
void FreezeState(){
		RefreshNixie();
	nixie_buf[0]=time_min;
	nixie_buf[1]=time_s/10;
	nixie_buf[2]=time_s%10;
	#ifdef DEBUG
	nixie_buf[7]=FREEZE;
  #endif
	if(key!=0xff){
    if(key==START){
        TR0=1;
        state=CLOCK;
    }
		else if(key==END) state=INIT;
	}
}

void time0() interrupt 1{
	#ifdef DEBUG
	nixie_buf[6]=8;
  #endif
	time--;
    if(!time){
        time_s--;
        if(time_s<0){
            time_s=59;
            time_min--;
            if(time_min<0){
                TR0=0;
                state=INIT;
							Delay(0.1);
                return;
            }
        }
        time=20;
    }
	TH0=0x3c;
	TL0=0xb0;
}