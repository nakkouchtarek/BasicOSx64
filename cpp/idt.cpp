#pragma once
#include "io.cpp"

#define VGA_WIDTH 80
#define BLUE 0x90

#define FOREGROUND_BLACK 0x00
#define FOREGROUND_BLUE 0x01
#define FOREGROUND_GREEN 0x02
#define FOREGROUND_CYAN 0x03
#define FOREGROUND_RED 0x04
#define FOREGROUND_MAGENTA 0x05
#define FOREGROUND_BROWN 0x06
#define FOREGROUND_LIGHTGRAY 0x07
#define FOREGROUND_DARKGRAY 0x08
#define FOREGROUND_LIGHTBLUE 0x09
#define FOREGROUND_LIGHTGREEN 0x0A
#define FOREGROUND_LIGHTCYAN 0x0B
#define FOREGROUND_LIGHTRED 0x0C
#define FOREGROUND_LIGHTMAGENTA 0x0D
#define FOREGROUND_YELLOW 0x0E
#define FOREGROUND_WHITE 0x0F

#define BACKGROUND_BLACK 0x00
#define BACKGROUND_BLUE 0x10
#define BACKGROUND_GREEN 0x20
#define BACKGROUND_CYAN 0x30
#define BACKGROUND_RED 0x40
#define BACKGROUND_MAGENTA 0x50
#define BACKGROUND_BROWN 0x60
#define BACKGROUND_LIGHTGRAY 0x70
#define BACKGROUND_BLINKINGBLACK 0x80
#define BACKGROUND_BLINKINGBLUE 0x90
#define BACKGROUND_BLINKINGGREEN 0xA0
#define BACKGROUND_BLINKINGCYAN 0xB0
#define BACKGROUND_BLINKINGRED 0xC0
#define BACKGROUND_BLINKINGMAGENTA 0xD0
#define BACKGROUND_BLINKINGYELLOW 0xE0
#define BACKGROUND_BLINKINGWHITE 0xF0

int ScanCodes[256] = { 0x1E, 0x30, 0x2E, 0x20, 0x12, 0x21, 0x22, 0x23, 0x17, 0x24,
		       0x25, 0x26, 0x32, 0x31, 0x18, 0x19, 0x10, 0x13, 0x1F, 0x14,
		       0x16, 0x2F, 0x11, 0x2D, 0x15, 0x2C };
char Keys[256] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		   'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

char number[20] = {'1', '2','3', '4', '5', '6', '7', '8', '9', '0'};

int NumScanCodes[20] = {0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B};

int pos = 0;
char command[256];
char ch = 0;

unsigned short CursorPosition_x;
unsigned short CursorPosition_y;
unsigned short CursorPosition;
unsigned int videomemory = 0xb8000;
unsigned int newline = 80;

extern unsigned char mode;
extern unsigned short input;
extern unsigned char currentch;

void setnewline();
unsigned short get_lenght(char word[]);
void clear_screen();
void printf(char word[]);
void print(char word[]);
int check_for_command(char command[]);
void SetCursorPosition(uint_16 pos);
void InitializeIDT();
void outb(unsigned short port,unsigned char val);
unsigned char inb(unsigned short port);
void getch();
char* getinput();
int cmpstr(char word1[],char word2[]);
void space();
void backspace();
void revstr(char *str1,int len);
char* inttochar(int num);
int expo(int num,int val);
int chartoint(char word[]);
void calculator();
void terminal();
char* kinput();

struct IDT64{
  uint_16 offset_low;
  uint_16 selector;
  uint_8 ist;
  uint_8 types_attr;
  uint_16 offset_mid;
  uint_32 offset_high;
  uint_32 zero;
};

extern IDT64 _idt[256];
extern uint_64 isr1;
extern "C" void LoadIDT();

unsigned char mode = 0;
unsigned short input = 0;
unsigned char currentch = 0;

void PrintInput(unsigned short scanCode);
void PrintInputCalc(uint_8 scanCode);

void PrintInput(uint_8 scanCode)
{
	for(int i=0;i<256;i++)
	{
		if(scanCode == ScanCodes[i])
		{
			*(char*)videomemory = Keys[i];
			videomemory = videomemory + 2;
			SetCursorPosition(CursorPosition+1);
			newline--;
			command[pos] = Keys[i];
			pos++;
			ch = Keys[i];
			return;		
		}
		else if(scanCode == NumScanCodes[i])
		{
			*(char*)videomemory = number[i];
			videomemory = videomemory + 2;
			SetCursorPosition(CursorPosition+1);
			newline--;
			command[pos] = number[i];
			pos++;
			ch = number[i];
			return;
		}
		else
		{
			ch = 1;
		}
	}
	return;
}

void PrintInputCalc(uint_8 scanCode)
{
	for(int i=0;i<256;i++)
	{
		if(scanCode == NumScanCodes[i])
		{
			*(char*)videomemory = number[i];
			videomemory = videomemory + 2;
			SetCursorPosition(CursorPosition+1);
			newline--;
			command[pos] = number[i];
			pos++;
			ch = number[i];
			return;
		}
		else
		{
			ch = 1;
		}
	}
	return;
}

void InitializeIDT(){

    for(uint_64 t=0;t<256;t++)
    {
	    _idt[t].zero = 0;
	    _idt[t].offset_low = (uint_16)(((uint_64)&isr1 & 0x000000000000ffff));
	    _idt[t].offset_mid = (uint_16)(((uint_64)&isr1 & 0x00000000ffff0000) >> 16);
	    _idt[t].offset_high = (uint_32)(((uint_64)&isr1 & 0xffffffff00000000) >> 32);
	    _idt[t].ist = 0;
	    _idt[t].selector = 0x08;
	    _idt[t].types_attr = 0x8e;
    }

	outb(0x21, 0xfd);
	outb(0xa1, 0xff);
	LoadIDT();
}

extern "C" void isr1_handler()
{
	if(input==1)
	{
		switch(mode)
		{
			case 0:
				currentch = inb(0x60);
				PrintInput(currentch);
				outb(0x20, 0x20);
				outb(0xa0, 0x20);
				break;
			case 1:
				currentch = inb(0x60);
				PrintInputCalc(currentch);
				outb(0x20, 0x20);
				outb(0xa0, 0x20);
				break;
		}
		
	}
}
