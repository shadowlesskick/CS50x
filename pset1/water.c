#include <stdio.h>
#include <cs50.h>

int main(void)
{

    int minutes;

    printf("minutes: ");
    minutes = GetInt();
    
    int bottles = minutes * 12;
    
    printf("bottles: %d", bottles);
}
