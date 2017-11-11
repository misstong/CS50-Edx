#include <stdio.h>  
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
//#include <dirent.h>  
  
  typedef char BYTE;
 bool load(FILE* file, BYTE** content, size_t* length);
 char* indexes(const char* path);
 const char* lookup(const char* path);
 bool parse(const char* line, char* abs_path, char* query);
int main()  
{  
    //int n;  
    //struct dirent **namelist;  
       
   // n=scandir("./",&namelist,0,0);  
   // while(n--)  
    //{  
      //  printf("%s\n",namelist[n]->d_name);  
    //}  
   //printf("%s","/index");
   //char path[15]="t/";
   //printf("%s",indexes(path));
   char *content=(char*)malloc(2);
   //size_t len;
   //FILE *f=fopen("1.txt","r");
   //load(f,&content,&len);
  // printf("%s %d",content,(int)len);
  int s=(int)sizeof(char);
  int j=(int)sizeof(content);
   printf("size %d %d",s,j); 
  // int* p = (int *) malloc ( sizeof(int) * 100 );
  // memset(p,0,100);
   //printf("size of int %d size of p %d",(int)sizeof(int),(int)sizeof(p));
 

 ///const char * path="a/b/c.jpg";
 //const char* type = lookup(path);
// printf("%s\n",type);
 // if (strcasecmp("text/x-php", type) == 0)
 //                   {
 //                        printf("ok");
  //                  }


    /*char* line="GET /df/d?q=d HTTP/1.1\r\n";
    char abs[100],query[100];
    bool b=parse(line,abs,query);
    if(b){
        printf("%s\n%s",abs,query);
    }*/
    return 0;  
}  


bool load(FILE* file, BYTE** content, size_t* length)
{
    // TODO
    BYTE c;
    int i=0;
    BYTE *result=(BYTE*)malloc(10);
    printf("size of result:%d size of byte:%d\n",(int)sizeof(result),(int)sizeof(BYTE));
    while(fread(&c,1,1,file)==1){
        i++;
        if(i>=sizeof(result)/sizeof(BYTE)){
            result=realloc(result,2*(int)sizeof(result));
            result[i-1]=c;
            printf("i is %d size of result %d\n",i,2*(int)sizeof(result));
        }else{
            result[i-1]=c;
        }
        printf("size of result:%d\n",(int)sizeof(result));
    }
    *length=i;
    result[i]='\0';
    *content=result;
    printf("size of result end:%d\n",(int)sizeof(result));
    return true;
}
char* indexes(const char* path)
{
    // TODO
     // ensure path is readable and executable
    char *result;
    
    // open directory
    DIR* dir = opendir(path);
    if (dir == NULL)
    {
        return NULL;
    }
    
    // iterate over directory entries
    struct dirent** namelist = NULL;
    int n = scandir(path, &namelist, NULL, 0);
    for (int i = 0; i < n; i++)
    {
        //printf("%s\n",namelist[i]->d_name);
        if(strcmp(namelist[i]->d_name, "index.php")==0){
            int len=(int)strlen(path)+(int)strlen("/index.php")+1;
            result=(char*)malloc(len*sizeof(char));
            strcpy(result,path);
            strcat(result,"/index.php");
            result[len]='\0';
            return result;
            
        }
    }
    for (int i = 0; i < n; i++){
        if(strcmp(namelist[i]->d_name, "index.html")==0){
             int len=(int)strlen(path)+(int)strlen("/index.html")+1;
            result=(char*)malloc(len*sizeof(char));
            
            strcpy(result,path);
            strcat(result,"/index.html");
            result[len-1]='\0';
            printf("%d\n",len);
            return result;
        }
    }
    return NULL;
}

bool parse(const char* line, char* abs_path, char* query)
{
    // TODO
    //error(501);
    //return false;
    char* fstSp=strchr(line,' ');
    char* sndSp=strchr(fstSp+1,' ');
    char* crlf=strstr(line,"\r\n");
    
    if(fstSp==NULL||sndSp==NULL||crlf==NULL||strchr(sndSp+1,' ')!=NULL||!(sndSp-fstSp>1)){
        //error(400);
        return false;
    }
    
    char method[fstSp-line+1];
    strncpy(method,line,fstSp-line);
    method[fstSp-line]='\0';
    printf("%s\n",method);
    if(strcmp(method,"GET")!=0){
        //error(405);
        return false;
    }
    
     char protocol[crlf-sndSp];
    strncpy(protocol,sndSp+1,crlf-sndSp-1);
    protocol[crlf-sndSp-1]='\0';
    printf("%s\n",protocol);
    if(strcmp(protocol,"HTTP/1.1")!=0){
        //error(505);
        return false;
    }
   // printf("%s\n",protocol);
    
    char reqTarget[sndSp-fstSp];
    strncpy(reqTarget,fstSp+1,sndSp-fstSp-1);
    reqTarget[sndSp-fstSp-1]='\0';
    printf("%s\n",reqTarget);
    if(reqTarget[0]!='/'){
        //error(501);
        return false;
    }
    if(strchr(reqTarget,'\"')!=NULL){
        //error(400);
        return false;
    }
    
    if(strstr(reqTarget,".exe")!=NULL){
        //error(501);
        return false;
    }
    char *c=strchr(reqTarget,'?');
    if(c==NULL){
        strcpy(abs_path,reqTarget);
        query[0]='\0';
    }else if(*(c+1)=='\0'){
        *c='\0';
        strcpy(abs_path,reqTarget);
        query[0]='\0';
    }else{
        strcpy(query,c+1);
        *c='\0';
        strcpy(abs_path,reqTarget);
    }
    return true;
    
}
const char* lookup(const char* path)
{
    // TODO
    char* p=strrchr(path,'.');
    char ends[6];
    strcpy(ends,p);
    if(strcasecmp(ends,".css")==0){
        return "text/css";
    }else if(strcasecmp(ends,".html")==0){
        return "text/html";
    }else if(strcasecmp(ends,".gif")==0){
        return "image/gif";
    }else if(strcasecmp(ends,".ico")==0){
        return "image/x-icon";
    }else if(strcasecmp(ends,".jpg")==0){
        return "image/jpeg";
    }else if(strcasecmp(ends,".js")==0){
        return "text/javascript";
    }else if(strcasecmp(ends,".php")==0){
        return "text/x-php";
    }else if(strcasecmp(ends,".png")==0){
        return "image/png";
    }else {
        return NULL;
    }
    
}

