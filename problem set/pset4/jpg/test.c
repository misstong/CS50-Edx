#include <stdio.h>
#include <stdlib.h>
int main(){
    FILE* fptr=fopen("1.txt","r");
   // char c[5];
    int c;
    fread(&c,1,5,fptr);
    //c[4]='\0';
    //puts(c);
   // for(int i=0;i<4;i++)
     //   printf("%x",c[i]);
     printf("%x",c);
    fclose(fptr);
    
}