#ifndef TEX_DUMP
#define TEX_DUMP

#include "../differenciator_h.h"

// void tex_dump(Node* node, Node* node_diff, FILE* tex_file, VariableArr* all_var);
void fprint_tree(FILE* file, Node* node, VariableArr* all_var);
void fprint_node(FILE* file, Node* node, VariableArr* all_var);

void tex_dump_start(FILE* file, Node* node, VariableArr* all_var);
void tex_dump_end(FILE* file, Node* current_node, Node* diff_node, VariableArr* all_var);

void tex_dump_add(FILE* file, Node* current_node, VariableArr* all_var);
void tex_dump_sub(FILE* file, Node* current_node, VariableArr* all_var);
void tex_dump_mul(FILE* file, Node* current_node, VariableArr* all_var);
void tex_dump_div(FILE* file, Node* current_node, VariableArr* all_var);
void tex_dump_sin(FILE* file, Node* current_node, VariableArr* all_var);
void tex_dump_cos(FILE* file, Node* current_node, VariableArr* all_var);
void tex_dump_log(FILE* file, Node* current_node, VariableArr* all_var);
void tex_dump_pow(FILE* file, Node* current_node, VariableArr* all_var);

void tex_dump_num(FILE* file, Node* current_node, VariableArr* all_var);
void tex_dump_var(FILE* file, Node* current_node, VariableArr* all_var);









#endif