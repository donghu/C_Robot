//
//  robot.cpp
//  oop244_a3
//
//  Created by Cheung Mac on 12-03-31.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <cstring>
#include <iostream>
#include "robot.h"

using namespace std;

void robot::memory(const char *p) {
    int len = (p == NULL) ? 0 : int(strlen(p));
    
    try {
        name = new char[len + 1];
    }
    catch(std::bad_alloc) {
        cout << "Error allocating " << len + 1 << " bytes of memory\n";
        name = NULL;
    }
    if(name) {
        if(p == NULL)
            strcpy(name, "");
        else
            strcpy(name, p);
    }
}


robot::robot(int num_of_cmds, const char *nm){
    total_cmds=num_of_cmds;
    command_in=0;
    commands = new (nothrow) command[num_of_cmds];
    memory(nm);
    
    for (int i=0; i<8; i++) {
        strcpy(items[i], "");
    }
    
    for (int j=0; j<3; j++){
        treasure[j] =0;
    }
}


robot::robot(){
    total_cmds=15;
    command_in=0;
    commands = new (nothrow) command[total_cmds];
    memory("univac.dat");
    for(int i=0;i<3;i++){
        this->treasure[i]=0;
    }
    for (int j=0; j< 8; j++){
        strcpy(items[j], "");
    }
}


//This function will be used to return the robot's name.
const char* robot::get_name( ) const{
    return name;
}


//This function returns the command at position "pos" (where a "pos" value
//of 0 means the first command). The function returns a default command if
//"pos" does not reference one of the robot's commands.
command robot::get_command(int pos) const{
    if (pos >=0 && pos < command_in){
        return commands[pos];
    }else{
        return commands[0];//command()
    }
}


//This is is used to return the number of command objects currently
//being stored in the robot.
int robot::get_command_count() const{
    return command_in;
}


//This function will copy the string 'item' into your array of "item"
//strings at position 'pos' provided that 'pos' is within the bounds of
//your array.
void robot::set_item(const char item[ ], int pos){
    if (pos >=0 && pos <8) {
        strcpy(items[pos], item);
    }
}


//This function returns the string item located at position 'pos',
//once again making sure that the value 'pos' is within the bounds of
//your array of "item" strings.
const char* robot::get_item(int pos) const{
		const char * ret =((pos >=0 && pos <8)?items[pos]: NULL);    
    return ret;//if out of bound. what should we return?
}


//This function adds the value stored in 'num' to the array of 'silver'
//'gold', or 'platinum' pieces being stored by the robot.
void robot::set_treasure(int pos, int num){
    if (pos >=0 && pos <3) {
        treasure[pos] = num;
    }
}


//This function simply returns the treasure (silver, gold, or platinum)
//being stored by voyager.
int robot::get_treasure(int pos) const{
	int ret = -1;
	if (pos >=0 && pos <3) 
    ret =  treasure[pos];
  return ret;
}


//This function reads lines from the file named in the string "fname" and
//adds them to the end of the list of commands stored by the robot.
int robot::readfile(const char fname[ ]){
    char record[162];
    int num_inst=0;
    
    FILE *fp;
    fp = fopen(fname, "r");
    if (fp == NULL) {
        cerr<<"Can not open the file"<< endl;
    }else{      //If there are more records in the file, ignore the rest
        //while (get_command_count() <= total_cmds && fgets(record, 161, fp) != NULL) {
        //while (command_in < total_cmds && fgets(record, 161, fp) != NULL) { 
        while (command_in < total_cmds && fscanf(fp, "%161[^\n]\n", record)==1) { //
            commands[command_in].init(record);//add them to commands
            num_inst++;
            command_in++;
        }
        fclose(fp);
    }
    return num_inst;
}


void robot::operator+=(command& add_cmd){//note: it's not reference.
    if (command_in <total_cmds) {
        commands[get_command_count()] = add_cmd;
        command_in++;
        //cout << "command_in in +=operator is: " << command_in << endl;
    }
}

int robot::operator==(char * str){
    int value=0;
    int n1=1;
    int n2=0;
    int flag=0;
    long len=strlen(str);
    char temp[len+4];
    strcpy(temp,  str);
    strcat(temp, " xx");
    
    for (; n1 <= get_command_count() && flag==0; n1++) {
        n2 = commands[n1-1].valid_command(temp)-1;
        if (n2>=0) {
            value=(n1*10)+n2;
            flag=1;
            break;
        }
    }return value;
}

int robot::execute(char *str){
    char tempSt[strlen(str)+1];//April 08 2012    
    bool keepgoing = false;
    //char temp1St[strlen(str)+1];//April 08 2012
    strcpy(tempSt, str);
    //strcat(tempSt," xx");
    //strcpy(temp1St, str);
    //cout << "temp string is: " << tempSt << endl;
    //int returnValue = 0;
    FILE * fpw;
    //bool flag = false;
    //fpw = fopen(name, "w");
    fpw = fopen(get_name(), "a");
    //cout << "writing file name is : " << get_name()<<endl;
    if (fpw == NULL) {
        cerr<<"Can not open file"<<endl;
    }else{
        
        if (*this == tempSt) {
            fprintf(fpw, "%s\n", tempSt);
            keepgoing = true;
        }
    }
    fclose(fpw);
    
    return keepgoing;       
}

robot::robot(const robot &rhs){
    //cout << "calling the copy constructor" << endl;
    *this = rhs;
    /*for (int i=0; i<3; i++) {
        treasure[i]=rhs.treasure[i];
    }
    for (int j=0; j< 8; j++){
        strncpy(items[j],rhs.items[j],15);
        items[j][15]='\0';
        
    }
    if (rhs.name !=NULL) {
        memory(rhs.name);
    }//else name=NULL;//April 08 2012
    
    if (rhs.commands !=NULL) {
        commands = new (nothrow) command();
        commands = rhs.commands;
    }else commands=NULL;
    
    command_in=rhs.command_in;
    total_cmds=rhs.total_cmds;*/
    
}

void robot::operator=(const robot &rhs){
    cout << "calling the =operator" << endl;

    if (this != &rhs) {
        int i=0;
        for(i=0;i<3;i++){
            this->treasure[i]=rhs.treasure[i];
        }
        
        for (int j=0; j< 8; j++){
            strncpy(items[j],rhs.items[j],15);
            items[j][15]='\0';
        }
        
        if(this->commands!=NULL) {
            delete this->commands;
            this->commands=NULL;
        }
        
        if(rhs.commands!=NULL){
            this->commands = new command[rhs.total_cmds];
            this->commands = rhs.commands;
        }else commands=NULL;
        
        command_in=rhs.command_in;
        total_cmds=rhs.total_cmds;
        if (name != NULL) {
            delete [] name;
            name=NULL;
        }
        if (rhs.name!= NULL) {
            memory(rhs.name);
        }else memory("univac.dat");//April 08 2012
        
    }
    
}

robot::~robot(){
    if (commands!=NULL) {
        cout << "deleting the commands" << endl;
        delete [] commands;
        commands =NULL;
    }
    if(name !=NULL){
        cout << "deleting the name" << endl;
        delete [] name;
        name=NULL;
    }
}










