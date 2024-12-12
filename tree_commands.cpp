#include "tree_commands.h"

#include <stdio.h>
#include <malloc.h>

#include "math_commands.h"

Node* create_new_node(TypeNode type, int value, Node* left, Node* right)
{
    Node* new_node = (Node*) calloc(1, sizeof(Node));
    *new_node = {type, value, left, right};
    return new_node;
}


TypeNode solve_subtree(Node* current_node, int* diference)
{
    if (current_node->type == OPERATION)
    {


        bool is_null = (current_node->left == NULL);

        bool condition_left  = (is_null || (solve_subtree(current_node->left, diference) == NUMBER));
        bool condition_right = (solve_subtree(current_node->right, diference) == NUMBER);

        if (condition_left && condition_right)
        {
            for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
            {
                if (op_arr[i].num == current_node->value) { current_node->value = op_arr[i].calculate(current_node->left, current_node->right); break; }
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
            if (op_arr[i].num == current_node->value) {op_arr[i].triv_calculate(current_node, diference); break;}
        }
    }
}


void solve(Node* current_node)
{
    int diference = 1;
    while (diference != 0)
    {
        diference = 0;
        solve_subtree(current_node, &diference);
        trivial_solver(current_node, &diference);
    }

}
