/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

#include <stdio.h>

bool rec(int value, int values[], int first, int last)
{
    int middle = (first+last)/2;
    if(last < first)
    {
        return false;
    }
    else if (value < values[middle])
    {
        return rec(value, values, first, middle-1);
    }
    else if (value > values[middle])
    {
        return rec(value, values, middle+1, last);
    }
    else
    {
        return true;
    }
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Linear search
    /*if(n < 0)
    {
        return false;
    }
    
    for(int i = 0; i < n; i++)
    {
        if(values[i] == value)
        {
            return true;
        }
    }
    return 0;
    */
    
    //Binary Search
    return rec(value, values, 0, n-1);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    // Implement selection sort
    /*
    for(int i = 0; i < n-1; i++)
    {
        int positionOfSmallest = i;
        for(int j = i+1; j < n; j++)
        {
            if(values[j] < values[positionOfSmallest])
            {
                positionOfSmallest = j;
            }
        } 
        int a = values[i];
        values[i] = values[positionOfSmallest];
        values[positionOfSmallest] = a;
    }
    */
    
    //Implement insertion sort
    for(int i = 1; i < n; i++)
    {
        int position = i;
        int value = values[i];
        while(position >=0)
        {
            if(value > values[position-1] || position == 0)
            {
                values[position] = value;
                break;
            }
            else
            {
                values[position] = values[position-1];
                position--;
            }
        }
    }
    
    for(int i = 0; i < n; i++)
    {
        printf("%d ",values[i]);
    }
    
    return;
}
