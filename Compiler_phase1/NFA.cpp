#include "NFA.h"
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

NFA::NFA()
{
    //ctor
}
//automata res;
//int cnt = 0;
bool vis[100];
void display_ (state st){
    vis[st.id] = 1;
  //  cout << st.id <<" " << st.transition.size()<<endl;
    for (auto edg: st.transition){
            cout << st.id <<" "<< (edg.first)->id <<" " << edg.second  <<"     "<<(edg.first)->accepted<<"     "<<(edg.first)->accepted_language<<endl;
        if (!vis[edg.first->id]){
            display_ (*(edg.first));
        }
    }
}

automata NFA::basic_NFA (string a, automata base){

 //   struct automata base;
    base.start->id = cnt++;
    base.end_->id = cnt++ ;
    base.start->transition.push_back({(base.end_), a});

    return base;
}

automata NFA::and_NFA (automata* automata1, automata* automata2){

    automata1-> end_->transition.push_back({(automata2->start),"\\L" });
    automata result;
    result.start =  automata1->start;
    result.end_ = automata2->end_;
    return result;
}


automata NFA::or_NFA (automata* automata1, automata* automata2, state* new_start, state* new_end){
 /*   cout << "OOOORRRR"<<endl;
    display_(*(automata1->start));
    cout << endl;
    memset(vis, 0, sizeof(vis));
*/
    new_start->id = cnt++;
    new_end->id = cnt++;
   // cout << new_start.id<<" size: " <<new_start.transition.size()<<endl;
    new_start->transition.push_back({(automata1->start), "\\L"});
    new_start->transition.push_back({(automata2->start), "\\L"});
    automata1->end_->transition.push_back({(new_end), "\\L"});
    automata2->end_->transition.push_back({(new_end), "\\L"});

    automata result;
    result.start = new_start;
    result.end_ = new_end;


 /* display_(*(result.start));
    cout << endl;
    memset(vis, 0, sizeof(vis));
*/
    return result;
}

automata NFA::Closure(automata * automata1, state* new_start, state* new_end, char c){

    new_start->id = cnt++;
    new_end->id = cnt++;
    automata result;
    automata1->end_->transition.push_back({(automata1->start), "\\L"});  //positive & kleene
    /*if (c == '+'){
        result = *automata1;
        return result;
    }*/
    new_start->transition.push_back({(automata1->start), "\\L"});
    automata1->end_->transition.push_back({new_end, "\\L"});
    if (c == '*')
        new_start->transition.push_back({new_end, "\\L"});
    result.start = new_start;
    result.end_ = new_end;
    return result;
}

automata NFA::combined_NFA(vector <pair<string,automata>> patterns, state* new_start){
    automata result;
    new_start->id = cnt++;
    for (int p=0;p<patterns.size();p++){
         state *temp = patterns[p].second.end_;
         temp->accepted = true;
         temp->accepted_language = patterns[p].first;
         temp->priority = p+1;
         new_start->transition.push_back({(patterns[p].second.start), "\\L"});
    }
    result.start = new_start;
    return result;
}
