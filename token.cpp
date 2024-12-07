#include "token.h"

#include <malloc.h>
#include <ctype.h>
#include <string.h>

#include "math_commands.h"


static void pass_spaces(int* point_current_letter, char* arr_file_tree);
static void get_word(int* current_symbol, char* arr_file_tree, Node* current_token, VariableArr* all_var);
static void get_num(int* current_symbol, char* arr_file_tree, Node* current_token);
static void get_oper(int* current_symbol, char* arr_file_tree, Node* current_token);




static void pass_spaces(int* point_current_letter, char* arr_file_tree) // add SKIP COMMENTS!!!!!!!!!!!!!!!!!!
{
    while ((arr_file_tree[*point_current_letter] == '\t') || (arr_file_tree[*point_current_letter] == '\n') || (arr_file_tree[*point_current_letter] == ' ')) *point_current_letter += 1;
}



void init_token(Token* token, size_t len_text)
{
    token->array = (Node*) calloc(len_text, sizeof(Node));
    token->size = 0;
    token->current_ind = 0;
}

void get_token(Token* token, char* arr_file_tree, VariableArr* all_var)
{
    int current_symbol = 0;

    while (arr_file_tree[current_symbol] != '\0')
    {
        // skip space and comments
        pass_spaces(&current_symbol, arr_file_tree);
        printf("SKIP\n");

        if      (isdigit(arr_file_tree[current_symbol]) != 0)
        {
            printf("isdigit\n");
            // read number and create new "Node" - NUM (add token->arr)
            get_num(&current_symbol, arr_file_tree, &token->array[token->size]);
            token->size++;
        }
        else if (isalpha(arr_file_tree[current_symbol]) != 0)
        {
            printf("isalpha\n");
            // read word and create new "Node" - VAR or OP(word) (add token->arr)
            get_word(&current_symbol, arr_file_tree, &token->array[token->size], all_var);
            token->size++;
        }
        else // OP
        {
            printf("oper\n");
            // read oper and create new "Node" - OP (add token->arr)
            get_oper(&current_symbol, arr_file_tree, &token->array[token->size]);
            token->size++;
        }
    }

    // printf("%d - all_var->size",all_var->size);

    // for (int i = 0; i < all_var->size; i++)
    // {
    //     printf("%s - %d ----\n", all_var->arr[i].name, all_var->arr[i].num);
    // }

}



static void get_num(int* current_symbol, char* arr_file_tree, Node* current_token)
{
    int val_num = 0;
    while (('0' <= arr_file_tree[*current_symbol]) && (arr_file_tree[*current_symbol] <= '9'))
    {
        val_num = val_num * 10 + arr_file_tree[*current_symbol] - '0';
        (*current_symbol)++;
    }
    // return create_new_node(NUMBER, val_num, NULL, NULL);
    *current_token = {NUMBER, val_num, NULL, NULL};
}


static void get_word(int* current_symbol, char* arr_file_tree, Node* current_token, VariableArr* all_var)
{
    int point_word = *current_symbol; // запомнили где слово начиналось
    // strncmp - ret 0 when =
    int len_word = 0;
    char name[MAX_NAME_IDENT_SIZE] = {};
    

    while ((('A' <= arr_file_tree[*current_symbol]) && (arr_file_tree[*current_symbol] <= 'Z')) || (('a' <= arr_file_tree[*current_symbol]) && (arr_file_tree[*current_symbol] <= 'z')))
    {
        name[len_word] = arr_file_tree[*current_symbol]; // сохраняю имя
        len_word++;
        (*current_symbol)++;
    }

    // Чтоб лишний раз не копировать имя?..
    int len_struct_arr = (int) (sizeof(op_arr) / sizeof(Operation));
    for (int i = 0; i < len_struct_arr; i++)
    {
        // if (strncmp(op_arr[i].name, (arr_file_tree + point_word), len_word) == 0) 
        if (strcmp(op_arr[i].name, name) == 0)
        {
            *current_token = {OPERATION, op_arr[i].num, NULL, NULL};
            break; 
        }
    }

    if (current_token->type != OPERATION)
    {
        // add variable

        // printf("%s - NAEMMEMEMEMEM\n", name);

        int num_var = find_variable(name, all_var);
        if  (num_var == -1) num_var = insert_new_variable(name, all_var);
        // printf("%s - var(2) %d - num\n", all_var->arr[all_var->size - 1].name, all_var->arr[all_var->size - 1].num);
        
        *current_token = {VARIABLE, num_var, NULL, NULL};

        // *current_token = {VARIABLE, val_num, NULL, NULL};
    }

}


static void get_oper(int* current_symbol, char* arr_file_tree, Node* current_token)
{
    char op[2] = {}; // ???????????????????????????
    op[0] = arr_file_tree[*current_symbol];
    (*current_symbol)++;

    int len_struct_arr = (int) (sizeof(op_arr) / sizeof(Operation));
    for (int i = 0; i < len_struct_arr; i++)
    {
        // if (strncmp(op_arr[i].name, (arr_file_tree + point_word), len_word) == 0) 
        if (strcmp(op_arr[i].name, op) == 0)
        {
            *current_token = {OPERATION, op_arr[i].num, NULL, NULL};

            break; 
        }
    }
    // return create_new_node(NUMBER, val_num, NULL, NULL);
    if (current_token->type == DEFAULT) printf("SYNTAX ERROR\n");
    // *current_token = {NUMBER, val_num, NULL, NULL};
}













int find_variable(char* var_name, VariableArr* all_var)
{
    for (size_t i = 0; i < all_var->size; i++)
    {
        // printf("%c - arr_file_tree[*point_current_letter]\n", arr_file_tree[*point_current_letter]);
        // printf("%s - all_var->arr[i].name\n", all_var->arr[i].name);

        if (strcmp(all_var->arr[i].name, var_name) == 0) 
        { 
            printf("FIND!");
            return all_var->arr[i].num; 
        }
    }

    return -1; // const
}


int insert_new_variable(char* var_name, VariableArr* all_var)
{
    all_var->size++;
    all_var->arr[all_var->size - 1].num = (int)all_var->size;
    strcpy(all_var->arr[all_var->size - 1].name, var_name);
    // all_var->arr[all_var->size - 1] = {(int)all_var->size, var_name};
    // num_var = all_var->size; // Говорим, что ЭТОТ номер ее
    // printf("%s - var\n", all_var->arr[all_var->size - 1].name);
    return (int)all_var->size;
}


void print_token(Token* token, VariableArr* all_var)
{
    for (size_t i = 0; i < token->size; i++)
    {
        if (token->array[i].type == NUMBER) printf("%d", token->array[i].value);
        if (token->array[i].type == VARIABLE) printf("%s", all_var->arr[token->array[i].value - 1].name);
        if (token->array[i].type == OPERATION) printf("%s", op_arr[token->array[i].value].name);
        // printf("TOKEN[%d] (Node) = {%d - type, %d - value}\n", i, token->array[i].type, token->array[i].value);
    }
}