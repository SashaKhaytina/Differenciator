#include "tex_dump.h"

#include "math_commands.h"




void fprint_node(FILE* file, Node* node, VariableArr* all_var)
{
    switch (node->type)
    {
    case NUMBER:
    {
        fprintf(file, "%d", node->value);
        break;
    }

    case VARIABLE:
    {
        // Is there a need check here?
        for (int i = 0; i < all_var->size; i++) 
        {
            if (all_var->arr[i].num == node->value) { fprintf(file, "%s", all_var->arr[i].name); break; }
        }
        break;
    }

    case OPERATION:
    {
        int len_struct_arr = (int) (sizeof(op_arr) / sizeof(Operation));
        for (int i = 0; i < len_struct_arr; i++)
        {
            if (op_arr[i].num == node->value) { fprintf(file, "%s", op_arr[i].name); break; }
        }
        break;
    }
    
    default:
    {
        printf("ERROR type node\n");
        break;
    }
    }
}




void fprint_tree(FILE* file, Node* node, VariableArr* all_var)
{   
    if (node == NULL) return;

    if (node->type != OPERATION) fprint_node(file, node, all_var);
    else
    {
        fprintf(file,"(");
        fprint_tree(file, node->left, all_var);

        
        fprint_node(file, node, all_var);
        
        fprint_tree(file, node->right, all_var);
        fprintf(file,")");
    }
}










// void tex_dump(Node* node, Node* node_diff, ForDump* st_dump, VariableArr* all_var)
// {
//     st_dump->dumps_counter++;
//     int number_of_dump = st_dump->dumps_counter;

//     char sample[] = "tex_files/tex00.tex";
//     sample[14] = (char) ('0' + ((int) number_of_dump / 10));
//     sample[15] = (char) ('0' + ((int) number_of_dump % 10));

//     FILE* file = fopen(sample, "w");

//     fprintf(file, "Посчитаем производную от $");
//     fprint_tree(file, node, all_var);
//     fprintf(file, "$:\n\n");

//     fprintf(file, "$ d(");
//     fprint_tree(file, node, all_var);
//     fprintf(file, "$) = ");
//     fprint_tree(file, node_diff, all_var);
//     fprintf(file, "$:\n\n");


//     graph_create_point(node, file, all_var);

//     graph_create_edge(node, file);

//     fprintf(file, "}\n");

//     fclose(file);

//     create_png(number_of_dump);

// }
