#include "tree_commands.h"

#include <stdio.h>
#include <malloc.h>

#include "math_commands.h"

Node* create_new_node(TypeNode type, Elem_t num , Node* left, Node* right)
{
    Node* new_node = (Node*) calloc(1, sizeof(Node));
    // *new_node = {type, val, left, right};
    new_node->type = type;

    if      (type == NUMBER)    new_node->value.num     = num;
    else if (type == VARIABLE)  new_node->value.var_num = (int) num;
    else if (type == OPERATION) new_node->value.op_num  = (AllOperations) num; // is it norm hahahahah?

    new_node->left  = left;
    new_node->right = right;

    return new_node;
}


TypeNode solve_subtree(Node* current_node, int* diference)
{
    if (current_node == NULL) return DEFAULT;
    if (current_node->type == OPERATION)
    {


        bool is_null = (current_node->left == NULL);

        bool condition_left  = (is_null || (solve_subtree(current_node->left, diference) == NUMBER));
        bool condition_right = (solve_subtree(current_node->right, diference) == NUMBER);
        printf("he calcul patrs\n");

        if (condition_left && condition_right)
        {
            for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
            {
                if (op_arr[i].num == current_node->value.op_num) 
                { 
                    current_node->value.num = op_arr[i].calculate(current_node->left, current_node->right); // It is ok? (value.num)
                    printf("he calcul\n");
                    break; 
                }
            }

            current_node->type = NUMBER;
            current_node->left = NULL;
            current_node->right = NULL;

            (*diference)++;
        }
    }

    return current_node->type;
}

void trivial_solver(Node* current_node, int* diference)
{
    if (current_node == NULL) return;
    

    trivial_solver(current_node->left, diference);
    trivial_solver(current_node->right, diference);

    if (current_node->type == OPERATION)
    {
        for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
        {
            if (op_arr[i].num == current_node->value.op_num) 
            {
                op_arr[i].triv_calculate(current_node, diference); 
                break;
            }
        }
    }
}


void solve(Node* current_node)
{
    int diference = 1;
    while (diference != 0)
    {
        diference = 0;
        printf("Go to solve_subtree\n");
        solve_subtree(current_node, &diference);
        printf("Go out solve_subtree\n");

        printf("Go to trivial_solver\n");
        trivial_solver(current_node, &diference);
        printf("Go out trivial_solver\n");
    }

}
