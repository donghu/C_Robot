//
//  command.h
//  as2
//
//  Created by Cheung Mac on 12-02-26.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef as2_command_h
#define as2_command_h

class command{
    char keyword[41];
    char modifiers[5][21];
public:
    command();
    command(char data[]);
    void init(char data[]);
    void init();
    int modifier_count();
    int valid_command(char phrase[]);
    void get_keyword(char s[]);
    void get_modifier(char s[], int pos);
};

#endif
