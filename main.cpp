#include "differenciator_h.h" 
#include "math/math_commands.h"
#include "dump/for_dump.h"
#include "tree_s__commands/tree_commands.h"
#include "get_math_task/input_tree.h"
#include "get_math_task/token.h"
#include "math/differentiation.h"
#include "tree_s__commands/free.h"



// void print_tree(Node* node, VariableArr* all_var);
// void print_node(Node* node, VariableArr* all_var);
// void free_val(VariableArr* all_var);

int main()
{
    FILE* file = fopen(FILE_MATH, "r");
    Tree tree = {};

    ForDump dumps_counter = 0;

    VariableArr all_var = {};

    Token token = {};
    

    get_tree(file, &tree, &all_var, &token);
    
    dump(tree.root, &dumps_counter, &all_var);
    


    // SOLVE_____________________________________________________________________________________________________________

    // solve(tree.root);
    dump(tree.root, &dumps_counter, &all_var);


    // // DIFF______________________________________________________________________________________________________________
    
    FILE* file_tex = fopen(FILE_TEX, "w");
    Tree diff_tree = {};

    diff_tree.root = diff(tree.root, file_tex, &all_var);

    
    // solve(diff_tree.root);
    dump(diff_tree.root, &dumps_counter, &all_var);


    dump(diff_tree.root, &dumps_counter, &all_var);

    fclose(file);
    fclose(file_tex);

    free_tree(tree.root);
    free_tokens(&token);

    printf("Print diff\n");
    
    free_tree(diff_tree.root); diff_tree.root = NULL;
    free_val(&all_var);


}




// void free_val(VariableArr* all_var)
// {
//     for (int i = 0; i < all_var->size; i++)
//     {
//         printf("ii - %d", i);
//         free(all_var->arr[i].name); all_var->arr[i].name = NULL;
//     }
// }


// void print_tree(Node* node, VariableArr* all_var)
// {   
//     if (node == NULL) return;

//     if (node->type != OPERATION) print_node(node, all_var);
//     else
//     {
//         printf("(");
//         print_tree(node->left, all_var);

        
//         print_node(node, all_var);
        
//         print_tree(node->right, all_var);
//         printf(")");
//     }
// }


// void print_node(Node* node, VariableArr* all_var)
// {
//     switch (node->type)
//     {
//     case NUMBER:
//     {
//         printf("%g", node->value.num);
//         break;
//     }

//     case VARIABLE:
//     {
//         for (int i = 0; i < all_var->size; i++) 
//         {
//             if (all_var->arr[i].num == node->value.var_num) { printf("%s", all_var->arr[i].name); break; }
//         }
//         break;
//     }

//     case OPERATION:
//     {
//         for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
//         {
//             if (op_arr[i].num == node->value.op_num) { printf("%s", op_arr[i].name); break; }
//         }
//         break;
//     }
    
//     default:
//     {
//         printf("ERROR type node\n");
//         break;
//     }
//     }
// }



