int expo(int num,int val)
{
    int num2 = num;
    int val2 = val; 

    if(val2==0)
    {
        return 1;
    }

    while(val2!=1)
    {
        num2 *= num; // num2 = 2 * 2
        val2--; // val2 = val2 - 1 
    }

    return num2; 
}
