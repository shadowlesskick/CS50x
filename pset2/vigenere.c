#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char rotk(char a, int k);
int kvalue(char a);

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Only 1 commandline argument please!");
        return 1;
    }
    
    string key = argv[1];
    int lengthkey = strlen(key);
    for(int i = 0; i < lengthkey; i++) // I would implement this as a function but I forget how to pass char arrays as pointers to other functions, why isn't this python? :(
    {
        if(!((key[i] >= 65 && key[i] <= 90)||(key[i] >= 97 && key[i] <= 122)))
        {
            printf("Please no non-alphabetical characters in the key");
            return 1;
        }
    }
    
    string text = GetString();
    int num = strlen(text);
    int whichk = 0;
    
    for(int i = 0; i < num; i++)
    {
        if(isalpha(text[i]))
        {
            int k = kvalue(key[whichk]);
            printf("%c", rotk(text[i],k));
            whichk++;
            if(whichk > lengthkey-1)
            {
                whichk = 0;
            }
        }
        else
        {
            printf("%c", text[i]);
        }
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

int kvalue(char a)
{
    if(a >= 65 && a <= 90)
    {
        int k = a-65;
        return k;
    }
    else if(a >= 97 && a <= 122)
    {
        int k = a-97;
        return k;
    }
    return 0;
}
