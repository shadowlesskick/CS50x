#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int correctInput = 0;
    float owed;
    printf("O hai! ");
    while(!correctInput)
    {
        printf("How much change is owed?\n");
        owed = GetFloat();
        if(owed >= 0)
        {
            correctInput = 1;
        }
    }
    
    int cent = (int) round(owed*100);
    int numberOfCoins = 0;
    numberOfCoins += cent/25;
    cent = cent%25;
    numberOfCoins += cent/10;
    cent = cent%10;
    numberOfCoins += cent/5;
    cent = cent%5;
    numberOfCoins += cent/1;
    cent = cent%1;
    printf("%d\n", numberOfCoins);
    
}
