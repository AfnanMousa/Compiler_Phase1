#include "input_rules.h"
#include "parse_rules.h"
#include "interface.h"
#include "minimization.h"
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
    for (auto edg: st.transition){
        cout << st.id <<" "<< (edg.first)->id <<" " << edg.second << "     "<<(edg.first)->accepted<<"     "<<(edg.first)->accepted_language<<endl;
        if (!visit[edg.first->id]){
            display (*(edg.first));
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
		display(*a.start);
        memset(visit, 0, sizeof(visit));
        cout << endl;
		Languages.push_back({parts[0],a});
	}else if (line.find(':') < line.length()) {
		cout << "expression \n";
		line = parse.removeExtraSpaces(line);
        cout << line<<endl;
		parts = parse.splits(line, ":");
		automata a ;
		a = cal.language_NFA (parts[1],Languages);
		display(*a.start);
        memset(visit, 0, sizeof(visit));
        cout << endl;
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
    convert(final_result);
	return 0;
}
