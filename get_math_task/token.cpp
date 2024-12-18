#include "token.h"

#include <malloc.h>
#include <ctype.h>
#include <string.h>

#include "../math/math_commands.h"
#include "../tree_s__commands/tree_commands.h"


const int NO_THIS_VAR = -1;


static void pass_spaces       (int* point_current_letter, char* arr_file_tree);
static void get_word          (int* current_symbol, char* arr_file_tree, Token* token, VariableArr* all_var);
static void get_num           (int* current_symbol, char* arr_file_tree, Token* token);
static void get_oper          (int* current_symbol, char* arr_file_tree, Token* token);
static bool find_and_create_op(Token* token, char* name);



static void pass_spaces(int* point_current_letter, char* arr_file_tree)
{
    while ((arr_file_tree[*point_current_letter] == '\t') || (arr_file_tree[*point_current_letter] == '\n') || (arr_file_tree[*point_current_letter] == ' ')) *point_current_letter += 1;
}



static void get_num(int* current_symbol, char* arr_file_tree, Token* token)
{
    Elem_t val_num = 0;

    sscanf(arr_file_tree + *current_symbol, "%lg", &val_num);

    bool not_was_point = true;
    while (isdigit(arr_file_tree[*current_symbol]) != 0 || arr_file_tree[*current_symbol] == '.')
    {
        if (arr_file_tree[*current_symbol] == '.')
        {
            if (not_was_point) not_was_point = false;
            else               printf("ERROR NUMBER");
        }
        (*current_symbol)++;
    }

    token->array[token->size] = _NUM(val_num);
    token->size++;

}


static void get_word(int* current_symbol, char* arr_file_tree, Token* token, VariableArr* all_var)
{
    int len_word = 0;
    char temporary_name[MAX_NAME_IDENT_SIZE] = {};

    while (isalpha(arr_file_tree[*current_symbol]) != 0)
    {
        temporary_name[len_word] = arr_file_tree[*current_symbol]; 
        len_word++;
        (*current_symbol)++;
    }

    char* name = (char*) calloc(len_word, sizeof(char));
    strcpy(name, temporary_name);

    bool is_oper = find_and_create_op(token, name);


    if (!is_oper)    // It is Variable 
    {

        int num_var = find_variable(name, all_var);
        if  (num_var == NO_THIS_VAR) num_var = insert_new_variable(name, all_var);

        token->array[token->size] = _VAR(num_var);
        token->size++;

    }

}


static void get_oper(int* current_symbol, char* arr_file_tree, Token* token)
{
    char op[MAX_OPER_SYMBOLS_SIZE] = {}; 
    op[0] = arr_file_tree[*current_symbol];
    (*current_symbol)++;

    bool is_oper = find_and_create_op(token, op);

    if (!is_oper) printf("SYNTAX ERROR\n");
}




void init_token(Token* token, size_t len_text)
{
    token->array = (Node**) calloc(len_text, sizeof(Node*));
    token->size = 0;
    token->current_ind = 0;
}


void get_token(Token* token, char* arr_file_tree, VariableArr* all_var)
{
    int current_symbol = 0;

    // while (arr_file_tree[current_symbol] != '\0') // see parser.cpp
    while (arr_file_tree[current_symbol] != '\n')
    {
        pass_spaces(&current_symbol, arr_file_tree);

        if      (isdigit(arr_file_tree[current_symbol]) != 0)
        {
            get_num(&current_symbol, arr_file_tree, token);
        }
        else if (isalpha(arr_file_tree[current_symbol]) != 0)
        {
            get_word(&current_symbol, arr_file_tree, token, all_var);
        }
        else
        {
            get_oper(&current_symbol, arr_file_tree, token);
        }
    }
}




int find_variable(char* var_name, VariableArr* all_var)
{
    for (size_t i = 0; i < all_var->size; i++)
    {
        if (strcmp(all_var->arr[i].name, var_name) == 0) 
        { 
            return all_var->arr[i].num; 
        }
    }

    return NO_THIS_VAR; 
}


int insert_new_variable(char* var_name, VariableArr* all_var)
{
    all_var->size++;

    all_var->arr[all_var->size - 1].num = (int)all_var->size;
    all_var->arr[all_var->size - 1].name = var_name;

    return (int)all_var->size;
}


static bool find_and_create_op(Token* token, char* name)
{
    bool is_oper = false;

    for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
    {
        if (strcmp(op_arr[i].name, name) == 0)
        {
            token->array[token->size] = create_new_node_op(OPERATION, op_arr[i].num, NULL, NULL);
            token->size++;

            is_oper = true;

            break; 
        }
    }

    return is_oper;
}




void print_token(Token* token, VariableArr* all_var)
{
    for (size_t i = 0; i < token->size; i++)
    {
        if (token->array[i]->type == NUMBER)    printf("%lg", token->array[i]->value.num);
        if (token->array[i]->type == VARIABLE)  printf("%s", all_var->arr[token->array[i]->value.var_num - 1].name);
        if (token->array[i]->type == OPERATION) printf("%s", op_arr[token->array[i]->value.op_num].name);
    }
}