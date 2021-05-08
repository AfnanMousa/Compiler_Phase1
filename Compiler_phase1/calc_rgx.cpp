#include "calc_rgx.h"
#include <bits/stdc++.h>
#include "structures.h"
using namespace std;
calc_rgx::calc_rgx()
{
}

int calc_rgx::find_language(string lang,vector<pair<string,automata> > Languages){
    for(int x=0;x<Languages.size();x++){
        if(Languages[x].first == lang)
            return x;
    }
    return -1;
}

bool calc_rgx::is_operator(char c){
    if(c=='|' || c==' ' || c=='+' || c=='*' || c=='(' || c==')')
        return true;
    return false;
}

int calc_rgx::priority(char op){
    if(op == '|')
        return 1;
    if(op == ' ')
        return 2;
    if(op == '*'||op == '+')
        return 3;
    return 0;
}

/*bool visit[1000];
void display (state st){
    visit[st.id] = 1;
   // cout << st.id <<" " << st.transition.size()<<endl;
    for (auto edg: st.transition){
        cout << st.id <<" "<< (edg.first)->id <<" " << edg.second <<endl;
        if (!visit[edg.first->id]){
            display (*(edg.first));
        }
    }
}
*/
bool v [1000];
void calc_rgx:: dfs(state* st, state* cpd, state* helper_end){
    v[st->id] = 1;
    st->related = new state;
    for (auto trs: st->transition){
        state* help = new state;
        st->related = cpd;

        if (trs.first->transition.size()==0){
            if (!v[trs.first->id]){
                help->id = nfa.cnt++;
                *(helper_end) = *(help);
            }
            cpd->transition.push_back({helper_end, trs.second});
            v[trs.first->id] = 1;
            continue;
        }
        if (!v[trs.first->id]){
            help->id = nfa.cnt++;
            cpd->transition.push_back({help, trs.second});
            dfs(trs.first, help, helper_end);
        }else {
            cpd->transition.push_back({trs.first->related, trs.second});
        }
    }

}

automata calc_rgx:: start_copy(automata n){
    state * cp =  new state;
    state *helper_end = new state;
    cp->id = nfa.cnt++;
  //  helper_end->id = nfa.cnt++;
    dfs(n.start, cp, helper_end);
    memset(v, 0, sizeof(v));
    automata cpd;
    cpd.start = cp;
    cpd.end_ = helper_end;
    return cpd;
}

automata calc_rgx::applyOp(automata* a, automata* b,char op, state* s, state* e){
    switch(op){
        case ' ': return nfa.and_NFA (a, b);
        case '|': return nfa.or_NFA (a, b, s, e);
        case '*': return nfa.Closure(a, s, e, op);
        case '+': return nfa.Closure(a, s, e, op);
    }
}

automata calc_rgx::language_NFA (string rgx,vector<pair<string,automata> > Languages){
    stack <automata> automatas;
    stack <char> ops;
    int i;
    for(i=0;i<rgx.length();i++){
        cout << rgx[i] <<'\n' ;
        if(rgx[i] == '('){
            ops.push(rgx[i]);
        }
        else if (!is_operator(rgx[i]) ||(is_operator(rgx[i]) && rgx[i-1]=='\\')){
            string  name = "";
            while(i < rgx.length() && (!is_operator(rgx[i]) ||(is_operator(rgx[i]) && rgx[i-1]=='\\'))){
                if(rgx[i]!='\\' )
                    name.push_back (rgx[i]);
                else{
                    if(rgx[i+1]=='L')
                        name.push_back (rgx[i]);
                }
                i++;
            }
            cout << "name :" << name <<'\n' ;
            int temp = find_language(name,Languages);
            cout << "temp : " << temp <<'\n' ;
            automata  n;
            if(temp == -1){
                automata base;
                n = nfa.basic_NFA(name, base);
            }else{
                n =Languages[temp].second;
                n = start_copy(n);
            }
            automatas.push(n);
            i--;

        }
        else if(rgx[i] == ')'){
            while(!ops.empty() && ops.top() != '('){
                automata auto1;
                automata auto2;
                state *s = new state;
                state *e = new state;
                if(ops.top()==' ' || ops.top()=='|'){
                    auto2 = automatas.top();
                    automatas.pop();
                }

                auto1 = automatas.top();
                automatas.pop();

                char op = ops.top();
                ops.pop();
                automata res = applyOp(&auto1, &auto2, op, s, e);
                automatas.push(res);
            }
            // pop opening brace.
            if(!ops.empty())
               ops.pop();
        }
        else{
            while(!ops.empty() && priority(ops.top())>= priority(rgx[i])){
                automata auto1;
                automata auto2;
                state *s = new state;
                state *e = new state;
                if(ops.top()==' ' || ops.top()=='|'){
                    auto2 = automatas.top();
                    automatas.pop();
                }

                auto1 = automatas.top();
                automatas.pop();
                char op = ops.top();
                ops.pop();

                automata res = applyOp(&auto1, &auto2, op, s, e);
                automatas.push(res);
            }
            ops.push(rgx[i]);
        }

    }
    while(!ops.empty()){
        automata auto1, auto2;
        state *s = new state;
        state *e = new state;
        if(ops.top()==' ' || ops.top()=='|'){
                auto2 = automatas.top();

                automatas.pop();
        }

        auto1 = automatas.top();
        automatas.pop();

        char op = ops.top();
        ops.pop();

        automata res = applyOp(&auto1, &auto2, op, s, e);

        automatas.push(res);
    }
   /* display(*automatas.top().start);

        memset(visit, 0, sizeof(visit));
        cout << endl;*/
    return automatas.top();
}

automata calc_rgx::combine (vector <pair<string,automata>> patterns,state* s){
    return nfa.combined_NFA(patterns,s);
}
