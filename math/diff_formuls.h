#ifndef DIFF_FORMULS
#define DIFF_FORMULS

#include "../differenciator_h.h" 


Node* diff_add(Node* current_node, FILE* file, VariableArr* all_var);
Node* diff_sub(Node* current_node, FILE* file, VariableArr* all_var);
Node* diff_mul(Node* current_node, FILE* file, VariableArr* all_var);
Node* diff_div(Node* current_node, FILE* file, VariableArr* all_var);
Node* diff_sin(Node* current_node, FILE* file, VariableArr* all_var);
Node* diff_cos(Node* current_node, FILE* file, VariableArr* all_var);
Node* diff_ln (Node* current_node, FILE* file, VariableArr* all_var);
Node* diff_pow(Node* current_node, FILE* file, VariableArr* all_var);



#endif
