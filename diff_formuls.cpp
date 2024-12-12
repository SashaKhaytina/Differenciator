#include "diff_formuls.h"
#include "math_commands.h"

#include "tree_commands.h"
#include "differentiation.h" // it is bad...
#include "tex_dump.h"


static Node* copy_branch(Node* current_node);



// void tex_dump_end(FILE* file, Node* current_node, Node* diff_node, VariableArr* all_var)
// {
//     fprintf(file, "Получилось:\n\n");
//     fprintf(file, "$ d(");
//     fprint_tree(file, current_node, all_var);
//     fprintf(file, ") = ");
//     fprint_tree(file, diff_node, all_var);
//     fprintf(file, "$\n\n");
// }



// void tex_dump_add(FILE* file, Node* current_node, VariableArr* all_var)
// {
//     fprintf(file, "$ d(");
//     fprint_tree(file, current_node, all_var);
//     fprintf(file, ") = d(");
//     fprint_tree(file, current_node->left, all_var);
//     fprintf(file, ") + d(");
//     fprint_tree(file, current_node->right, all_var);
//     fprintf(file, ")$\n\n");
//     fprintf(file, "Посчитаем составные части:\n\n");
// }


// void tex_dump_sub(FILE* file, Node* current_node, VariableArr* all_var)
// {
//     fprintf(file, "$ d(");
//     fprint_tree(file, current_node, all_var);
//     fprintf(file, ") = d(");
//     fprint_tree(file, current_node->left, all_var);
//     fprintf(file, ") - d(");
//     fprint_tree(file, current_node->right, all_var);
//     fprintf(file, ")$\n\n");
//     fprintf(file, "Посчитаем составные части:\n\n");
// }



Node* diff_add(Node* current_node, FILE* file, VariableArr* all_var)//, FILE* file, VariableArr* all_var)
{

    // tex_dump(current_node, diff_node, st_dump, all_var); // тут сначала должен прописывать d(current_node) = d() + d()
    // fprintf(file, "$ d(");
    // fprint_tree(file, current_node, all_var);
    // fprintf(file, ") = d(");
    // fprint_tree(file, current_node->left, all_var);
    // fprintf(file, ") + d(");
    // fprint_tree(file, current_node->right, all_var);
    // fprintf(file, ")$\n\n");
    // fprintf(file, "Посчитаем составные части:\n\n");
    tex_dump_add(file, current_node, all_var);


    
    
    // Node* diff_node = create_new_node(OPERATION, ADD, diff(current_node->left, file, all_var), diff(current_node->right, file, all_var)); // TODO: DSL
    Node* diff_node = _ADD(_DIFF(_LEFT), _DIFF(_RIGHT));
    solve(diff_node);
    
    tex_dump_end(file, current_node, diff_node, all_var);

    // fprintf(file, "Получилось:\n\n");
    // fprintf(file, "$ d(");
    // fprint_tree(file, current_node, all_var);
    // fprintf(file, ") = ");
    // fprint_tree(file, diff_node, all_var);
    // fprintf(file, "$\n\n");

    // return create_new_node(OPERATION, ADD, diff(current_node->left), diff(current_node->right)); // TODO: DSL
    return diff_node;
}


Node* diff_sub(Node* current_node, FILE* file, VariableArr* all_var)
{
    tex_dump_sub(file, current_node, all_var);
    // Node* diff_node =  create_new_node(OPERATION, SUB, diff(current_node->left, file, all_var), diff(current_node->right, file, all_var));
    Node* diff_node = _SUB(_DIFF(_LEFT), _DIFF(_RIGHT));
    solve(diff_node);

    tex_dump_end(file, current_node, diff_node, all_var);


}


Node* diff_mul(Node* current_node, FILE* file, VariableArr* all_var)
{
    tex_dump_mul(file, current_node, all_var);

    // Node* diff_node = create_new_node(OPERATION, ADD, 
    //                                     create_new_node(OPERATION, MUL, diff(current_node->left, file, all_var), copy_branch(current_node->right)), 
    //                                     create_new_node(OPERATION, MUL, copy_branch(current_node->left), diff(current_node->right, file, all_var)));
    
    Node* diff_node = _ADD(_MUL(_DIFF(_LEFT), _COPY(_RIGHT)),
                           _MUL(_COPY(_LEFT), _DIFF(_RIGHT)));
    solve(diff_node);

    tex_dump_end(file, current_node, diff_node, all_var);

    return diff_node;
}


Node* diff_div(Node* current_node, FILE* file, VariableArr* all_var)
{
    tex_dump_div(file, current_node, all_var);
    // Node* diff_node = create_new_node(OPERATION, DIV, 
    //                                     create_new_node(OPERATION, SUB, 
    //                                         create_new_node(OPERATION, MUL, diff(current_node->left, file, all_var), copy_branch(current_node->right)), 
    //                                         create_new_node(OPERATION, MUL, copy_branch(current_node->left), diff(current_node->right, file, all_var))),

    //                                     create_new_node(OPERATION, MUL, copy_branch(current_node->right), copy_branch(current_node->right)));
    
    Node* diff_node = _DIV(_SUB(
                                _MUL(_DIFF(_LEFT), _COPY(_RIGHT)),
                                _MUL(_COPY(_LEFT), _DIFF(_RIGHT))), 

                            _MUL(_COPY(_RIGHT), _COPY(_RIGHT)));
    solve(diff_node);


    tex_dump_end(file, current_node, diff_node, all_var);
    
    
    return diff_node;
}

// TODO: pow, sin, cos, log


Node* diff_sin(Node* current_node, FILE* file, VariableArr* all_var)
{
    tex_dump_sin(file, current_node, all_var);

    // Node* diff_node = create_new_node(OPERATION, MUL, 
    //                                     create_new_node(OPERATION, COS, NULL, copy_branch(current_node->right)),
    //                                     diff(current_node->right, file, all_var));

    Node* diff_node = _MUL(_COS(_COPY(_RIGHT)), _DIFF(_RIGHT));
    solve(diff_node);

    tex_dump_end(file, current_node, diff_node, all_var);
    
    return diff_node;

}


Node* diff_cos(Node* current_node, FILE* file, VariableArr* all_var)
{
    tex_dump_cos(file, current_node, all_var);

    // Node* diff_node = create_new_node(OPERATION, MUL, 
    //                                     create_new_node(OPERATION, MUL,
    //                                                                 create_new_node(NUMBER, -1, NULL, NULL),
    //                                                                 create_new_node(OPERATION, SIN, NULL, copy_branch(current_node->right))), 
    //                                     diff(current_node->right, file, all_var));

    Node* diff_node = _MUL(_MUL(
                                _NUM(-1), 
                                _SIN(_COPY(_RIGHT))), 
                           _DIFF(_RIGHT));
    solve(diff_node);
    
    tex_dump_end(file, current_node, diff_node, all_var);
    
    return diff_node;

}



Node* diff_log(Node* current_node, FILE* file, VariableArr* all_var)
{
    tex_dump_log(file, current_node, all_var);

    // Node* diff_node = create_new_node(OPERATION, DIV,
    //                                     diff(current_node->right, file, all_var),
    //                                     copy_branch(current_node->right));

    Node* diff_node = _DIV(_DIFF(_RIGHT), _COPY(_RIGHT));
    solve(diff_node);
    
    tex_dump_end(file, current_node, diff_node, all_var);
    
    return diff_node;

}



Node* diff_pow(Node* current_node, FILE* file, VariableArr* all_var)
{
//     return create_new_node(OPERATION, MUL, 
//                                         create_new_node()

}



static Node* copy_branch(Node* current_node)
{
    if (current_node == NULL) return NULL;
    return create_new_node(current_node->type, current_node->value, copy_branch(current_node->left), copy_branch(current_node->right));

}
