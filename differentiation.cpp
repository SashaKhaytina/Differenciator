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
            tex_dump_num(file, current_node, all_var);

            Node* diff_node = create_new_node(NUMBER, 0, NULL, NULL);
            
            return diff_node;
            break; // this not use
        }
        
        case VARIABLE:
        {
            tex_dump_var(file, current_node, all_var);

            Node* diff_node = create_new_node(NUMBER, 1, NULL, NULL);

            return diff_node;
        }

        case OPERATION:
        {
            Node* diff_node = NULL;
            
            for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
            {
                if (op_arr[i].num == current_node->value.op_num) {diff_node = op_arr[i].diff_form(current_node, file, all_var); break;}//return op_arr[i].diff_form(current_node, file, all_var);
            }

            return diff_node;

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