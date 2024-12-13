#include "token.h"

#include <malloc.h>
#include <ctype.h>
#include <string.h>

#include "../math/math_commands.h"


const int NO_THIS_VAR = -1;


static void pass_spaces(int* point_current_letter, char* arr_file_tree);
static void get_word   (int* current_symbol, char* arr_file_tree, Node* current_token, VariableArr* all_var);
static void get_num    (int* current_symbol, char* arr_file_tree, Node* current_token);
static void get_oper   (int* current_symbol, char* arr_file_tree, Node* current_token);




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
}



static void get_num(int* current_symbol, char* arr_file_tree, Node* current_token)
{
    Elem_t val_num = 0;
    while (('0' <= arr_file_tree[*current_symbol]) && (arr_file_tree[*current_symbol] <= '9'))
    {
        val_num = val_num * 10 + arr_file_tree[*current_symbol] - '0';
        (*current_symbol)++;
    }
    // *current_token = {NUMBER, val_num, NULL, NULL};
    current_token->type      = NUMBER;
    current_token->value.num = val_num;
    current_token->left      = NULL;
    current_token->right     = NULL;
}


static void get_word(int* current_symbol, char* arr_file_tree, Node* current_token, VariableArr* all_var)
{
    // int point_word = *current_symbol; // запомнили где слово начиналось
    // strncmp - ret 0 when =
    int len_word = 0;

    char name[MAX_NAME_IDENT_SIZE] = {};
    
    // Read word
    while ((('A' <= arr_file_tree[*current_symbol]) && (arr_file_tree[*current_symbol] <= 'Z')) || (('a' <= arr_file_tree[*current_symbol]) && (arr_file_tree[*current_symbol] <= 'z')))
    {
        name[len_word] = arr_file_tree[*current_symbol]; // сохраняю имя
        len_word++;
        (*current_symbol)++;
    }

    // Чтоб лишний раз не копировать имя?..

    // Is it Operation?
    for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
    {
        // if (strncmp(op_arr[i].name, (arr_file_tree + point_word), len_word) == 0) 
        if (strcmp(op_arr[i].name, name) == 0)
        {
            // *current_token = {OPERATION, op_arr[i].num, NULL, NULL};
            current_token->type         = OPERATION;
            current_token->value.op_num = op_arr[i].num;
            current_token->left         = NULL;
            current_token->right        = NULL;

            break; 
        }
    }

    // It is Variable
    if (current_token->type != OPERATION)
    {
        // add variable

        int num_var = find_variable(name, all_var);
        if  (num_var == NO_THIS_VAR) num_var = insert_new_variable(name, all_var);
        
        // *current_token = {VARIABLE, num_var, NULL, NULL};
        current_token->type          = VARIABLE;
        current_token->value.var_num = num_var;
        current_token->left          = NULL;
        current_token->right         = NULL;

    }

}


static void get_oper(int* current_symbol, char* arr_file_tree, Node* current_token)
{
    char op[2] = {}; // ???
    op[0] = arr_file_tree[*current_symbol];
    (*current_symbol)++;

    for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
    {
        if (strcmp(op_arr[i].name, op) == 0)
        {
            // *current_token = {OPERATION, op_arr[i].num, NULL, NULL};
            current_token->type         = OPERATION;
            current_token->value.op_num = op_arr[i].num;
            current_token->left         = NULL;
            current_token->right        = NULL;

            break; 
        }
    }
    if (current_token->type == DEFAULT) printf("SYNTAX ERROR\n");
}




int find_variable(char* var_name, VariableArr* all_var)
{
    for (size_t i = 0; i < all_var->size; i++)
    {
        if (strcmp(all_var->arr[i].name, var_name) == 0) 
        { 
            printf("FIND!");
            return all_var->arr[i].num; 
        }
    }

    return NO_THIS_VAR; 
}


int insert_new_variable(char* var_name, VariableArr* all_var)
{
    all_var->size++;

    all_var->arr[all_var->size - 1].num = (int)all_var->size;
    strcpy(all_var->arr[all_var->size - 1].name, var_name);

    return (int)all_var->size;
}


void print_token(Token* token, VariableArr* all_var)
{
    for (size_t i = 0; i < token->size; i++)
    {
        if (token->array[i].type == NUMBER)    printf("%d", token->array[i].value.num);
        if (token->array[i].type == VARIABLE)  printf("%s", all_var->arr[token->array[i].value.var_num - 1].name);
        if (token->array[i].type == OPERATION) printf("%s", op_arr[token->array[i].value.op_num].name);
    }
}