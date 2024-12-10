#ifndef DIFFERENCIATOR
#define DIFFERENCIATOR

#include <stdio.h>
#include <assert.h>


const char* const FILE_MATH = "math_problem.txt";
const size_t      MAX_NAME_IDENT_SIZE = 200;
// const int         NULL_ARG = -1;

enum TypeNode
{
    DEFAULT,
    NUMBER,
    VARIABLE,
    OPERATION
};


struct ForDump
{
    int dumps_counter;
};


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



#endif