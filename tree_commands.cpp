#include "tree_commands.h"

#include <stdio.h>
#include <malloc.h>

Node* create_new_node(TypeNode type, int value, Node* left, Node* right)
{
    Node* new_node = (Node*) calloc(1, sizeof(Node));
    *new_node = {type, value, left, right};
    return new_node;
}