// Это будет подключаться к главному хедеру. (так как там массив операций)
// Эти функции хотим в структуру Operation (и в массив) op_arr.
// Тогда в diff() просто цикл, который вызывает функцию по операции
#ifndef DIFF_FORMULS
#define DIFF_FORMULS

#include "differenciator_h.h" 


#define _LEFT  current_node->left
#define _RIGHT current_node->right

#define _NUM(num)         create_new_node(NUMBER,    num,  NULL, NULL)

#define _ADD(left, right) create_new_node(OPERATION, ADD, left, right)
#define _SUB(left, right) create_new_node(OPERATION, SUB, left, right)
#define _MUL(left, right) create_new_node(OPERATION, MUL, left, right)
#define _DIV(left, right) create_new_node(OPERATION, DIV, left, right)
#define _POW(left, right) create_new_node(OPERATION, POW, left, right)
#define _SIN(arg)         create_new_node(OPERATION, SIN, NULL, arg)
#define _COS(arg)         create_new_node(OPERATION, COS, NULL, arg)
#define _LOG(arg)         create_new_node(OPERATION, ADD, NULL, arg)

#define _DIFF(arg)        diff(arg, file, all_var)
#define _COPY(arg)        copy_branch(arg)







Node* diff_add(Node* current_node, FILE* file, VariableArr* all_var);
Node* diff_sub(Node* current_node, FILE* file, VariableArr* all_var);
Node* diff_mul(Node* current_node, FILE* file, VariableArr* all_var);
Node* diff_div(Node* current_node, FILE* file, VariableArr* all_var);
Node* diff_sin(Node* current_node, FILE* file, VariableArr* all_var);
Node* diff_cos(Node* current_node, FILE* file, VariableArr* all_var);
Node* diff_log(Node* current_node, FILE* file, VariableArr* all_var);
Node* diff_pow(Node* current_node, FILE* file, VariableArr* all_var);



#endif