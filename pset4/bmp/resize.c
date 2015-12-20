/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP to 1 to n times the size of the original with n <= 100
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    int n = atoi(argv[1]);
    
    if(n < 1 || n > 100)
    {
        printf("Invalid n\n");
        return 4;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    BITMAPFILEHEADER newbf = bf;
    BITMAPINFOHEADER newbi = bi;
    
    newbi.biWidth = n*bi.biWidth;
    newbi.biHeight = n*bi.biHeight;
    
    int newpadding =  (4 - (newbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    newbi.biSizeImage = (newbi.biWidth*3+newpadding)*abs(newbi.biHeight); //includes padding, size of the image
    newbf.bfSize = newbi.biSizeImage + newbf.bfOffBits; //includes padding, size of the whole file including headers
    

    // write outfile's BITMAPFILEHEADER
    fwrite(&newbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&newbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        RGBTRIPLE * array_scanline = malloc(sizeof(RGBTRIPLE)*newbi.biWidth);
        
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            for(int k = 0; k < n; k++)
            {
                array_scanline[j*n+k] = triple;
            }


        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
        
        for(int j = 0; j < n; j++)
        {
            fwrite(array_scanline, sizeof(RGBTRIPLE)*newbi.biWidth, 1, outptr);
            for (int k = 0; k < newpadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
        free(array_scanline);       
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
