//
//  command.cpp
//  as2
//
//  Created by Cheung Mac on 12-02-26.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <string>
#include "command.h"
#include "fuction.c"
using namespace std;

command::command(){
    init();
}

command::command(char data[]){
    init(data);
}

void command::init(char data[]){
    long length=0;
    int i=0;
    int k=0;
    int flag=0;
    int l=0;
    int count=0;
    int m=0;
    memset(modifiers, '\0', sizeof(modifiers));
    memset(keyword, '\0', sizeof(keyword));
    length = strlen(data);
    
    for (i=0; i<length && flag==0; i++) {
        if (data[i]!=';' && data[i]!='\0') {
            keyword[m++]=data[i];
//            cout<<"keyword is : "<<keyword<<endl;
        }if (data[i]==';' || data[i]=='\0'){
            flag=1;
            break;
        }
    }
    
    
    if(flag==1){
        for(; i<length;i++){
            if (data[i]==';' && count<5) {
                k++;
                l=0;//reset l,so that the next word can start at position 0.
                count++;
            }else if (data[i]!=';' && count<5){
                modifiers[k-1][l++]=data[i];
            }
        }
    }
}

void command::init(){
    strcpy(keyword, "go");
    strcpy(modifiers[0], "north");
    strcpy(modifiers[1], "south");
    strcpy(modifiers[2], "east");
    strcpy(modifiers[3], "west");
    strcpy(modifiers[4], "start");
}

//This function returns the number of modifiers contained in the command.
int command::modifier_count(){
    int count=0;
    while(modifiers[count][0] && count<5){
        count++;
    }
    return count;
}


int command::valid_command(char phrase[]){
    int isKeyword=0;
    int isModifiers=0;
    int i=0;
    for (i=0; i<words(phrase) && isKeyword==0; i++) {
        isKeyword=match(keyword, phrase, i);
        //cout << "isKeyword is: " << isKeyword << endl;
    }
    if (isKeyword==1) {
        for (; i<=words(phrase); i++) {
            if (match(modifiers[0], phrase, i)) {isModifiers=1;break;}
            if (match(modifiers[1], phrase, i)) {isModifiers=2;break;}
            if (match(modifiers[2], phrase, i)) {isModifiers=3;break;}
            if (match(modifiers[3], phrase, i)) {isModifiers=4;break;}
            if (match(modifiers[4], phrase, i)) {isModifiers=5;break;}
        }
    }
    //cout << "--valid_command-- return value is: " << isKeyword+isModifiers << endl;
    return isKeyword+isModifiers;
}

void command::get_keyword(char s[]){
    strcpy(s, keyword);
    //
    //cout << "keyword is get_keyword is:" << keyword<<endl;
}

void command::get_modifier(char s[], int pos){
    if(pos>=0 && pos<5){
        strcpy(s, modifiers[pos]);
    }else{
        strcpy(s, "");
    }
}




