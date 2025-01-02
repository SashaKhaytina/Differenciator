#ifndef FREE
#define FREE

#include "../differenciator_h.h"
#include "../get_math_task/token.h"


void free_tree           (Node* node);
void free_val            (VariableArr* all_var);
void free_tokens         (Token* token);
void free_needless_tokens(Token* token);



#endif 
