#include "calculate_formuls.h"

#include "math.h"



int calculate_add(Node* node1, Node* node2)
{
    assert(node1);
    assert(node2);


    return (node1->value + node2->value);
}


int calculate_sub(Node* node1, Node* node2)
{
    assert(node1);
    assert(node2);


    return (node1->value - node2->value);
}


int calculate_mul(Node* node1, Node* node2)
{
    assert(node1);
    assert(node2);


    return (node1->value * node2->value);
}


int calculate_div(Node* node1, Node* node2)
{
    assert(node1);
    assert(node2);
    

    return (node1->value / node2->value);
}


int calculate_sin(Node* node1, Node* node2) // NULL_ARG
{
    assert(!node1); // NULL
    assert(node2);


    return ((int) sin((double) node2->value)); ///////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}


int calculate_cos(Node* node1, Node* node2) // NULL_ARG
{
    assert(!node1); // NULL
    assert(node2);


    return ((int) cos((double) node2->value)); ///////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}


int calculate_pow(Node* node1, Node* node2)
{
    assert(node1);
    assert(node2);


    return ((int) pow((double) node1->value, (double) node2->value)); ///////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}


int calculate_log(Node* node1, Node* node2) // NULL_ARG
{
    assert(!node1); // NULL
    assert(node2);


    return ((int) log((double) node2->value)); ///////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}