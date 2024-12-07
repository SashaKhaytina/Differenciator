#ifndef DIFFERENCIATOR
#define DIFFERENCIATOR

#include <stdio.h>


const char* const FILE_MATH = "math_problem.txt";
const size_t MAX_NAME_IDENT_SIZE = 200;


enum TypeNode
{
    DEFAULT,
    NUMBER,
    VARIABLE,
    OPERATION
};

// enum AllOperations
// {
//     ADD,
//     SUB,
//     MUL,
//     DIV,
// };


struct ForDump
{
    int dumps_counter;
};

// Как реализовать переменные? Сделать структуру {num, name} и их массив / просто массив где номер - индекс..
// И куда положить этот массив? В Tree?

struct Variable
{
    int num;
    char name[MAX_NAME_IDENT_SIZE]; // Я тут ИСПРАВЛЯЛЯ
};

struct VariableArr
{
    Variable arr[10];
    size_t size;
};

struct Node
{
    TypeNode type;
    int      value; // само число или номер переменной или номер операции 
    Node*    left;
    Node*    right;
};

struct Tree
{
    Node* root;
};

// struct Operation
// {
//     AllOperations num;
//     char name[10]; // mabye for sin, sqrt ...
//     // void (*to_do_comm)(FILE* file_asm, Asm_SPU* proc, MashineCode com);
//     Node* (*diff_form)(Node* current_node);
// };


// // #include "diff_formuls.h"
// Node* diff_add(Node* current_node);
// Node* diff_sub(Node* current_node);
// Node* diff_mul(Node* current_node);
// Node* diff_div(Node* current_node);

// const Operation op_arr[] = {
//                                 {ADD, "+", diff_add},
//                                 {SUB, "-", diff_sub},
//                                 {MUL, "*", diff_mul},
//                                 {DIV, "/", diff_div}
//                             };

// #include "diff_formuls.h" // is it bad?


#endif