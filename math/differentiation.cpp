#include "differentiation.h"

#include "math_commands.h"

#include "../tree_s__commands/tree_commands.h"
#include "../dump/tex_dump.h"



Node* diff(Node* current_node, FILE* file, VariableArr* all_var)
{
    if (current_node == NULL) return NULL;

    switch (current_node->type)
    {
        case NUMBER:
        {
            tex_dump_num(file, current_node, all_var);

            Node* diff_node = _NUM(0);

            return diff_node;
        }

        case VARIABLE:
        {
            tex_dump_var(file, current_node, all_var);

            Node* diff_node = _NUM(1);

            return diff_node;
        }

        case OPERATION:
        {
            Node* diff_node = NULL;

            for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
            {
                if (op_arr[i].num == current_node->value.op_num) {diff_node = op_arr[i].diff_form(current_node, file, all_var); break; } // не пиши так никогда, это нечитаемо
            }

            return diff_node;
        }

        default:
        {
            printf("ERROR\n");
            return NULL;
        }
    }
}
