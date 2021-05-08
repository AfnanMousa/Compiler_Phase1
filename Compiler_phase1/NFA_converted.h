#ifndef NFA_CONVERTED_H
#define NFA_CONVERTED_H

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*struct input{
    string name;
    string content;
};*/

struct Transition{
    //struct input
    string input_symbol;
    struct NFA_State* next;
};

struct NFA_State {
    int id;
    bool accept_state_flag = false; //0 not accepting ,1 for accepting.
    string name="";
    vector <Transition> transitions;
};

#endif
