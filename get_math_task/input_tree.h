#ifndef INPUT_TREE
#define INPUT_TREE

#include "../differenciator_h.h" 
#include "token.h"

#include <stdio.h>


void get_tree(FILE* file, Tree* tree, VariableArr* all_var, Token* token);
void fill_tree(Node* current_node, int* point_current_letter, char* arr_file_tree, VariableArr* all_var);


#endif
