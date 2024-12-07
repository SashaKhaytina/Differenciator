#include "input_tree.h"
#include "math_commands.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "tree_commands.h"
#include "recursive_descent_algorithm.h"
#include "token.h"

static void read_new_node(Node* current_node, int* point_current_letter, char* arr_file_tree, BranchDirection line, VariableArr* all_var);
static size_t size_file(FILE* file);

static size_t size_file(FILE* file)
{
    size_t size = 0;

    fseek(file, 0, SEEK_END);
    size = (size_t) ftell(file);
    fseek(file, 0, SEEK_SET);

    return size;
}


// static void read_new_node(Node* current_node, int* point_current_letter, char* arr_file_tree, BranchDirection line, VariableArr* all_var)
// {
//         *point_current_letter += 1;


//         if (line == RIGHT)
//         {
//             current_node->right = create_new_node(DEFAULT, 0, NULL, NULL); // ????????????????????????????????????????????????

//             fill_tree(current_node->right, point_current_letter, arr_file_tree, all_var);
//         }
//         else
//         {   
//             current_node->left = create_new_node(DEFAULT, 0, NULL, NULL);
//             fill_tree(current_node->left, point_current_letter, arr_file_tree, all_var);
//         }
// }




void get_tree(FILE* file, Tree* tree, VariableArr* all_var)
{
    Token token = {};
    size_t len_text = size_file(file);

    char arr_file_tree[len_text+1] = {};

    size_t count_symbol = fread(arr_file_tree, sizeof(char), len_text, file);

    init_token(&token, len_text);
    printf("INIT\n");

    get_token(&token, arr_file_tree, all_var);
    printf("GET\n");

    // for (size_t i = 0; i<all_var->size;i++)
    // {
    //     printf("%s - %d \n", all_var->arr[i].name, all_var->arr[i].num);
    // }
    
    print_token(&token, all_var);
    printf("\n");

    tree->root = GetG(&token, all_var);
}








// void fill_tree(Node* current_node, int* point_current_letter, char* arr_file_tree, VariableArr* all_var)
// {
// //     // тут надо прочитать файл
    
// //     get_tree(node->left);



//     // pass_spaces(point_current_letter, arr_file_tree);
//     printf("IN fill_tree\n");

//     if (arr_file_tree[*point_current_letter] == ')') { printf("GO_OUT\n"); *point_current_letter +=1; return; } 


//     if (arr_file_tree[*point_current_letter] == '(') // для левого поддерева
//     {
//         printf("GO_TO LEFT\n");
//         read_new_node(current_node, point_current_letter, arr_file_tree, LEFT, all_var);
//     }




//     // ---------------------------------------------------------------------------------------------------------------

//     // тут должен быть ввод текущей ячейки     это вообще про что?

//     if (isalpha(arr_file_tree[*point_current_letter]) != 0) // variable
//     {
//         current_node->type  = VARIABLE;
//         // current_node->value = arr_file_tree[*point_current_letter];
//         printf("VARIABLE: %d - type, %c - name\n", current_node->type, current_node->value);

//         // *point_current_letter += 1;
//         // FUNC ADD VARIABLE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//         bool know_this_var = false;
//         for (size_t i = 0; i < all_var->size; i++)
//         {
//             // printf("%c - arr_file_tree[*point_current_letter]\n", arr_file_tree[*point_current_letter]);
//             // printf("%c - all_var->arr[i].name\n", all_var->arr[i].name);

//             if (all_var->arr[i].name == arr_file_tree[*point_current_letter]) { know_this_var = true; current_node->value = all_var->arr[i].num; printf("FIND!\n"); break; }
//         }

//         // printf("%d - know_this_var\n", know_this_var);

//         if (!know_this_var)
//         {
//             all_var->size++;
//             all_var->arr[all_var->size - 1] = {(int)all_var->size, arr_file_tree[*point_current_letter]};
//             current_node->value = all_var->size; // Говорим, что ЭТОТ номер ее
//         }
//         // printf("PRINT 2 VARIABLE: %d - type, %d - num (val)\n", current_node->type, current_node->value);
//         *point_current_letter += 1;
//     }
//     else if (isdigit(arr_file_tree[*point_current_letter]) != 0) // num
//     {
//         current_node->type  = NUMBER;
//         int num = 0;

//         // read num (value)
//         while (isdigit(arr_file_tree[*point_current_letter]) != 0)
//         {
//             num += arr_file_tree[*point_current_letter] - 48;
//             num *= 10;
//             *point_current_letter += 1;
//         }
//         num /= 10;
//         // *point_current_letter -= 1;

//         current_node->value = num;

//         printf("NUMBER: %d - type, %d - value\n", current_node->type, current_node->value);
//     }
//     else // operation
//     {
//         current_node->type  = OPERATION;

//         char op[10] = {arr_file_tree[*point_current_letter]}; // для длинных функций должен быть нормальный ввод. (если 2 буквы подряд - ф-я, а не переменная)
//         *point_current_letter += 1;

//         int len_struct_arr = (int) (sizeof(op_arr) / sizeof(Operation));
//         for (int i = 0; i < len_struct_arr; i++)
//         {
//             if (strcmp(op_arr[i].name, op) == 0) { current_node->value = op_arr[i].num; break; }
//         }
//         printf("OPER: %d - type, %d - value\n", current_node->type, current_node->value);


//     }


//     // -----------------------------------------------------------------------------------------------------------------



//     // pass_spaces(point_current_letter, arr_file_tree);


//     if (arr_file_tree[*point_current_letter] == '(') // для правого поддерева
//     {
//         printf("GO_TO RIGHT\n");
//         read_new_node(current_node, point_current_letter, arr_file_tree, RIGHT, all_var);
//     }


//     // pass_spaces(point_current_letter, arr_file_tree);

//     if (arr_file_tree[*point_current_letter] == ')') { printf("GO_OUT\n"); *point_current_letter +=1; return; }



// }






