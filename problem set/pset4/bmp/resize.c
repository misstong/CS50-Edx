/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
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
    int n=atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

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
    
    //original info
    DWORD bfsize=bf.bfSize,imageSize=bi.biSizeImage;
    LONG width=bi.biWidth,height=bi.biHeight;
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //printf("---original infomation---\n");
   // printf("width:%d,height:%d,bfsize:%d,imagesize:%d\n",width,height,bfsize,imageSize);
    
    //resized info
    LONG widthResized=width*n,heightResized=height*n;
    int paddingResized=(4 - (widthResized * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //change the header
    bi.biWidth=widthResized;
    bi.biHeight=heightResized;
    bi.biSizeImage=widthResized*abs(heightResized)*3+paddingResized*abs(heightResized);
    bf.bfSize=bi.biSizeImage+54;
   // printf("---resized infomation---\n");
    //printf("width:%d,height:%d,bfsize:%d,imagesize:%d\n",bi.biWidth,bi.biHeight,bf.bfSize,bi.biSizeImage);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(height); i < biHeight; i++)
    {
        int back=width*3+padding;
        for(int m=0;m<n;m++){
            
        
            // iterate over pixels in scanline
            for (int j = 0; j < width; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                // write RGB triple to outfile
                for(int k=0;k<n;k++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
    
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < paddingResized; k++)
            {
                fputc(0x00, outptr);
            }
            
            
            fseek(inptr,-back,SEEK_CUR);
       }
        fseek(inptr,back,SEEK_CUR);
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
