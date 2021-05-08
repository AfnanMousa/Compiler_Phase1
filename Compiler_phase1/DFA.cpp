#include <iostream>
#include <bits/stdc++.h>
#include <iterator>
#include "DFA.h"
#include"minimization.h"
using namespace std;
vector<DFA_State*>Table;
int Count = 2;

template<typename T>
bool isEqual(std::set<T> const& v1, std::set<T> const& v2)
{
    return (v1.size() == v2.size() &&
        std::equal(v1.begin(), v1.end(), v2.begin()));
}
bool Check(set<int> v)
{

    for (auto i : Table)
    {
        if (isEqual(v, i->subset_ids))
        {
            return false;
        }
    }
    return true;
}

vector <NFA_State*> E_closure(NFA_State* original) {
    vector <NFA_State*> closures;
    stack <NFA_State*> temp;
    temp.push(original);
    while (!temp.empty()) {

        NFA_State* state = temp.top();
        temp.pop();
        vector <Transition> t = state->transitions;
        for (auto item : t) {
                string s2="\\L";
                string s1=item.input_symbol;

            if (s1.compare(s2)==0 ) {
                if (!count(closures.begin(), closures.end(), item.next)) {
                    closures.push_back(item.next);
                    temp.push(item.next);
                }
            }
        }
    }
    return closures;
}
vector<DFA_State*> get()
{
    return Table;
}

void Move_To(DFA_State* Basic_node) //struct node
{
    set<NFA_State*> Initial_state = Basic_node->subset;
    map <string, set<NFA_State*>> temp_symbols;
    map <string, set<int>> temp_ids;
    map<string, bool> flag_accept;
    for (auto i : Initial_state)//int i=0;i<Initial_state.size();i++
    {
        vector<Transition> Total_Transition = i->transitions;

        for (int j = 0; j < Total_Transition.size(); j++)
        {
            string s2="\\L";
            if (Total_Transition[j].input_symbol.compare(s2)==0 ) continue;

            if (Total_Transition[j].next->accept_state_flag)flag_accept[Total_Transition[j].input_symbol] = true; //check if the next state is accept or not .

            temp_symbols[Total_Transition[j].input_symbol].insert(Total_Transition[j].next);  //push the next node .
            temp_ids[Total_Transition[j].input_symbol].insert((Total_Transition[j].next)->id);

            vector <struct NFA_State*> Epsilon_state = E_closure(Total_Transition[j].next);         // part of epsilon ..
            if (Epsilon_state.size() != 0) //epsilon of each reachable node.
            {
                for (auto item : Epsilon_state)
                {
                    if (item->accept_state_flag)flag_accept[Total_Transition[j].input_symbol] = true; //check if the next state is accept or not for epsilon state.
                    temp_symbols[Total_Transition[j].input_symbol].insert(item); //push epsilon of each reachable node.
                    temp_ids[Total_Transition[j].input_symbol].insert(item->id);
                }
            }

        }
    }
    //after that the row is fish must push it in the vector under each input symbol.
    for (auto i : temp_ids)
    {
        if (Check(i.second))
        {
            DFA_State* temp = new DFA_State;
            temp->id = Count++; //cout<<i.first<<endl;
            temp->subset = temp_symbols[i.first]; //i.first mean input;
            temp->subset_ids = temp_ids[i.first];
            temp->accept_state_flag = flag_accept[i.first];
            Table.push_back(temp);

        }
    }
    Basic_node->symbols = temp_symbols;
    //print...
    /*for(auto t :Basic_node->symbols)
    {
        cout<<t.first<<" "<<endl;
        for(auto e: t.second)
            cout<<"id"<<e->id<<" "<<endl;

    }*/
    Basic_node->Group_ids = temp_ids;
}

void Subset_Construction(NFA_State* original)
{
    // prepare the initial state by original.
    DFA_State* a = new DFA_State;
    a->id = 1;
    a->subset.insert(original);
    a->subset_ids.insert(original->id);
    if (original->accept_state_flag) a->accept_state_flag = true;
    //call epsilon .
    vector <struct NFA_State*> Epsilon_state = E_closure(original);
    if (Epsilon_state.size() != 0) //epsilon of each reachable node.
    {
        for (auto item : Epsilon_state)
        {
            if (!(a->accept_state_flag)&&(item->accept_state_flag)) a->accept_state_flag = true;
            a->subset.insert(item);
            a->subset_ids.insert(item->id);
        }
    }
    //push a to the Table as start state.
    Table.push_back(a);
    int t = 0;
    while (t < Table.size())
    {
        Move_To(Table[t]);
        t++;
    }
    cout<<"DFA before minimization \n";
    map<int, DFA_Graph> Result_graph=get_graph();
    print_graph(Result_graph);
    cout<<"DFA after minimization \n";
    minimize_graph(Result_graph);

}

void test(DFA_State* a)
{

    Table.push_back(a);

    int t = 0;
    while (t < Table.size())
    {
        Move_To(Table[t]);
        t++;
    }

    for (int i = 0; i < Table.size(); i++)
    {
        cout << "State : { ";
        for (auto item : Table[i]->subset_ids)
        {
             cout<< item << " ";
        }
        cout << "} accepted falg = "<<Table[i]->accept_state_flag<<" ";
        for (auto const& pair : Table[i]->Group_ids) {
            std::cout << " transition {" << pair.first << ": ";

            set<int> myset = pair.second;

            // using begin() to print set
            for (auto it = myset.begin(); it != myset.end(); ++it)
            {
                cout << ' ' << *it << " ";

            }
            cout << "}\n";
        }
    }

}

map<int, DFA_Graph> get_graph (){
    //first map: DFA state id with DFA transitions
    //second map: input symbol with the id of corresponding reached DFA state
    DFA_Graph state_info;
    map<string, int> transition_map;
    map<int, DFA_Graph> graph;


    for(int i=0; i<Table.size(); i++){
        int current_id = Table[i]->id;
        bool accepted = Table[i]->accept_state_flag;
        string type_name = Table[i]->name;
        map <string, set<NFA_State*>> transition = Table[i]->symbols;
        for(auto item : transition){
            string input = item.first;
            int next_id;
            set <NFA_State*> sub = item.second;
            for(auto next:Table){
                if(next->subset == sub){
                    next_id = next->id;
                    break;
                }
            }
            transition_map.insert({input, next_id});
        }
        state_info.acceptance_state = accepted;
        state_info.name = type_name;
        state_info.next_state = transition_map;

        graph.insert({current_id, state_info});

        transition_map.clear();
    }
    cout<<"DFA before minimization \n";
    print_graph(graph);
    return graph;
}

//make the map = struct of this map + acceptable state
void print_graph(map<int, DFA_Graph> graph){
    cout<<"\n *******************"<<"\n";
    // graph[1] -> maptT
    //Print your graph here
    //map<int, map<string, int>> graph;
    map<int, DFA_Graph>::iterator itr1;
    map<string, int>::iterator itr2;
    for(itr1 =  graph.begin(); itr1 !=  graph.end(); ++itr1){
        cout<<"\n state id is: "<<itr1->first<<"\n its accepting state is " << itr1->second.acceptance_state<<"\n";
        for(itr2 = itr1->second.next_state.begin(); itr2 != itr1->second.next_state.end(); ++itr2)
            cout<<"under input "<< itr2->first<<"  it goes to state "<<itr2->second<<"\n";
        cout<<"*******************"<<"\n";
    }
}



