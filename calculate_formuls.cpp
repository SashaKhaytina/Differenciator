#include "calculate_formuls.h"



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