//  fuction.c
//  OOP244B ASSIGNMENT#1
//  Created by Donghu Zhang(064-361-108) on 12-02-04.
//  Instructor: Danny Abesdris
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <string>
using namespace std;
#define CURR sentence[i]
#define POSI sentence[index+j]

int words(char sentence[]);
int match(char str[ ], char sentence[ ], int n);
int wordsIndex(char sentence[],int n);

int words(char sentence[]){
    int num_of_words = 0;
    int i = 0;
    int flag = 0;
    while(sentence[i]!='\0'){
        if (flag ==0){
            if((CURR==' ')|| (CURR=='\n')|| (CURR=='\t')){
                ;
            }else 
                flag=1; 
        }else if (flag==1){
            if((CURR==' ')|| (CURR=='\n')|| (CURR=='\t')){
                flag =0;
                num_of_words++;
            }
        }
        i++;
    }
    if(flag==1)
        num_of_words++;
    return num_of_words;
} 

//find the index of words
int wordsIndex(char sentence[],int n){
    int num_of_words = 0;
    int i = 0;
    int flag = 0;
    while(CURR!='\0'){
        if (flag ==0){
            if((CURR==' ')|| (CURR=='\n')|| (CURR=='\t')){
                ;
            }else {
                flag=1;
                if (n == num_of_words+1) {
                    return i;
                }                
            }
        }else if (flag==1){
            if((CURR==' ')|| (CURR=='\n')|| (CURR=='\t')){
                flag =0;
                num_of_words++;
            }
        }
        i++;
    }
    if(flag==1)
        num_of_words++;
    return -1;
} 


int match(char str[ ], char sentence[ ], int n){
    int j = 0;
    int flag = 0;
    
    if (strlen(str)==0) {
        flag=0;
        //cout<<"match out 1."<<endl;
        return flag;
    }
    int index = wordsIndex(sentence, n);
    for (j=0; j<strlen(str) ; j++) {
        if (tolower(POSI)!=tolower(str[j])) {//change all case to lower case
            flag=0;
            /*cout<<"match out second."<<endl;
            cout<<"sentence::"<<sentence<<endl;
            cout<<"index::"<<index<<endl;
            cout<<"j::"<<j<<endl;
            cout<<"tolower(POSI)::"<<&POSI<<endl;
            cout<<"tolower(str[j]::"<<str<<endl;*/
            return flag;
        }
    }
    flag = 1;
    if (POSI=='\0' || POSI ==' '|| POSI =='\t'|| POSI =='\n'||str[j-1]==' '||str[j-1]=='\t'||str[j-1]=='\n'){
        return flag;//if reached end of line
    }
    
    return 0;    
}