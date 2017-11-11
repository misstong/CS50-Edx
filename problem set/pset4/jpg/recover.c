/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
int isStartOfJpg(int buffer[]);
int main()
{
    //open the file
    FILE* inptr=fopen("card.raw","r");
    if (inptr == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }
    
    int buffer[128];
   // printf("size of int:%d\n",(int)sizeof(buffer));
    int n=0;
    FILE* outptr=NULL;
    while(fread(buffer,1,512,inptr)==512){
        if(isStartOfJpg(buffer)){
           // printf("%x\n",buffer[0]);
            char title[10];
            sprintf(title,"%03d.jpg",n++);
            //printf("title is :%s",title);
            if(outptr!=NULL)
                fclose(outptr);
            outptr=fopen(title,"w");
            fwrite(buffer,1,512,outptr);
            
        }
        else{
           // printf("not the start %i\n",i++);
           // printf("%x\n",buffer[0]);
            if(outptr!=NULL){
                fwrite(buffer,1,512,outptr);
            }
            
        }
    }
    fclose(outptr);
    
}
int isStartOfJpg(int buffer[]){
   // if(buffer[0]==0xff&&buffer[1]==0xd8&&buffer[2]==0xff&&(buffer[3]&0xf0)==0xe0)
   if((buffer[0]&0xf0ffffff)==0xe0ffd8ff)
        return 1;
    return 0;
}
