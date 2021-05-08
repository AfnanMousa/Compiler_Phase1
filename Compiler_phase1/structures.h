#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <bits/stdc++.h>
using namespace std;

struct state{
    int id = 0;
    state * related;
    bool accepted = false;
    string accepted_language = "";
    vector <pair<state*, string > > transition ;
};

struct edge{
    state from;
    state to;
    string symbol;
};

struct automata{
    state* start = new state;
    state* end_  = new state;
};

class structures
{
    public:
        structures();


    protected:

    private:
};

#endif // STRUCTURES_H
