#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

char rotk(char a, int k);

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Only 1 commandline argument please!");
        return 1;
    }
    
    string text = GetString();
    int k = atoi(argv[1])%26;
    int num = strlen(text);
    
    for(int i = 0; i < num; i++)
    {
        printf("%c", rotk(text[i],k));
    }
    printf("\n");

return 0;
}

char rotk(char a, int k)
{
    if(a >= 65 && a <= 90)
    {
        a = 65 + (((a-65)+k)%26);
        return a;
    }
    else if(a >= 97 && a <= 122)
    {
        a = 97 + (((a-97)+k)%26);
        return a;
    }
    else
    {
        return a;
    }
}
