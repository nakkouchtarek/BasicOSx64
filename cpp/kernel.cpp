#include "idt.cpp"

void printf(char word[])
{
    print(word);
    setnewline();
}

// calculator

void clear_array(char word[], int val)
{
	for(int i=0;i<val;i++)
	{
		word[i] = 0;
	}
	pos = 0;
}

// file

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

// file

// file

void getch()
{
	while(ch==0)
	{
		input = 1;
	}
	ch = 0;
	input = 0;
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

// file

char commands[][20] = { "calc" }; 

int check_for_command(char command[])
{
	int n_apps = 1;
	for(int i=0;i<n_apps;i++)
    {
        if(cmpstr(commands[i],command)==0)
		{
			return i;
		}
    }
    setnewline();
    print(command);
    print(" was not found");
    setnewline();
    return -1;
}


// file

void calculator()
{
    int num, num2, total;
    char op;

    mode=1;

    setnewline();

    print("First number: ");
    getinput();
    num = chartoint(command);
    clear_array(command,256);

    setnewline();

    /*
    print("Operator: ");
    getinput();
    op = command[0];
    clear_array(command,256);

    setnewline();
    */

    print("Second number: ");
    getinput();
    num2 = chartoint(command);
    clear_array(command,256);

    setnewline();

    print("Total of both numbers: ");
    total = num + num2;
    print(inttochar(total));

    setnewline();

    mode=0;
}

void revstr(char *str1,int len)  
{  
    // declare variable  
    int i, temp;  
    // use for loop to iterate the string   
    for (i = 0; i < len/2; i++)  
    {  
        // temp variable use to temporary hold the string  
        temp = str1[i];  
        str1[i] = str1[len - i - 1];  
        str1[len - i - 1] = temp;  
    }  
}  
 
char* inttochar(int num)
{
    int num2 = num;
    int res;
    static char word[256];
    int i =0;
    while(num2!=0)
    {
        res = num2 % 10;
        num2 = num2 / 10;
        word[i] = res+48;
        i++;
    }
    revstr(word,i); 
    return word;
}

int expo(int num,int val)
{
    int num2 = num; // num2 = 2
    int val2 = val; // val2 = 2 

    if(val2==0)
    {
        return 1;
    }

    while(val2!=1) // while val2 >= 0
    {
        num2 *= num; // num2 = 2 * 2
        val2--; // val2 = val2 - 1 
    }

    return num2; 
}

int chartoint(char word[])
{
    int lenght;
    int i = 0;
    while(word[i])
    {
        i++;
    }
    lenght = i - 1;
    i = 0;
    int num = 0;
    while(word[i])
    {
        num = num + ((word[i]-48) * expo(10,lenght));
        lenght--;
        i++;
    }
    return num;
}

// file

int cmpstr(char word1[],char word2[])
{
    int i =0;
    while(word1[i])
    {
        if(!(word1[i]==word2[i]))
        {
            return 1;
        }
        i++;
    }  
    return 0;
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


uint_16 get_lenght(char word[])
{
    int i=0;
    while(word[i])
    {
        i++;
    }
    return CursorPosition_x + i;
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

void terminal()
{
    clear_screen();
    mode=0;

    while(1)
    {
        print("user@randomos:>> ");
        getinput();

        switch (check_for_command(command))
        {
            case 0:
                calculator();
                break;
            
            default:
                break;
        }
    }
}

void init()
{
    clear_screen();
    SetCursorPosition(0);
    InitializeIDT();
    printf("Welcome to my OS");
    printf("Press a key to continue...");
    getinput();
    clear_screen();
    return;
}

extern "C" void _start()
{
    init();
    terminal();
    return;
}