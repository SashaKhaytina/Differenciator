#include "differenciator_h.h" 
#include "math_commands.h"
#include "for_dump.h"
#include "tree_commands.h"
#include "input_tree.h"
#include "differentiation.h"

// enum TypeNode
// {
//     NUMBER,
//     VARIABLE,
//     OPERATION
// };

// enum Operation
// {
//     ADD,
//     SUB,
//     MUL,
//     DIV,
// };

// // Как реализовать переменные? Сделать структуру {num, name} и их массив / просто массив где номер - индекс..
// // И куда положить этот массив? В Tree?

// struct Variable
// {
//     int num;
//     char* name;
// };

// struct Node
// {
//     TypeNode type;
//     int      value; // само число или номер переменной или номер операции 
//     Node*    left;
//     Node*    right;
// };

// struct Tree
// {
//     Node* root;
// };


// Node* create_new_node(TypeNode type, int value, Node* left, Node* right);
void print_tree(Node* node, VariableArr* all_var);
void print_node(Node* node, VariableArr* all_var);


int main()
{
    FILE* file = fopen(FILE_MATH, "r");
    Tree tree = {};
    ForDump st_dump = {};

    VariableArr all_var = {};

    // tree.root = create_new_node(OPERATION, DIV, 
    //                             create_new_node(OPERATION, ADD, 
    //                                             create_new_node(VARIABLE, 1, NULL, NULL),
    //                                             create_new_node(NUMBER, 6, NULL, NULL)),
    //                             create_new_node(NUMBER, 20, NULL, NULL));

    get_tree(file, &tree, &all_var);

    // write all_var
    for (int i = 0; i < all_var.size; i++)
    {
        printf("%d: %c - name, %d - num\n", i, all_var.arr[i].name, all_var.arr[i].num);
    }

    printf("HE CAN READ\n");
    dump(tree.root, &st_dump, &all_var);
    
    print_tree(tree.root, &all_var);

    printf("\n");

    solve_subtree(tree.root);
    dump(tree.root, &st_dump, &all_var);
    print_tree(tree.root, &all_var);

    // printf("GET DIFF\n");
    // Tree diff_tree = {};
    // diff_tree.root = diff(tree.root);
    // print_tree(diff_tree.root, &all_var);
}


// Node* create_new_node(TypeNode type, int value, Node* left, Node* right)
// {
//     Node* new_node = (Node*) calloc(1, sizeof(Node));
//     *new_node = {type, value, left, right};
//     return new_node;
// }


void print_tree(Node* node, VariableArr* all_var)
{   
    if (node == NULL) return;

    printf("(");
    print_tree(node->left, all_var);

    
    print_node(node, all_var);
    
    print_tree(node->right, all_var);
    printf(")");
}


void print_node(Node* node, VariableArr* all_var)
{
    switch (node->type)
    {
    case NUMBER:
    {
        printf("%d", node->value);
        break;
    }

    case VARIABLE:
    {
        // char* var_name = find_var_name(node->value); // тут номер переменной
        // printf("%s", var_name);

        // Is there a need check here?
        for (int i = 0; i < all_var->size; i++) 
        {
            // printf("%c - i var\n", all_var->arr[i].name);
            if (all_var->arr[i].num == node->value) { printf("%c", all_var->arr[i].name); break; }
        }
        // printf("x");
        break;
    }

    case OPERATION:
    {
        int len_struct_arr = (int) (sizeof(op_arr) / sizeof(Operation));
        for (int i = 0; i < len_struct_arr; i++)
        {
            if (op_arr[i].num == node->value) { printf("%s", op_arr[i].name); break; }
        }
        // switch (node->value)
        // {
        // case ADD:
        // {
        //     printf("+");
        //     break;
        // }

        // case SUB:
        // {
        //     printf("-");
        //     break;
        // }

        // case MUL:
        // {
        //     printf("*");
        //     break;
        // }

        // case DIV:
        // {
        //     printf("/");
        //     break;
        // }
        
        // default:
        // {
        //     printf("ERROR num operation\n");
        //     break;
        // }
        // }
        break;
    }
    
    default:
    {
        printf("ERROR type node\n");
        break;
    }
    }
}
