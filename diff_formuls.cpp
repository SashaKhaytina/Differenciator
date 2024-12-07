#include "diff_formuls.h"
#include "math_commands.h"

#include "tree_commands.h"
#include "differentiation.h" // it is bad...

static Node* copy_branch(Node* current_node);



Node* diff_add(Node* current_node)
{
    return create_new_node(OPERATION, ADD, diff(current_node->left), diff(current_node->right)); // TODO: DSL
}


Node* diff_sub(Node* current_node)
{
    return create_new_node(OPERATION, SUB, diff(current_node->left), diff(current_node->right));
}


Node* diff_mul(Node* current_node)
{
    return create_new_node(OPERATION, ADD, 
                                        create_new_node(OPERATION, MUL, diff(current_node->left), copy_branch(current_node->right)), 
                                        create_new_node(OPERATION, MUL, copy_branch(current_node->left), diff(current_node->right)));
}


Node* diff_div(Node* current_node)
{
    return create_new_node(OPERATION, DIV, 
                                        create_new_node(OPERATION, SUB, 
                                            create_new_node(OPERATION, MUL, diff(current_node->left), copy_branch(current_node->right)), 
                                            create_new_node(OPERATION, MUL, copy_branch(current_node->left), diff(current_node->right))),

                                        create_new_node(OPERATION, MUL, copy_branch(current_node->right), copy_branch(current_node->right)));
}

// TODO: pow, sin, cos, log


static Node* copy_branch(Node* current_node)
{
    if (current_node == NULL) return NULL;
    return create_new_node(current_node->type, current_node->value, copy_branch(current_node->left), copy_branch(current_node->right));

}
