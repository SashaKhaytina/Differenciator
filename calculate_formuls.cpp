#include "calculate_formuls.h"

#include "math.h"



Elem_t calculate_add(Node* node1, Node* node2)
{
    assert(node1);
    assert(node2);


    return (node1->value.num + node2->value.num);
}


Elem_t calculate_sub(Node* node1, Node* node2)
{
    assert(node1);
    assert(node2);


    return (node1->value.num - node2->value.num);
}


Elem_t calculate_mul(Node* node1, Node* node2)
{
    assert(node1);
    assert(node2);


    return (node1->value.num * node2->value.num);
}


Elem_t calculate_div(Node* node1, Node* node2)
{
    assert(node1);
    assert(node2);
    

    return (node1->value.num / node2->value.num);
}


Elem_t calculate_sin(Node* node1, Node* node2) // NULL_ARG
{
    assert(!node1); // NULL
    assert(node2);


    return (sin((double) node2->value.num)); ///////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}


Elem_t calculate_cos(Node* node1, Node* node2) // NULL_ARG
{
    assert(!node1); // NULL
    assert(node2);


    return ( cos((double) node2->value.num)); ///////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}


Elem_t calculate_pow(Node* node1, Node* node2)
{
    assert(node1);
    assert(node2);


    return ( pow((double) node1->value.num, (double) node2->value.num)); ///////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}


Elem_t calculate_log(Node* node1, Node* node2) // NULL_ARG
{
    assert(!node1); // NULL
    assert(node2);


    return ( log((double) node2->value.num)); ///////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}