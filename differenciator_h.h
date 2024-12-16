#ifndef DIFFERENCIATOR
#define DIFFERENCIATOR

#include <stdio.h>
#include <assert.h>


typedef double Elem_t;

const char* const FILE_MATH             = "math_problem.txt";
const char* const FILE_TEX              = "all_dumps/tex_files/tex.tex";
const size_t      MAX_NAME_IDENT_SIZE   = 200;
const int         MAX_OPER_SYMBOLS_SIZE = 2;
const int         MAX_TOKEN_S_ARR_SIZE  = 100;


enum TypeNode
{
    DEFAULT,
    NUMBER,
    VARIABLE,
    OPERATION
};


enum AllOperations
{
    ADD,
    SUB,
    MUL,
    DIV,
    SIN,
    COS,
    POW,
    LOG,
    OPEN_SKOB,
    CLOSE_SKOB, 
    DOLL  // TODO: remove
};


struct ForDump
{
    int dumps_counter;
};  // TODO: remove blya


struct ForTexDump
{
    int tex_dumps_counter;
};  // TODO: remove blya


struct Variable
{
    int num;
    char* name; 
};

struct VariableArr
{
    Variable arr[10];
    size_t size;
};

// struct Node
// {
//     TypeNode type;
//     int      value; // само число или номер переменной или номер операции 
//     Node*    left;
//     Node*    right;
// };

union Value
{
    Elem_t num;
    int var_num;
    AllOperations op_num;
};


struct Node
{
    TypeNode type;
    Value    value;
    Node*    left;
    Node*    right;
};

struct Tree
{
    Node* root;
};



#endif