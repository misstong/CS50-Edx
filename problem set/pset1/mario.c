#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("height:");
    int height;
    while(true)
    {
        height=GetInt();
        if (height>=0&&height<=23)
            break;
        printf("height:");
    }
    for(int i=1;i<=height;i++)
    {
        for(int j=0;j<height-i;j++)
            printf(" ");
            
        for(int k=0;k<i+1;k++)
            printf("#");
        
        printf("\n");
    }
}