// Это будет подключаться к главному хедеру. (так как там массив операций)
// Эти функции хотим в структуру Operation (и в массив) op_arr.
// Тогда в diff() просто цикл, который вызывает функцию по операции
#ifndef DIFF_FORMULS
#define DIFF_FORMULS

#include "differenciator_h.h" // bad?

Node* diff_add(Node* current_node);
Node* diff_sub(Node* current_node);
Node* diff_mul(Node* current_node);
Node* diff_div(Node* current_node);

const Operation op_arr[] = {
                                {ADD, "+", diff_add},
                                {SUB, "-", diff_sub},
                                {MUL, "*", diff_mul},
                                {DIV, "/", diff_div}
                            };

#endif