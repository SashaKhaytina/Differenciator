#include "diff_formuls.h"

#include "differentiation.h"
#include "math_commands.h"

#include "../tree_s__commands/tree_commands.h"
#include "../dump/tex_dump.h"

#include <math.h>


static Node* copy_branch(Node* current_node);




Node* diff_add(Node* current_node, FILE* file, VariableArr* all_var)
{
    assert(current_node);
    assert(file);
    assert(all_var);


    tex_dump_add(file, current_node, all_var);
    
    Node* diff_node = _ADD(_DIFF(_LEFT), _DIFF(_RIGHT));
    solve(diff_node);
    
    tex_dump_end(file, current_node, diff_node, all_var);

    return diff_node;
}


Node* diff_sub(Node* current_node, FILE* file, VariableArr* all_var)
{
    assert(current_node);
    assert(file);
    assert(all_var);


    tex_dump_sub(file, current_node, all_var);

    Node* diff_node = _SUB(_DIFF(_LEFT), _DIFF(_RIGHT));
    solve(diff_node);

    tex_dump_end(file, current_node, diff_node, all_var);

    return diff_node;
}


Node* diff_mul(Node* current_node, FILE* file, VariableArr* all_var)
{
    assert(current_node);
    assert(file);
    assert(all_var);


    tex_dump_mul(file, current_node, all_var);

    Node* diff_node = _ADD(_MUL(_DIFF(_LEFT), _COPY(_RIGHT)),
                           _MUL(_COPY(_LEFT), _DIFF(_RIGHT)));
    solve(diff_node);

    tex_dump_end(file, current_node, diff_node, all_var);

    return diff_node;
}


Node* diff_div(Node* current_node, FILE* file, VariableArr* all_var)
{
    assert(current_node);
    assert(file);
    assert(all_var);


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
    assert(current_node);
    assert(file);
    assert(all_var);


    tex_dump_sin(file, current_node, all_var);

    Node* diff_node = _MUL(_COS(_COPY(_RIGHT)), _DIFF(_RIGHT));

    solve(diff_node);

    tex_dump_end(file, current_node, diff_node, all_var);
    
    return diff_node;

}


Node* diff_cos(Node* current_node, FILE* file, VariableArr* all_var)
{
    assert(current_node);
    assert(file);
    assert(all_var);


    tex_dump_cos(file, current_node, all_var);

    Node* diff_node = _MUL(_MUL(
                                _NUM(-1), 
                                _SIN(_COPY(_RIGHT))), 
                           _DIFF(_RIGHT));
    solve(diff_node);
    
    tex_dump_end(file, current_node, diff_node, all_var);
    
    return diff_node;

}



Node* diff_ln(Node* current_node, FILE* file, VariableArr* all_var)
{
    assert(current_node);
    assert(file);
    assert(all_var);


    tex_dump_ln(file, current_node, all_var);

    Node* diff_node = _DIV(_DIFF(_RIGHT), _COPY(_RIGHT));
    solve(diff_node);
    
    tex_dump_end(file, current_node, diff_node, all_var);
    
    return diff_node;

}



Node* diff_pow(Node* current_node, FILE* file, VariableArr* all_var)
{
    assert(current_node);
    assert(file);
    assert(all_var);


    tex_dump_pow(file, current_node, all_var);
    
    Node* diff_node = _MUL(_POW(_LEFT, _RIGHT),
                           _DIFF(_MUL(_LN(_LEFT), _RIGHT)));

    solve(diff_node);

    tex_dump_end(file, current_node, diff_node, all_var);

    return diff_node;

}



static Node* copy_branch(Node* current_node)
{
    if (current_node == NULL) return NULL;

    Elem_t val = 0;
    if (current_node->type == NUMBER)   return create_new_node_num(current_node->type, current_node->value.num,     copy_branch(current_node->left), copy_branch(current_node->right));
    if (current_node->type == VARIABLE) return create_new_node_var(current_node->type, current_node->value.var_num, copy_branch(current_node->left), copy_branch(current_node->right));
    else                                return create_new_node_op (current_node->type, current_node->value.op_num,  copy_branch(current_node->left), copy_branch(current_node->right));

}
