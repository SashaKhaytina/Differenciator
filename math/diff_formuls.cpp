#include "diff_formuls.h"

#include "differentiation.h"
#include "math_commands.h"

#include "../tree_s__commands/tree_commands.h"
#include "../dump/tex_dump.h"


static Node* copy_branch(Node* current_node);




Node* diff_add(Node* current_node, FILE* file, VariableArr* all_var)
{

    tex_dump_add(file, current_node, all_var);
    
    Node* diff_node = _ADD(_DIFF(_LEFT), _DIFF(_RIGHT));
    solve(diff_node);
    
    tex_dump_end(file, current_node, diff_node, all_var);

    return diff_node;
}


Node* diff_sub(Node* current_node, FILE* file, VariableArr* all_var)
{
    tex_dump_sub(file, current_node, all_var);

    Node* diff_node = _SUB(_DIFF(_LEFT), _DIFF(_RIGHT));
    solve(diff_node);

    tex_dump_end(file, current_node, diff_node, all_var);

    return diff_node;
}


Node* diff_mul(Node* current_node, FILE* file, VariableArr* all_var)
{
    tex_dump_mul(file, current_node, all_var);

    Node* diff_node = _ADD(_MUL(_DIFF(_LEFT), _COPY(_RIGHT)),
                           _MUL(_COPY(_LEFT), _DIFF(_RIGHT)));
    solve(diff_node);

    tex_dump_end(file, current_node, diff_node, all_var);

    return diff_node;
}


Node* diff_div(Node* current_node, FILE* file, VariableArr* all_var)
{
    tex_dump_div(file, current_node, all_var);

    Node* diff_node = _DIV(_SUB(
                                _MUL(_DIFF(_LEFT), _COPY(_RIGHT)),
                                _MUL(_COPY(_LEFT), _DIFF(_RIGHT))), 

                            _MUL(_COPY(_RIGHT), _COPY(_RIGHT)));
    solve(diff_node);


    tex_dump_end(file, current_node, diff_node, all_var);
    
    
    return diff_node;
}


Node* diff_sin(Node* current_node, FILE* file, VariableArr* all_var)
{
    tex_dump_sin(file, current_node, all_var);

    Node* diff_node = _MUL(_COS(_COPY(_RIGHT)), _DIFF(_RIGHT));

    solve(diff_node);

    tex_dump_end(file, current_node, diff_node, all_var);
    
    return diff_node;

}


Node* diff_cos(Node* current_node, FILE* file, VariableArr* all_var)
{
    tex_dump_cos(file, current_node, all_var);

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

    Node* diff_node = _DIV(_DIFF(_RIGHT), _COPY(_RIGHT));
    solve(diff_node);
    
    tex_dump_end(file, current_node, diff_node, all_var);
    
    return diff_node;

}



Node* diff_pow(Node* current_node, FILE* file, VariableArr* all_var) // TODO: 3^x will not work
{
    tex_dump_pow(file, current_node, all_var);
    
    Node* diff_node = _MUL(_MUL(_COPY(_RIGHT), _POW(_COPY(_LEFT), _SUB(_RIGHT, _NUM(1)))), _DIFF(_LEFT));
    solve(diff_node);

    tex_dump_end(file, current_node, diff_node, all_var);

    return diff_node;

}



static Node* copy_branch(Node* current_node)
{
    if (current_node == NULL) return NULL;


    // ????????????????????????????
    Elem_t val = 0;
    if      (current_node->type == NUMBER)    val = current_node->value.num;
    else if (current_node->type == VARIABLE)  val = (Elem_t) current_node->value.var_num;
    else if (current_node->type == OPERATION) val = (Elem_t) current_node->value.op_num;

    return create_new_node(current_node->type, val, copy_branch(current_node->left), copy_branch(current_node->right));
    

}
