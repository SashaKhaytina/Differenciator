#include "differentiation.h"
#include "math_commands.h"

#include "tree_commands.h"
#include "tex_dump.h"



// in main: dif_tree.root = diff(tree.root) // tree - old, dif_tree - new
Node* diff(Node* current_node, FILE* file, VariableArr* all_var)
{
    if (current_node == NULL) return NULL;

    switch (current_node->type)
    {
        case NUMBER:
        {
            fprintf(file, "$ d(");
            fprint_tree(file, current_node, all_var);
            fprintf(file, ") = 0$\n\n");
            
            // Node* diff_node = create_new_node(NUMBER, 0, NULL, NULL);
            // tex_dump(current_node, diff_node,st_dump, all_var);
            return create_new_node(NUMBER, 0, NULL, NULL);
            break; // this not use
        }
        
        case VARIABLE:
        {
            fprintf(file, "$ d(");
            fprint_tree(file, current_node, all_var);
            fprintf(file, ") = 1$\n\n");
            return create_new_node(NUMBER, 1, NULL, NULL);
            break; // this not use
        }

        case OPERATION:
        {
            // return create_new_node(NUMBER, 1, NULL, NULL);
            // return FUNC_FOR_THIS_OP;
            int len_struct_arr = (int) (sizeof(op_arr) / sizeof(Operation)); // TODO: why int, why not const
            for (int i = 0; i < len_struct_arr; i++)
            {
                if (op_arr[i].num == current_node->value) return op_arr[i].diff_form(current_node, file, all_var);
            }
            // if (current_node->value == ADD) return diff_add(current_node);
            // if (current_node->value == SUB) return diff_sub(current_node);
            // if (current_node->value == MUL) return diff_mul(current_node);
            // if (current_node->value == DIV) return diff_div(current_node);
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