#include "parse_rules.h"
#include "structures.h"
#include "calc_rgx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

parse_rules parse;
calc_rgx cal;
vector<pair<string,automata> > Languages;
vector <pair<string,automata> > patterns;
vector <string> keyWords;
vector <char> punctuation;
