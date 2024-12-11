#ifndef TEX_DUMP
#define TEX_DUMP

#include "differenciator_h.h"

void tex_dump(Node* node, Node* node_diff, ForDump* st_dump, VariableArr* all_var);
void fprint_tree(FILE* file, Node* node, VariableArr* all_var);
void fprint_node(FILE* file, Node* node, VariableArr* all_var);





#endif