#include "input_rules.h"
#include "parse_rules.h"
#include "minimization.h"
#include "TestProgram.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
bool visit[1000];
void display (state st){
    visit[st.id] = 1;
   // cout << st.id <<" " << st.transition.size()<<endl;
    for (auto edg: st.transitions){
       cout << st.id <<" "<< (edg.next)->id <<" " << edg.input_symbol << "     "<<(edg.next)->accepted<<"     "<<(edg.next)->accepted_language <<"   " << (edg.next)->priority<<endl;
        if (!visit[edg.next->id]){
            display (*(edg.next));
        }
    }
}

void extract(string line) {
	vector<string> parts;
	if ((line.find('=') < line.length()) && (line.at(line.find('=')-1) != '\\') && !(line.find(':') < line.length())){
        cout << "definition \n";
        line = parse.removeExtraSpaces(line);
        cout <<line<<endl;
		parts = parse.splits(line, "=");
		automata a ;
		a = cal.language_NFA(parts[1],Languages);
		Languages.push_back({parts[0],a});
	}else if (line.find(':') < line.length()) {
		cout << "expression \n";
		line = parse.removeExtraSpaces(line);
        cout << line<<endl;
		parts = parse.splits(line, ":");
		automata a ;
		a = cal.language_NFA (parts[1],Languages);
		patterns.push_back({parts[0],a});
	}
	else if(line[0]=='{'){
		cout << "keyword\n";
       // line = parse.removeSpaces(line);
		line.erase(remove(line.begin(), line.end(), '{'), line.end());
		line.erase(remove(line.begin(), line.end(), '}'), line.end());
		cout << line << '\n';
		parts = parse.splits(line, " ");
		for (int i = 0;i < parts.size(); i++) {
				keyWords.push_back(parts[i]);
		}
	}else if(line[0]=='['){
		cout << "punctuation\n";
        line = parse.removeSpaces(line);
		line.erase(remove(line.begin(), line.end(), '['), line.end());
		line.erase(remove(line.begin(), line.end(), ']'), line.end());
		line.erase(remove(line.begin(), line.end(), ' '), line.end());
		cout << line << '\n';
		for (int i = 0;i < line.size();i++) {
                if (line[i]!='\\' || (line[i]=='\\'  && line[i+1] == '\\' )){
                    punctuation.push_back(line[i]);
                }
		}
	}

}
int main(){
	fstream my_file;
	my_file.open("rules.txt", ios::in);

	if (!my_file)
		cout << "No such file";
	else {
		string line;
		while (getline(my_file, line)) { //read data from file object and put it into string.
           // line = parse.removeExtraSpaces(line);
			cout << line << "\n"; //print the data of the string
			extract(line);
			cout << "--------------------------\n";
		}
		cout << "keyWords : \n" ;
		for (int i = 0; i < keyWords.size(); i++)
			cout << keyWords[i]<<'\n';

        cout << "punctuation : \n";
        for (int i = 0; i < punctuation.size(); i++)
			cout << punctuation[i]<< '\n';

	}
	my_file.close();
	state *s=new state ;
	automata final_result = cal.combine(patterns,s);
	display(*final_result.start);
    memset(visit, 0, sizeof(visit));
    map<int, DFA_Graph> Final_Graph=Subset_Construction(final_result.start);

    int line_num = 1;
    my_file.open("test.txt", ios::in);
    if (!my_file)
		cout << "No such file";
	else {
		string line;
		while (getline(my_file, line)) { //read data from file object and put it into string.
           //cout << line_num <<"the line is : "<<line<<endl;
           line_num++;
           split(line, punctuation, keyWords,Final_Graph);

		}

	}
	my_file.close();


	return 0;
}
