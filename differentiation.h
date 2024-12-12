// за что..

#ifndef DIFFERENTIATION
#define DIFFERENTIATION

#include "differenciator_h.h"

Node* diff(Node* current_node, FILE* file, VariableArr* all_var); // берет производную от поддерева (начиная с данного)
// Node* diff(Node* current_node, ForTexDump* tex_dump, VariableArr* all_var);


#endif