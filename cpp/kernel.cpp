#include "idt.cpp"
#include "string.cpp"
#include "calc.cpp"

char commands[][20] = { "calc", "clear" }; 

int check_for_command(char command[])
{
	int n_apps = 2;

	for(int i=0;i<n_apps;i++)
    {
        if(cmpstr(commands[i],command) == 0)
		{
			return i;
		}
    }

    return -1;
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
            case 1:
                clear_screen();
                break;
            
            default:
                setnewline();
                print(command);
                print(" was not found");
                setnewline();
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