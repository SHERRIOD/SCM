#ifndef TIMER_H_
#define TIMER_H_

#define INIT 0
#define PREPARE1 1
#define PREPARE2 2
#define PREPARE3 3
#define CLOCK 4
#define FREEZE 5
#define PREPAREWELL 6

#define SETTIME 0x0a
#define START 0x0b
#define PAUSE 0x0c
#define END 0x0d

extern int state;
extern int time_min;
extern int time_s;
extern int time;

extern unsigned char key;
extern unsigned char nixie_buf[8];

void InitTimer0();
void RefreshNixie();
void InitState();
void PrepareState1();
void PrepareState2();
void PrepareState3();
void PrepareWell();
void ClockState();
void FreezeState();
void time0();

#endif