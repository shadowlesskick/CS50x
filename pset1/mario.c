#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int correctInput = 0;
    int height;
    while(!correctInput)
    {
        printf("height: ");
        height = GetInt();
        if(height >= 0 && height <= 23)
        {
            correctInput = 1;
        }
    }
    
    for(int i = height; i >= 1; i--)
    {
        for(int j = 0; j < i-1; j++)
        {
            printf(" ");
        }
        for(int j = 0; j < 2+(height-i); j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
