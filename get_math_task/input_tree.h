#ifndef INPUT_TREE
#define INPUT_TREE

#include "../differenciator_h.h" 
#include <stdio.h>


// enum BranchDirection
// {
//     RIGHT,
//     LEFT
// };


void get_tree(FILE* file, Tree* tree, VariableArr* all_var);
void fill_tree(Node* current_node, int* point_current_letter, char* arr_file_tree, VariableArr* all_var);


#endif