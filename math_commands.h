#ifndef MATH
#define MATH

#include "differenciator_h.h"


enum AllOperations
{
    ADD,
    SUB,
    MUL,
    DIV,
};

struct Operation
{
    AllOperations num;
    char name[10]; // mabye for sin, sqrt ...
    // void (*to_do_comm)(FILE* file_asm, Asm_SPU* proc, MashineCode com);
    Node* (*diff_form)(Node* current_node);
    int   (*calculate)(Node* node1, Node* node2); // for sin - value and NULL
};

#include "diff_formuls.h"
#include "calculate_formuls.h"

const Operation op_arr[] = {
                                {ADD, "+", diff_add, calculate_add},
                                {SUB, "-", diff_sub, calculate_sub},
                                {MUL, "*", diff_mul, calculate_mul},
                                {DIV, "/", diff_div, calculate_div}
                            };

#endif

