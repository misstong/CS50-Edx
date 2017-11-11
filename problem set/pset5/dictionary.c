/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"

node* root;
unsigned int wordCount=0;

node* createNode(){
    node * t=(node*)malloc(sizeof(node));
    t->is_word=false;
    for(int i=0;i<27;i++){
        t->children[i]=NULL;
    }
    return t;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int i=0;
    node *t=root;
    while(word[i]!='\0'){
        char c=tolower(word[i]);
        if(isalpha(word[i])){
            if(t->children[c-'a']==NULL){
                return false;
            }
            else{
                t=t->children[c-'a'];
            }
        }else{
            
            if(t->children[26]==NULL){
                return false;
            }
            else{
                t=t->children[26];
            }
        }
        
        i++;   
    }
    if(t->is_word==true)
        return true;
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* fp=fopen(dictionary,"r");
    if(!fp){
        return false;
    }
    int n=LENGTH+2;
    char word[n];
    root=createNode();
    while(!feof(fp)){
        fgets(word,n,fp);
        
        if(!feof(fp)){
            int len=strlen(word);
            if(word[len-1]=='\n'){
                word[len-1]='\0';
                printf("delete enter\n");
            }
            printf("%s ",word);
            int i=0;
            node *t=root;
            while(word[i]!='\0'){
                if(isalpha(word[i])){
                    if(t->children[word[i]-'a']==NULL){
                        t->children[word[i]-'a']=createNode();
                        
                    }
                    t=t->children[word[i]-'a'];
                }
                else{
                    if(t->children[26]==NULL){
                        t->children[26]=createNode();
                    }
                    t=t->children[26];
                }
                i++;
                
            }
            t->is_word=true;
            wordCount+=1;
            
        }
    }
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if(root!=NULL)
        return wordCount;
    return 0;
}

bool destroy(node *t){
    if(t==NULL){
        return true;
    }else{
        for(int i=0;i<27;i++){
            destroy(t->children[i]);
        }
        free(t);
    }
    return true;
}
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    node *t=root;
    destroy(t);
    wordCount=0;
    return true;
}

int main()
{
     load("myfile.txt");
     bool b=check("ieeqwedakjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjkjhf");
     if(b)
        printf("\ndog exist\n");
     /*
     if(b)
        printf("dog exist\n");
    else
        printf("dog not exist\n");
        
    if(check("cat")){
        printf("cat exist\n");
    }
    else
        printf("cat not exist\n");
        
     if(check("caterpillar")){
        printf("caterpillar exist\n");
    }
    else
        printf("caterpillar not exist\n");
        */
    printf("\nsize is:%d",size());
    return 0;
}