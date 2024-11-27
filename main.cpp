

#include "differenciator_h.h" 
#include "for_dump.h"
#include "tree_commands.h"
#include "input_tree.h"

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
void print_tree(Node* node);
void print_node(Node* node);


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
    printf("HE CAN READ\n");
    dump(tree.root, &st_dump);
    
    print_tree(tree.root);
}


// Node* create_new_node(TypeNode type, int value, Node* left, Node* right)
// {
//     Node* new_node = (Node*) calloc(1, sizeof(Node));
//     *new_node = {type, value, left, right};
//     return new_node;
// }


void print_tree(Node* node)
{   
    if (node == NULL) return;

    printf("(");
    print_tree(node->left);

    
    print_node(node);
    
    print_tree(node->right);
    printf(")");
}


void print_node(Node* node)
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
        printf("x");
        break;
    }

    case OPERATION:
    {
        switch (node->value)
        {
        case ADD:
        {
            printf("+");
            break;
        }

        case SUB:
        {
            printf("-");
            break;
        }

        case MUL:
        {
            printf("*");
            break;
        }

        case DIV:
        {
            printf("/");
            break;
        }
        
        default:
        {
            printf("ERROR num operation\n");
            break;
        }
        }
        break;
    }
    
    default:
    {
        printf("ERROR type node\n");
        break;
    }
    }
}
