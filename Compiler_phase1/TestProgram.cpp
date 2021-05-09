#include "TestProgram.h"
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <regex>
#include <iterator>
using namespace std;

bool split_spc (int i, string str){
     if (i==0 || i == str.length()-1) return 0;
     return (isdigit(str[i-1]) ||isalpha(str[i-1])) && (isdigit(str[i+1]) ||isalpha(str[i+1]));
}
string removeSpaces(string str){
	string new_str="";
	for (int i = 0; i<str.length(); i++) {
		if (str.at(i) != ' ' || (str.at(i) == ' ' && split_spc(i, str)) )
			new_str.push_back(str.at(i));
	}
	return new_str;
}



pair<bool,string> check_regex(string x, map<string, int> next)
{
    pair<bool, string> output = {false,""};
    for (auto item : next)
    {
        string y = "["+item.first+"]";
        regex temp (y);//("(sub)(.*)");  // !=  item.first
  //      cout<<item.first<<endl;
  //      cout<<x<<endl;  //a
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

void validation(map<int, DFA_Graph> graph, string word,vector <char> punctuation, vector <string> keyWords) {
    int state_id = 1;
    int last_accepted_state = 0; //id of accepted
    int last_state; // last id reached
    bool flag = true;
    int new_start = 0;
    for (int i = 0; i < word.size(); i++)
    {
        map<string, int> next = graph[state_id].next_state;
        string temp="";
        temp+= word[i];
       // cout<<"temp is   ";
        if(find(keyWords.begin(), keyWords.end(), word.substr(0,i+1)) != keyWords.end()){
            if(i+1==word.size()||(i+1<word.size()&&find(punctuation.begin(), punctuation.end(), word[i+1]) != punctuation.end()))
            {
               cout<<word.substr(0,i+1)<<endl;
                new_start=i+1;
                if(new_start<word.size()) {
                    validation(graph,  word.substr(new_start),punctuation,keyWords);
                    return;
                }
            }

        }
        pair<bool, string> result = check_regex(temp, next);
        if (result.first) //found the char in DFA.
        {
            if (graph[next[result.second]].acceptance_state){
                    last_accepted_state = next[result.second];
                    new_start = i+1 ;
            }

            last_state=next[result.second];
            state_id=next[result.second];
        }
        else
        {
            flag = false;
            if (i == 0){
                if(find(punctuation.begin(), punctuation.end(), temp[0]) != punctuation.end())
                    cout<<temp<<endl;
                else
                    cout<<"ERROR!!!"<<endl;

                if (i+1 < word.length()){
                    validation(graph,  word.substr(i+1),punctuation,keyWords);
                    return;
                }else
                    return;
            }else{
                //cout<<"the temp :"<<temp<<endl;
                if(find(keyWords.begin(), keyWords.end(), temp) != keyWords.end())
                    cout<<temp<<endl;
                else if (last_accepted_state > 0){
                    cout << word.substr(0, new_start) <<"  " <<"shimaa accepted word : " <<graph[last_accepted_state].name << endl;
                }
                validation(graph,  word.substr(new_start ),punctuation,keyWords);
                return;
       //         break;
            }
        }
    }
    if (flag&&last_accepted_state==last_state)
    {
        cout << word <<"  " <<"accepted word : " <<graph[last_accepted_state].name << endl;
    }
    else{
        //should call Recovary function .
        cout <<word <<"  "<<"not accepted word" << endl;
    }
}
void Parse(map<int, DFA_Graph> graph, vector <char> punctuation, vector <string> keyWords, vector <string> splitted )
{
    for(auto it:splitted){
        if (count (punctuation.begin(), punctuation.end(), it[0])){
            cout << it[0]<<endl;
        }else if (count (keyWords.begin(),keyWords.end(), it)){
            cout << it <<endl;
        }else{
            validation(graph,it,punctuation,keyWords);
        }
    }
}

vector <string> remove_space_from_Word(string str)
{
    // Used to split string around spaces.
    vector <string> splitted;
    istringstream ss(str);

    string word; // for storing each word

    // Traverse through all words
    // while loop till we get
    // strings to store in string word
    while (ss >> word)
    {
        splitted.push_back(word);
    }
  return splitted;
}

void split(string program, vector <char> punctuation, vector <string> keyWords, map<int, DFA_Graph> graph) {
    vector <string> splitted;
    smatch match;
    //regex rgx("(([0-9]+.[0-9]+(E[0-9]+)?)|[0-9]+)|(\\w)+|(!=)|(==)|(<=)|(>=)|(>)|(<)|[*+-\\=,;\\(\\){}]");
    //program = removeSpaces(program);
      // for( sregex_iterator it(program.begin(), program.end(), rgx), it_end; it != it_end; ++it ){

        //   splitted.push_back ((*it)[0]);
      // }
    splitted=remove_space_from_Word(program);
    string token = "";
    Parse(graph,punctuation, keyWords,splitted);

}
