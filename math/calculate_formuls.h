#ifndef CALCULATE_FORMULS
#define CALCULATE_FORMULS

#include "../differenciator_h.h"

// Or real numbers in this func (Или просто для чисел, а не для Node)

Elem_t calculate_add(Node* node1, Node* node2);
Elem_t calculate_sub(Node* node1, Node* node2);
Elem_t calculate_mul(Node* node1, Node* node2);
Elem_t calculate_div(Node* node1, Node* node2);
Elem_t calculate_sin(Node* node1, Node* node2);
Elem_t calculate_cos(Node* node1, Node* node2);
Elem_t calculate_log(Node* node1, Node* node2);
Elem_t calculate_pow(Node* node1, Node* node2);

#endif
