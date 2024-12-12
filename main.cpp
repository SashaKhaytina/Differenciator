#include "differenciator_h.h" 
#include "math_commands.h"
#include "for_dump.h"
#include "tree_commands.h"
#include "input_tree.h"
#include "differentiation.h"



void print_tree(Node* node, VariableArr* all_var);
void print_node(Node* node, VariableArr* all_var);


int main()
{
    FILE* file = fopen(FILE_MATH, "r");
    Tree tree = {};
    ForDump st_dump = {};
    ForTexDump st_tex_dump = {};

    VariableArr all_var = {};
    

    // tree.root = create_new_node(OPERATION, DIV, 
    //                             create_new_node(OPERATION, ADD, 
    //                                             create_new_node(VARIABLE, 1, NULL, NULL),
    //                                             create_new_node(NUMBER, 6, NULL, NULL)),
    //                             create_new_node(NUMBER, 20, NULL, NULL));




    get_tree(file, &tree, &all_var);

    // write all_var
    // for (int i = 0; i < all_var.size; i++)
    // {
    //     printf("%d: %c - name, %d - num\n", i, all_var.arr[i].name, all_var.arr[i].num);
    // }

    printf("HE CAN READ\n");
    dump(tree.root, &st_dump, &all_var);
    
    print_tree(tree.root, &all_var);
    printf("\n");

    // SOLVE_____________________________________________________________________________________________________________



    solve(tree.root);
    dump(tree.root, &st_dump, &all_var);
    print_tree(tree.root, &all_var);
    printf("\n");



    printf("\n\n\n\n");
    print_tree(tree.root, &all_var);
    printf("\n\n\n\n");


    // DIFF______________________________________________________________________________________________________________

    printf("GET DIFF\n");
    FILE* file_tex = fopen(FILE_TEX, "w");
    Tree diff_tree = {};

    diff_tree.root = diff(tree.root, file_tex, &all_var);
    
    solve(diff_tree.root);
    dump(diff_tree.root, &st_dump, &all_var);
    print_tree(diff_tree.root, &all_var);
    printf("\n");

    dump(diff_tree.root, &st_dump, &all_var);

}



void print_tree(Node* node, VariableArr* all_var)
{   
    if (node == NULL) return;

    if (node->type != OPERATION) print_node(node, all_var);
    else
    {
        printf("(");
        print_tree(node->left, all_var);

        
        print_node(node, all_var);
        
        print_tree(node->right, all_var);
        printf(")");
    }
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
        // Is there a need check here?
        for (int i = 0; i < all_var->size; i++) 
        {
            if (all_var->arr[i].num == node->value) { printf("%s", all_var->arr[i].name); break; }
        }
        break;
    }

    case OPERATION:
    {
        for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
        {
            if (op_arr[i].num == node->value) { printf("%s", op_arr[i].name); break; }
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



