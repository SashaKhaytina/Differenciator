// Это будет подключаться к главному хедеру. (так как там массив операций)
// Эти функции хотим в структуру Operation (и в массив) op_arr.
// Тогда в diff() просто цикл, который вызывает функцию по операции
#ifndef DIFF_FORMULS
#define DIFF_FORMULS

#include "differenciator_h.h" 

Node* diff_add(Node* current_node);

#endif