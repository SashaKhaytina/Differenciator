#ifndef TEX_DUMP
#define TEX_DUMP

#include "../differenciator_h.h"


void fprint_tree(FILE* file, Node* node, VariableArr* all_var);
void fprint_node(FILE* file, Node* node, VariableArr* all_var);

void tex_dump_title(FILE* file);
void tex_dump_end_title(FILE* file);

void tex_dump_end(FILE* file, Node* current_node, Node* diff_node, VariableArr* all_var);

void tex_dump_num(FILE* file, Node* current_node, VariableArr* all_var);
void tex_dump_var(FILE* file, Node* current_node, VariableArr* all_var);

void tex_dump_add(FILE* file, Node* current_node, VariableArr* all_var);
void tex_dump_sub(FILE* file, Node* current_node, VariableArr* all_var);
void tex_dump_mul(FILE* file, Node* current_node, VariableArr* all_var);
void tex_dump_div(FILE* file, Node* current_node, VariableArr* all_var);
void tex_dump_sin(FILE* file, Node* current_node, VariableArr* all_var);
void tex_dump_cos(FILE* file, Node* current_node, VariableArr* all_var);
void tex_dump_ln (FILE* file, Node* current_node, VariableArr* all_var);
void tex_dump_pow(FILE* file, Node* current_node, VariableArr* all_var);


#endif
