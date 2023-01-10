#include <reg52.h>
#define lcd P3
#define dat P2
sbit rs=P1^6;
sbit e=P1^7;

void delay(int);
void display(unsigned char);
void cmd(unsigned char);
void init(void);
void string(char*);
void intro(void);
char i=0;

void delay(int d)
{
	unsigned char i=0;
	for(;d>0;d--)
	{ 
		for(i=250; i>0; i--);
		for(i=248; i>0; i--);
	}
}
void display(unsigned char c){
	lcd = c ; 
	rs = 1;
	e = 1;
	delay(10);
	e=0;
}
void string(char *c)
{
	while(*c){
		display(*c++);
	}
}
void init(void){
	cmd(0x38); // Configure the LCD in 8-bit mode, 2 line and 5×7 font
	cmd(0x01);  // Clear display screen
	cmd(0x0C);  // Display On and Cursor Off
	cmd(0x80); // Set cursor position to 1st line, 1st column
}
void intro(void){
	string("Electronics" );
	cmd(0xc0);
	string("    Hub    ");
	delay(2000);
	cmd(0x01);
	string("   Digital   ");
	cmd(0xc0);
	string("    Voltmeter   ");
	delay(2000);
	cmd(0x01);
	cmd(0x08);
}

void main()
{
	unsigned int temp=0;
	unsigned int temp1=0;
	float val=0.0;
	
	init();
	intro();
	dat=0xFF;
	while(1)
	{
		if(i==0)
		{
			string(" Volts - ");
			i++;
		}
		val = dat*0.02;
		val = val/0.2;
		cmd(0x89);
		if((val>=1.0) && (val<10.0))
		{
			display(' ');
			temp=val*1000;
			temp1=((temp/1000)+48);
			display(temp1);
			display('.');
			temp1 = (((temp/100)%10)+48);
			display(temp1);
		}
		else if((val>=10.0) && (val<100.0)){
			temp=val*100;
			temp1=((temp/1000)+48);
			display(temp1);
			temp1=(((temp/1000)%10)+48);
			display(temp1);
			display('.');
			temp1=(((temp/10)%10)+48);
			display(temp1);
		}
		else
		{
			display(' ');
			string("0.0");
		}
		delay(1000);
	}
	while(1);
}
		
	
		
		