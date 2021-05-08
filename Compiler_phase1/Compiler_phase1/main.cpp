#include <iostream>
#include "minimization.h"
//#include "DFA.h"
//#include "NFA.h"
using namespace std;

/*int main()
{
    struct NFA_State A, B, C, D;
    struct Transition edge;
    struct DFA_State* a = new DFA_State;

    //example 1c in sheet3
    A.id = 1;
    edge.input_symbol.name = "0";
    edge.next = &B;
    A.transitions.push_back(edge);

    edge.input_symbol.name = "0";
    edge.next = &C;
    A.transitions.push_back(edge);



    B.id = 2;
    edge.input_symbol.name = "1";
    edge.next = &A;
    B.transitions.push_back(edge);

    edge.input_symbol.name = "1";
    edge.next = &C;
    B.transitions.push_back(edge);




    C.id = 3;
    edge.input_symbol.name = "0";
    edge.next = &D;
    C.transitions.push_back(edge);

    edge.input_symbol.name = "1";
    edge.next = &D;
    C.transitions.push_back(edge);




    D.id = 4;
    edge.input_symbol.name = "1";
    edge.next = &D;
    D.transitions.push_back(edge);

    edge.input_symbol.name = "0";
    edge.next = &B;
    D.transitions.push_back(edge);

    B.accept_state_flag = true;
    C.accept_state_flag = true;

    cout << "current state: " << A.id << " input: " << A.transitions[0].input_symbol.name << " new state " << A.transitions[0].next->id << "\n";
    cout << "current state: " << B.id << " input: " << B.transitions[0].input_symbol.name << " new state " << B.transitions[0].next->id << "\n";
    cout << "current state: " << B.id << " input: " << B.transitions[1].input_symbol.name << " new state " << B.transitions[1].next->id << "\n";

    //cout<<"hiiii"<<endl;
    a->id = 1;
    a->subset_ids.insert(1);
    a->subset.insert(&A);

    test(a);


    //get_graph -> primary DFA
    //table_filling -> minimized DFA
    minimize_graph(get_graph());

    return 0;
}
*/
