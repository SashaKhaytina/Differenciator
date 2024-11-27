#include "differentiation.h"

#include "tree_commands.h"
#include "diff_formuls.h"


// in main: dif_tree.root = diff(tree.root) // tree - old, dif_tree - new
Node* diff(Node* current_node)
{
    if (current_node == NULL) return NULL;

    switch (current_node->type)
    {
        case NUMBER:
        {
            return create_new_node(NUMBER, 0, NULL, NULL);
            break; // this not use
        }
        
        case VARIABLE:
        {
            return create_new_node(NUMBER, 1, NULL, NULL);
            break; // this not use
        }

        case OPERATION:
        {
            // return create_new_node(NUMBER, 1, NULL, NULL);
            // return FUNC_FOR_THIS_OP;
            if (current_node->value == ADD) return diff_add(current_node);
            break; // this not use
        }
    
        default:
        {
            printf("ERROR\n");
            break;
        }
    }

    // if (current_node->type == NUMBER) return create_new_node(NUMBER, 0, NULL, NULL);
    // if (current_node->type == VARIABLE) return create_new_node(NUMBER, 0, NULL, NULL)

}