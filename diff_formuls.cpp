#include "diff_formuls.h"
#include "math_commands.h"

#include "tree_commands.h"
#include "differentiation.h" // it is bad...
#include "tex_dump.h"


static Node* copy_branch(Node* current_node);



Node* diff_add(Node* current_node, FILE* file, VariableArr* all_var)
{

    // tex_dump(current_node, diff_node, st_dump, all_var); // тут сначала должен прописывать d(current_node) = d() + d()
    fprintf(file, "$ d(");
    fprint_tree(file, current_node, all_var);
    fprintf(file, ") = d(");
    fprint_tree(file, current_node->left, all_var);
    fprintf(file, ") + d(");
    fprint_tree(file, current_node->right, all_var);
    fprintf(file, ")$\n\n");
    fprintf(file, "Посчитаем составные части:\n\n");

    
    
    Node* diff_node = create_new_node(OPERATION, ADD, diff(current_node->left, file, all_var), diff(current_node->right, file, all_var)); // TODO: DSL
    fprintf(file, "Получилось:\n\n");
    fprintf(file, "$ d(");
    fprint_tree(file, current_node, all_var);
    fprintf(file, ") = ");
    fprint_tree(file, diff_node, all_var);
    fprintf(file, "$\n\n");

    // return create_new_node(OPERATION, ADD, diff(current_node->left), diff(current_node->right)); // TODO: DSL
    return diff_node;
}


// Node* diff_sub(Node* current_node)
// {
//     return create_new_node(OPERATION, SUB, diff(current_node->left), diff(current_node->right));
// }


// Node* diff_mul(Node* current_node)
// {
//     return create_new_node(OPERATION, ADD, 
//                                         create_new_node(OPERATION, MUL, diff(current_node->left), copy_branch(current_node->right)), 
//                                         create_new_node(OPERATION, MUL, copy_branch(current_node->left), diff(current_node->right)));
// }


// Node* diff_div(Node* current_node)
// {
//     return create_new_node(OPERATION, DIV, 
//                                         create_new_node(OPERATION, SUB, 
//                                             create_new_node(OPERATION, MUL, diff(current_node->left), copy_branch(current_node->right)), 
//                                             create_new_node(OPERATION, MUL, copy_branch(current_node->left), diff(current_node->right))),

//                                         create_new_node(OPERATION, MUL, copy_branch(current_node->right), copy_branch(current_node->right)));
// }

// // TODO: pow, sin, cos, log


// Node* diff_sin(Node* current_node)
// {
//     return create_new_node(OPERATION, MUL, 
//                                         create_new_node(OPERATION, COS, NULL, copy_branch(current_node->right)),
//                                         diff(current_node->right));

// }


// Node* diff_cos(Node* current_node)
// {
//     return create_new_node(OPERATION, MUL, 
//                                         create_new_node(OPERATION, MUL,
//                                                                     create_new_node(NUMBER, -1, NULL, NULL),
//                                                                     create_new_node(OPERATION, SIN, NULL, copy_branch(current_node->right))), 
//                                         diff(current_node->right));

// }



// Node* diff_log(Node* current_node)
// {
//     return create_new_node(OPERATION, DIV,
//                                         diff(current_node->right),
//                                         copy_branch(current_node->right));

// }



// Node* diff_pow(Node* current_node)
// {
// //     return create_new_node(OPERATION, MUL, 
// //                                         create_new_node()

// }



// static Node* copy_branch(Node* current_node)
// {
//     if (current_node == NULL) return NULL;
//     return create_new_node(current_node->type, current_node->value, copy_branch(current_node->left), copy_branch(current_node->right));

// }
