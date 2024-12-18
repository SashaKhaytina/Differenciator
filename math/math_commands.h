#ifndef MATH
#define MATH

#include "../differenciator_h.h"



struct Operation
{
    AllOperations num;
    char          name[10];
    Node*         (*diff_form)     (Node* current_node, FILE* file, VariableArr* all_var);
    Elem_t        (*calculate)     (Node* node1, Node* node2); 
    void          (*triv_calculate)(Node* node, int* diference);
};

#include "diff_formuls.h"
#include "calculate_formuls.h"
#include "calculate_trivial.h"

const Operation op_arr[] = {
                                {ADD,        "+",   diff_add, calculate_add, calculate_triv_add},
                                {SUB,        "-",   diff_sub, calculate_sub, calculate_triv_sub},
                                {MUL,        "*",   diff_mul, calculate_mul, calculate_triv_mul},
                                {DIV,        "/",   diff_div, calculate_div, calculate_triv_div},
                                {SIN,        "sin", diff_sin, calculate_sin, calculate_triv_sin},
                                {COS,        "cos", diff_cos, calculate_cos, calculate_triv_cos},
                                {POW,        "^",   diff_pow, calculate_pow, calculate_triv_pow},
                                {LN ,        "ln",  diff_ln , calculate_ln , calculate_triv_ln },

                                {OPEN_SKOB,  "(",   NULL,     NULL,          NULL},
                                {CLOSE_SKOB, ")",   NULL,     NULL,          NULL}

                                // {DOLL,       "$",   NULL,     NULL,          NULL} 
                            };

const int LEN_STRUCT_OP_ARR = (int) (sizeof(op_arr) / sizeof(Operation));

#endif