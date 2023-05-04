#include "typedef.hpp"
#include "math.cpp"

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

uint_16 get_lenght(char word[])
{
    int i=0;
    while(word[i])
    {
        i++;
    }
    return CursorPosition_x + i;
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