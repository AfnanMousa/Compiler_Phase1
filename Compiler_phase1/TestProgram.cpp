#include "TestProgram.h"
#include <iostream>
#include <bits/stdc++.h>
#include <regex>
#include <iterator>
using namespace std;

bool split_spc (int i, string str){
     if (i==0 || i == str.length()-1) return 0;
     return isalpha(str[i-1]) && isalpha(str[i+1]);
}
string removeSpaces(string str){
	string new_str="";
	for (int i = 0; i<str.length(); i++) {
		if (str.at(i) != ' ' || (str.at(i) == ' ' && split_spc(i, str)))
			new_str.push_back(str.at(i));
	}
	new_str.push_back ('\0');
	return new_str;
}



pair<bool,string> check_regex(string x, map<string, int> next)
{
    pair<bool, string> output = {false,""};
    for (auto item : next)
    {
        string y = "["+item.first+"]";
        regex temp (y);//("(sub)(.*)");  // !=  item.first
        cout<<item.first<<endl;
        cout<<x<<endl;  //a
        if (regex_match(x, temp)) // matched
        {
            output.first = true;
            output.second += item.first;
            //cout<<output.first<<endl;
            break;
        }
    }
    return output;
}

void validation(map<int, DFA_Graph> graph, string word) {
    int state_id = 1;
    int last_accepted_state = -1; //id of accepted
    int last_state; // last id reached
    bool flag = true;
    for (int i = 0; i < word.size(); i++)
    {
        map<string, int> next = graph[state_id].next_state;
        string temp="";
        temp+= word[i];
        pair<bool, string> result = check_regex(temp, next);
        //cout<<result.second<<endl;
        if (result.first) //found the char in DFA.
        {
            if (graph[next[result.second]].acceptance_state) last_accepted_state = next[result.second];

            last_state=next[result.second];
            state_id=next[result.second];
        }
        else
        {
            flag = false;
            break;
        }
    }
    if (flag&&last_accepted_state==last_state)
    {
        cout <<"accepted word : " <<graph[last_accepted_state].name << endl;
    }
    else
    {
        //should call Recovary function .
        cout <<"not accepted word" << endl;
    }
}
void Parse(map<int, DFA_Graph> graph,vector <string> splitted )
{
    for(auto it:splitted)
        validation(graph,it);
}

void split(string program,map<int, DFA_Graph> graph) {
    vector <string> splitted;
    smatch match;
    regex rgx("(\\w+)|(!=)|(==)|(<=)|(>=)|(>)|(<)|[*+-\\=,;\\(\\){}]");
    program = removeSpaces(program);
       for( sregex_iterator it(program.begin(), program.end(), rgx), it_end; it != it_end; ++it ){
           splitted.push_back ((*it)[0]);
       }
    Parse(graph,splitted);

    //return splitted;
}


