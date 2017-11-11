#include <stdio.h>
#include <string.h>

#include "dictionary.h"

#define DICTIONARY "myfile.txt"
int main()
{
    /*FILE * pFile;
    char mystring [100];

    pFile = fopen ("myfile.txt" , "r");
    if (pFile == NULL)
        perror ("Error opening file");
    else {
        if ( fgets (mystring , 15 , pFile) != NULL )
        {
            int n=(int)strlen(mystring);
            mystring[n-1]='\0';
            
        }
            printf("%s:%d",mystring,(int)strlen(mystring));
        fclose (pFile);
    }*/
    //char *dic="myfile.txt";
    if(load(DICTIONARY)){
     printf("completed");   
    }
    return 0;
}