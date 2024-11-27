#include "diff_formuls.h"

#include "tree_commands.h"
#include "differentiation.h" // it is bad...

Node* diff_add(Node* current_node)
{
    return create_new_node(OPERATION, ADD, diff(current_node->left), diff(current_node->right));
}