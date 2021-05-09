#ifndef TESTPROGRAM_H
#define TESTPROGRAM_H

#include <iostream>
#include <vector>
#include <map>
#include "minimization.h"
//#include "DFA.h"
#include <bits/stdc++.h>
using namespace std;

void split (string program, vector <char> punctuation, vector <string> keyWords, map<int, DFA_Graph> graph);
void validation(map<int, DFA_Graph> graph, string word,vector <char> punctuation, vector <string> keyWords);

#endif
