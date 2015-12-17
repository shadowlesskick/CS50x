#include <stdio.h>
#include <cs50.h>
#include <string.h>

char makeUpper(char a);

int main(int argc, char* argv[])
{
    string name = GetString();
    int sizeOfName = strlen(name);
    
    printf("%c", makeUpper(name[0]));
    int previousSpace = 0;
    for(int i=1; i<sizeOfName; i++)
    {
        if(previousSpace)
        {
            printf("%c", makeUpper(name[i]));
            previousSpace = 0;
        }
        if(name[i] == ' ')
        {
            previousSpace = 1;
        }

    }
    printf("\n");
    return 0;
}

char makeUpper(char a)
{
    if(a >= 97 && a <=122)
    {
    a -= 32;
    }
    return a;
}
