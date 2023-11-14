#include"keyboard.h"
#include"delay.h"
#include"ch451.h"

#include<reg51.h>

unsigned char Convert(unsigned char key){
	key&=0x3f;
	if(key>=0x00&&key<=0x03) return key;
	else if(key>=0x08&&key<=0x0b) return key-0x04;
	else if(key>=0x10&&key<=0x13) return key-0x08;
	return key-0x0c;
}

unsigned char GetKey()
{
	unsigned char key_num=0xff;
	key_num=ch451_key;
	ch451_key=0xff;
	return Convert(key_num);
}