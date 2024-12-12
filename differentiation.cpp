#include "differentiation.h"
#include "math_commands.h"

#include "tree_commands.h"
#include "tex_dump.h"



// in main: dif_tree.root = diff(tree.root) // tree - old, dif_tree - new
// Node* diff(Node* current_node, ForTexDump* st_tex_dump, VariableArr* all_var)
Node* diff(Node* current_node, FILE* file, VariableArr* all_var)
{
    // st_tex_dump->tex_dumps_counter++;
    // int number_of_dump = st_tex_dump->tex_dumps_counter;

    // char sample[] = "tex_files/tex00.tex";
    // sample[13] = (char) ('0' + ((int) number_of_dump / 10));
    // sample[14] = (char) ('0' + ((int) number_of_dump % 10));

    // FILE* tex_file = fopen(sample, "w");

    // fprintf(tex_file, "$d( ");
    // fprint_tree(tex_file, current_node, all_var);
    // fprintf(tex_file, ") = ");
    // tex_dump_start(current_node, st_tex_dump, all_var);
    // tex_dump_start(current_node, file, all_var);





    if (current_node == NULL) return NULL;

    switch (current_node->type)
    {
        case NUMBER:
        {
            fprintf(file, "$ d(");
            fprint_tree(file, current_node, all_var);
            fprintf(file, ") = 0$\n\n");
            
            Node* diff_node = create_new_node(NUMBER, 0, NULL, NULL);
            // tex_dump(current_node, diff_node, tex_file, all_var);
            // tex_dump_finish(diff_node, file, all_var);
            // st_tex_dump->tex_dumps_counter++;
            // int number_of_dump = st_tex_dump->tex_dumps_counter;

            // char sample[] = "tex_files/tex00.tex";
            // sample[13] = (char) ('0' + ((int) number_of_dump / 10));
            // sample[14] = (char) ('0' + ((int) number_of_dump % 10));

            // tex_file = fopen(sample, "w");


            // fprint_tree(tex_file, diff_node, all_var);
            // fprintf(tex_file, "$\\\\");
            // return create_new_node(NUMBER, 0, NULL, NULL);
            return diff_node;
            break; // this not use
        }
        
        case VARIABLE:
        {
            fprintf(file, "$ d(");
            fprint_tree(file, current_node, all_var);
            fprintf(file, ") = 1$\n\n");
            Node* diff_node = create_new_node(NUMBER, 1, NULL, NULL);
            // tex_dump(current_node, diff_node, tex_file, all_var);
            // tex_dump_finish(diff_node, file, all_var);

            // st_tex_dump->tex_dumps_counter++;
            // int number_of_dump = st_tex_dump->tex_dumps_counter;

            // char sample[] = "tex_files/tex00.tex";
            // sample[13] = (char) ('0' + ((int) number_of_dump / 10));
            // sample[14] = (char) ('0' + ((int) number_of_dump % 10));

            // tex_file = fopen(sample, "w");

            // fprint_tree(tex_file, diff_node, all_var);
            // fprintf(tex_file, "$\\\\");

            return diff_node;
            break; // this not use
        }

        case OPERATION:
        {
            // return create_new_node(NUMBER, 1, NULL, NULL);
            // return FUNC_FOR_THIS_OP;
            Node* diff_node = NULL;
            
            int len_struct_arr = (int) (sizeof(op_arr) / sizeof(Operation)); // TODO: why int, why not const
            for (int i = 0; i < len_struct_arr; i++)
            {
                if (op_arr[i].num == current_node->value) {diff_node = op_arr[i].diff_form(current_node, file, all_var); break;}//return op_arr[i].diff_form(current_node, file, all_var);
            }
            // tex_dump(current_node, diff_node, tex_file, all_var);
            // tex_dump_finish(diff_node, file, all_var);

            // st_tex_dump->tex_dumps_counter++;
            // int number_of_dump = st_tex_dump->tex_dumps_counter;

            // char sample[] = "tex_files/tex00.tex";
            // sample[13] = (char) ('0' + ((int) number_of_dump / 10));
            // sample[14] = (char) ('0' + ((int) number_of_dump % 10));

            // tex_file = fopen(sample, "w");

            // fprint_tree(tex_file, diff_node, all_var);
            // fprintf(tex_file, "$\\\\");
            return diff_node;
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