#ifndef DIFFERENCIATOR
#define DIFFERENCIATOR

#include <stdio.h>


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
};

struct Operation
{
    AllOperations num;
    char name[10]; // mabye for sin, sqrt ...
};


struct ForDump
{
    char commands[100][30];
    int dumps_counter;
};

// Как реализовать переменные? Сделать структуру {num, name} и их массив / просто массив где номер - индекс..
// И куда положить этот массив? В Tree?

struct Variable
{
    int num;
    char name;
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


const Operation op_arr[] = {
                                {ADD, "+"},
                                {SUB, "-"},
                                {MUL, "*"},
                                {DIV, "/"}
                            };
const char* const FILE_MATH = "math_problem.txt";


#endif