#include "interface.h"
#include "DFA.h"
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void Get_NFA_Converted_State(map<int,vector<pair<int,string>>> NFA_set_map ,map <int,NFA_State*> NFA_initial_Map)
{

    map<int,vector<pair<int,string>>>::iterator itr2;
    for(itr2 =  NFA_set_map.begin(); itr2 !=  NFA_set_map.end(); ++itr2){
        int id_source=itr2->first;
        vector<pair<int,string>> temp_transition = itr2->second;
        NFA_State * source=NFA_initial_Map[id_source];
        vector <Transition> source_transitions;
            // using begin() to print set
            for (auto item :temp_transition)
            {
                int id_destination=item.first;
                Transition temp_item;
                temp_item.next=NFA_initial_Map[id_destination];
                temp_item.input_symbol=item.second;
                source_transitions.push_back(temp_item);
            }

        source->transitions=source_transitions;
    }
    //print
    /*map <int,NFA_State*>::iterator itr;
    for(itr =  NFA_initial_Map.begin(); itr !=  NFA_initial_Map.end(); ++itr){
        cout<<"source : "<<itr->first<<"destination :  ";
        NFA_State* temp=itr->second;
            // using begin() to print set
            for (auto item :temp->transitions)
            {
              cout <<"condition :" <<item.input_symbol <<" id :"<<item.next->id<< " \n";

            }
            cout << " \n";


    }*/


}


NFA_State * convert(automata final_result){
    //extracted from automata
    state* first = final_result.start;
    state* last = final_result.end_;
    state* current = first;

    //build graph
    map <int,NFA_State*> NFA_initial_Map;
    queue <state*> state_queue;
    map<int,vector<pair<int,string>>> NFA_set_map;
    NFA_State * start_state =new NFA_State;
    //initalize
    start_state->id = current->id;
    start_state->accept_state_flag = current->accepted;
    start_state->name = current->accepted_language;
    start_state->priority = current->priority;
     NFA_initial_Map[start_state->id]=start_state;
     //loop to get all next transitions
     for(auto item:current->transition){
         state_queue.push(item.first);
         NFA_set_map[start_state->id] .push_back ({item.first->id,item.second}); //the node which i exists .
     }

    //map <int, pair<int, string>> NFA_set_map;

    while(!state_queue.empty()){
        //get the first item out
        current = state_queue.front();
        state_queue.pop();
        NFA_State* temp = new NFA_State;
        temp->id = current->id;
        temp->accept_state_flag = current->accepted;
        temp->name = current->accepted_language;
        temp->priority = current->priority;
        //const bool is_in = NFA_set.find(temp) != NFA_set.end();
        if(NFA_initial_Map.count(temp->id)==0){
            NFA_initial_Map[temp->id]=temp;
            //loop to get all next transitions
             for(auto item:current->transition){
                state_queue.push(item.first);
                NFA_set_map[temp->id] .push_back ({item.first->id,item.second}); //the node which i exists .
            }
        }
    }
    Get_NFA_Converted_State(NFA_set_map,NFA_initial_Map);
    //Subset_Construction(start_state);

   /* map<int,NFA_State*>::iterator itr;
    for(itr =  NFA_initial_Map.begin(); itr !=  NFA_initial_Map.end(); ++itr){
        cout<<itr->first<<endl;
    }

    map<int,vector<pair<int,string>>>::iterator itr2;
    for(itr2 =  NFA_set_map.begin(); itr2 !=  NFA_set_map.end(); ++itr2){
        cout<<"source :"<<itr2->first<<"destina : { ";
        vector<pair<int,string>> myset = itr2->second;

            // using begin() to print set
            for (auto item :myset)
            {
                cout << item.first<< " ";

            }
            cout << " }\n";


    }
    */
    return start_state;
}

