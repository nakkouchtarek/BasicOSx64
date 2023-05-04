#include "setup.hpp"

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

void printf(char word[])
{
    print(word);
    setnewline();
}

void setnewline()
{
	CursorPosition+=newline;
	SetCursorPosition(CursorPosition);
	videomemory+=newline*2;
	newline=80;
	return;
}

void space()
{
	videomemory = videomemory - 2;
	*(char*)videomemory = ' ';
	SetCursorPosition(CursorPosition-1);
	newline++;
	pos--;
	command[pos] = 0;
}

void backspace()
{	
	*(char*)videomemory = ' ';
	videomemory = videomemory + 2;
	SetCursorPosition(CursorPosition+1);
	newline--;
	command[pos] = ' ';
	pos++;
}

void getch()
{
	while(ch==0)
	{
		input = 1;
	}
	ch = 0;
	input = 0;
}

void clear_array(char word[], int val)
{
	for(int i=0;i<val;i++)
	{
		word[i] = 0;
	}
	pos = 0;
}

char* getinput()
{
	clear_array(command,256);

	while(currentch!=0x1C)
	{
		if(currentch==0x0E)
		{
			space();
		}
		else if(currentch==0x39)
		{
			backspace();
		}
		getch();
	}

	currentch=0;

	return command;
}

void print(char word[])
{
	int i = 0;
	while(word[i])
	{	
		*(char*)videomemory = word[i];
		videomemory += 2;
		i++;
	}
	CursorPosition += i;
	SetCursorPosition(CursorPosition);
	newline-=i;
	return;

}

void SetCursorPosition(uint_16 position)
{
    //uint_16 position = position_y * VGA_WIDTH + position_x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(position & 0xFF)); 
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((position >> 8) & 0xFF));
    CursorPosition = position;
}

void clear_screen()
{
    videomemory = 0xb8000;
    for(int i=0;i<2048;i++)
    {
        *(char*)videomemory = ' ';
        videomemory++;
        *(char*)videomemory = BLUE;
        videomemory++;
    }
    videomemory = 0xb8000;
    SetCursorPosition(0);
}