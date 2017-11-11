#include <stdio.h>
FILE* fptr;
int main(){
	char fileLine[81];
	fptr=fopen("1.txt","rb");
	if(fptr!=0){
		while(!feof(fptr)){
			fgets(fileLine,81,fptr);
			if(!feof(fptr)){
				puts(fileLine);}
		}
	}
}