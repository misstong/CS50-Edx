#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    string name;
    char initial[10];
    int isspace=0,index=0;
    
    //printf("Enter your name!\n");
    name=GetString();
    //printf("%s\n",name);
    
    initial[index++]=toupper(name[0]);
    for(int i=1;i<strlen(name);i++)
    {
        if(isalpha(name[i])&&isspace){
            initial[index++]=toupper(name[i]);
            isspace=0;
        }
        else if(name[i]==' '){
            isspace=1;
        }
    }
    
    for(int j=0;j<index;j++)
        printf("%c",initial[j]);
    printf("\n");
   
    
    
    
    
    
    
    
    
}