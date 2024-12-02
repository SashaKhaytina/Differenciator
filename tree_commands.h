#ifndef TREE_COMMANDS
#define TREE_COMMANDS

#include "differenciator_h.h"

Node* create_new_node(TypeNode type, int value, Node* left, Node* right);

// there are solve_subtree here
TypeNode solve_subtree(Node* current_node); // strange type return for this func


#endif