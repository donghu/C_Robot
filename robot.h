//
//  robot.h
//  oop244_a3
//
//  Created by Cheung Mac on 12-03-23.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include "command.h"

#ifndef oop244_a3_robot_h
#define oop244_a3_robot_h

class command; //forward declaration

class robot{
    char items [8][16];
    int treasure[3];
    char *name;
    command * commands;
    int command_in;
    int total_cmds;
    void memory(const char *);
    
public:
    robot(int num_of_cmds, const char *nm);
    robot( );
    const char* get_name( ) const;
    command get_command(int pos) const;
    int get_command_count() const;
    void set_item(const char item[ ], int pos);
    const char* get_item(int pos) const;
    void set_treasure(int pos, int num);
    int get_treasure(int pos) const;
    int readfile(const char fname[ ]);
    void operator+=(command &);//copy constructor
    int operator==(char *);// assignment operator
    
    int execute(char *str);
    robot(const robot &); 
    void operator=(const robot &);
    ~robot();
};


#endif
