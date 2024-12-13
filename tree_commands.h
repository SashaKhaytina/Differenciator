#ifndef TREE_COMMANDS
#define TREE_COMMANDS

#include "differenciator_h.h"

Node* create_new_node(TypeNode type, Elem_t num, Node* left, Node* right);


void solve(Node* current_node);

TypeNode solve_subtree (Node* current_node, int* diference); // strange type return for this func
void     trivial_solver(Node* current_node, int* diference);


#endif