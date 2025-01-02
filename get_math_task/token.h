#ifndef TOKEN
#define TOKEN

#include "../differenciator_h.h"

struct Token
{
    Node** array;
    size_t size; 
    size_t current_ind;
};

int find_variable      (char* var_name, VariableArr* all_var);
int insert_new_variable(char* var_name, VariableArr* all_var);

void get_token  (Token* token, char* arr_file_tree, VariableArr* all_var);
void print_token(Token* token, VariableArr* all_var);
void init_token (Token* token, size_t len_text);


#endif
