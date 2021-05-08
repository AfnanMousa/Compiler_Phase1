#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <bits/stdc++.h>
using namespace std;

struct state{
    int id = 0;
    state * related;
    bool accepted = false;
    string accepted_language = "";
    int priority = 0;
    vector <pair<state*, string > > transition ;
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
