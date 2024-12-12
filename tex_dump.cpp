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
        if (node->value == ADD) fprintf(file, " \\cdot ");
        else
        {
            int len_struct_arr = (int) (sizeof(op_arr) / sizeof(Operation));
            for (int i = 0; i < len_struct_arr; i++)
            {
                if (op_arr[i].num == node->value) { fprintf(file, "%s", op_arr[i].name); break; }
            }
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
        if (node->value == DIV)
        {
            fprintf(file,"\\frac{");
            fprint_tree(file, node->left, all_var);
            fprintf(file,"}{");
            fprint_tree(file, node->right, all_var);
            fprintf(file,"}");
        }
        // fprintf(file,"(");
        bool is_lower_op =  (node->value == ADD || node->value == SUB);

        if (is_lower_op) fprintf(file,"(");


        fprint_tree(file, node->left, all_var);

        
        fprint_node(file, node, all_var);

        bool is_func =  (node->value == SIN || node->value == COS || node->value == LOG);

        if (is_func) fprintf(file,"(");
        
        fprint_tree(file, node->right, all_var);

        if (is_func || is_lower_op) fprintf(file,")");
        // fprintf(file,")");
    }
}




void tex_dump(Node* node, Node* node_diff, FILE* tex_file, VariableArr* all_var)
{
    fprintf(tex_file, "$d( ");
    fprint_tree(tex_file, node, all_var);
    fprintf(tex_file, ") = ");
    fprint_tree(tex_file, node_diff, all_var);
    fprintf(tex_file, "$\\\\\n\n");

}


void tex_dump_start(Node* node,FILE* tex_file, VariableArr* all_var)
{
    // st_tex_dump->tex_dumps_counter++;
    // int number_of_dump = st_tex_dump->tex_dumps_counter;

    // char sample[] = "tex_files/tex00.tex";
    // sample[13] = (char) ('0' + ((int) number_of_dump / 10));
    // sample[14] = (char) ('0' + ((int) number_of_dump % 10));

    // FILE* tex_file = fopen(sample, "w");

    fprintf(tex_file, "$\\\\d( ");
    fprint_tree(tex_file, node, all_var);
    fprintf(tex_file, ") = $");
}


// void tex_dump_finish(Node* node_diff, ForTexDump* st_tex_dump, VariableArr* all_var)
void tex_dump_finish(Node* node_diff, FILE* tex_file, VariableArr* all_var)
{
    // st_tex_dump->tex_dumps_counter++;
    // int number_of_dump = st_tex_dump->tex_dumps_counter;

    // char sample[] = "tex_files/tex00.tex";
    // sample[13] = (char) ('0' + ((int) number_of_dump / 10));
    // sample[14] = (char) ('0' + ((int) number_of_dump % 10));

    // FILE* tex_file = fopen(sample, "w");

    fprintf(tex_file, "$= ");
    fprint_tree(tex_file, node_diff, all_var);
    fprintf(tex_file, "$\\\\");
}








void tex_dump_end(FILE* file, Node* current_node, Node* diff_node, VariableArr* all_var)
{
    fprintf(file, "Получилось:\n\n");
    fprintf(file, "$ d(");
    fprint_tree(file, current_node, all_var);
    fprintf(file, ") = ");
    fprint_tree(file, diff_node, all_var);
    fprintf(file, "$\n\n");
}



void tex_dump_add(FILE* file, Node* current_node, VariableArr* all_var)
{
    fprintf(file, "$ d(");
    fprint_tree(file, current_node, all_var);
    fprintf(file, ") = d(");
    fprint_tree(file, current_node->left, all_var);
    fprintf(file, ") + d(");
    fprint_tree(file, current_node->right, all_var);
    fprintf(file, ")$\n\n");
    fprintf(file, "Посчитаем составные части:\n\n");
}


void tex_dump_sub(FILE* file, Node* current_node, VariableArr* all_var)
{
    fprintf(file, "$ d(");
    fprint_tree(file, current_node, all_var);
    fprintf(file, ") = d(");
    fprint_tree(file, current_node->left, all_var);
    fprintf(file, ") - d(");
    fprint_tree(file, current_node->right, all_var);
    fprintf(file, ")$\n\n");
    fprintf(file, "Посчитаем составные части:\n\n");
}


void tex_dump_mul(FILE* file, Node* current_node, VariableArr* all_var)
{
    fprintf(file, "$ d(");
    fprint_tree(file, current_node, all_var);
    fprintf(file, ") = d(");
    fprint_tree(file, current_node->left, all_var);
    fprintf(file, ") \\cdot (");
    fprint_tree(file, current_node->right, all_var);
    fprintf(file, ") + d(");
    fprint_tree(file, current_node->right, all_var);
    fprintf(file, ") \\cdot (");
    fprint_tree(file, current_node->left, all_var);
    fprintf(file, ")$\n\n");
    fprintf(file, "Посчитаем составные части:\n\n");
}

void tex_dump_div(FILE* file, Node* current_node, VariableArr* all_var)
{
    fprintf(file, "$ d(");
    fprint_tree(file, current_node, all_var);
    fprintf(file, ") = \\frac{d(");
    fprint_tree(file, current_node->left, all_var);
    fprintf(file, ") \\cdot (");
    fprint_tree(file, current_node->right, all_var);
    fprintf(file, ") + d(");
    fprint_tree(file, current_node->right, all_var);
    fprintf(file, ") \\cdot (");
    fprint_tree(file, current_node->left, all_var);
    fprintf(file, ")}{$\n\n");
    fprint_tree(file, current_node->right, all_var);
    fprintf(file, "}$\n\n");
    fprintf(file, "Посчитаем составные части:\n\n");
}


void tex_dump_sin(FILE* file, Node* current_node, VariableArr* all_var)
{
    fprintf(file, "$ d(");
    fprint_tree(file, current_node, all_var);
    fprintf(file, ") = cos(");
    fprint_tree(file, current_node->right, all_var);
    fprintf(file, ") \\cdot d(");
    fprint_tree(file, current_node->right, all_var);
    fprintf(file, ")$\n\n");
    fprintf(file, "Посчитаем составные части:\n\n");
}

void tex_dump_cos(FILE* file, Node* current_node, VariableArr* all_var)
{
    fprintf(file, "$ d(");
    fprint_tree(file, current_node, all_var);
    fprintf(file, ") = (-1) \\cdot sin(");
    fprint_tree(file, current_node->right, all_var);
    fprintf(file, ") \\cdot d(");
    fprint_tree(file, current_node->right, all_var);
    fprintf(file, ")$\n\n");
    fprintf(file, "Посчитаем составные части:\n\n");
}


void tex_dump_log(FILE* file, Node* current_node, VariableArr* all_var)
{
    fprintf(file, "$ d(");
    fprint_tree(file, current_node, all_var);
    fprintf(file, ") = \\frac{d(");
    fprint_tree(file, current_node->right, all_var);
    fprintf(file, "){");
    fprint_tree(file, current_node->right, all_var);
    fprintf(file, "}$\n\n");
    fprintf(file, "Посчитаем составные части:\n\n");
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
