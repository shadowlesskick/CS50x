/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 *
 * 0xff 0xd8 0xff 0xe0
 * 0xff 0xd8 0xff 0xe1
 */
 
 #include <stdlib.h>
 #include <stdio.h>
 #include <stdint.h>
 #include <cs50.h>
 #include <string.h>

int main(int argc, char* argv[])
{
    uint8_t tocheck1[4] = {0xff, 0xd8, 0xff, 0xe0};
    uint8_t tocheck2[4] = {0xff, 0xd8, 0xff, 0xe1};
    
    string filenamerecover = "card.raw";
    
    FILE* file = fopen(filenamerecover, "r");
    
    if (file == NULL)
    {
        printf("Could not open %s.\n", filenamerecover);
        return 2;
    }
    
    uint8_t data[512];
    uint8_t check[4];
    int writing = 0;
    int filenumber = 0;
    FILE* outptr;
    char filenamewrite[80];
    while(fread(&data, sizeof(uint8_t), 512, file) > 0)
    {
        for(int i = 0; i < 4; i++)
        {
            check[i] = data[i];
        }
        
        if((memcmp(check, tocheck1, sizeof(check)) == 0 || memcmp(check, tocheck2, sizeof(check)) == 0) && writing == 0)
        {
            sprintf(filenamewrite, "%03d.jpg", filenumber);
            outptr = fopen(filenamewrite, "w");
                if (outptr == NULL)
                {
                    fprintf(stderr, "Could not create %s.\n", filenamewrite);
                    return 3;
                }
            fwrite(data, 512, 1, outptr);
            writing = 1;
        }
        else if((memcmp(check, tocheck1, sizeof(check)) == 0 || memcmp(check, tocheck2, sizeof(check)) == 0) && writing == 1)
        {
            fclose(outptr);
            filenumber++;
            sprintf(filenamewrite, "%03d.jpg", filenumber);
            outptr = fopen(filenamewrite, "w");
                if (outptr == NULL)
                {
                    fprintf(stderr, "Could not create %s.\n", filenamewrite);
                    return 3;
                }
            fwrite(data, 512, 1, outptr);
        }
        else if(writing == 1)
        {
            fwrite(data, 512, 1, outptr);
        }
        else
        {
        
        }
    }
    
    fclose(file);
       
    return 0;
}
