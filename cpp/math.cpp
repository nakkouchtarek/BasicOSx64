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