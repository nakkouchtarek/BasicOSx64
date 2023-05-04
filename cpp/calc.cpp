#include "setup.hpp"

void calculator()
{
    int num, num2, total;
    char op;

    mode=1;

    clear_array(command,256);
    setnewline();

    print("First number: ");
    getinput();
    num = chartoint(command);
    clear_array(command,256);
    setnewline();

    print("Operator: ");
    getinput();
    op = command[0];
    clear_array(command,256);
    setnewline();

    print("Second number: ");
    getinput();
    num2 = chartoint(command);
    clear_array(command,256);
    setnewline();

    print("Total of both numbers: ");
    
    switch (op)
    {

    case '+':
        total = num + num2;
        break;
    
    case '*':
        total = num * num2;
        break;

    case '-':
        total = num - num2;
        break;

    case '/':
        total = num / num2;
        break;
    
    default:
        total = -1;
        break;
    }

    print(inttochar(total));

    setnewline();

    mode=0;
}
