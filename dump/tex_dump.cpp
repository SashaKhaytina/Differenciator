#include "tex_dump.h"

#include "../math/math_commands.h"



void fprint_node(FILE* file, Node* node, VariableArr* all_var)
{
    switch (node->type)
    {
    case NUMBER:
    {
        fprintf(file, "%lg", node->value.num);
        break;
    }

    case VARIABLE:
    {
        for (size_t i = 0; i < all_var->size; i++) 
        {
            if (all_var->arr[i].num == node->value.var_num) { fprintf(file, "%s", all_var->arr[i].name); break; }
        }
        break;
    }

    case OPERATION:
    {
        if (node->value.op_num == MUL) fprintf(file, " \\cdot ");
        else
        {
            for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
            {
                if (op_arr[i].num == node->value.op_num) { fprintf(file, "%s", op_arr[i].name); break; }
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
        if (node->value.op_num == DIV)
        {
            fprintf(file,"\\frac{");
            fprint_tree(file, node->left, all_var);
            fprintf(file,"}{");
            fprint_tree(file, node->right, all_var);
            fprintf(file,"}");
        }
        else
        {
            bool is_lower_op =  (node->value.op_num == ADD || node->value.op_num == SUB);
            bool is_pow =  (node->value.op_num == POW);
            bool is_func =  (node->value.op_num == SIN || node->value.op_num == COS || node->value.op_num == LN);
            if (is_lower_op || is_pow) fprintf(file, "(");

            fprint_tree(file, node->left, all_var);
            
            if (is_pow) fprintf(file, ")");

            
            fprint_node(file, node, all_var);


            if (is_func) fprintf(file, "(");
            if (is_pow)  fprintf(file, "{");
            

            fprint_tree(file, node->right, all_var);

            if (is_pow)  fprintf(file, "}");
            if (is_func || is_lower_op) fprintf(file, ")");
        }
    }
}




void tex_dump_start(FILE* file, Node* current_node, VariableArr* all_var)
{
    fprintf(file, "$\\\\d( ");
    fprint_tree(file, current_node, all_var);
    fprintf(file, ") = $");
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


void tex_dump_num(FILE* file, Node* current_node, VariableArr* all_var)
{
    fprintf(file, "$ d(");
    fprint_tree(file, current_node, all_var);
    fprintf(file, ") = 0$\n\n");
}


void tex_dump_var(FILE* file, Node* current_node, VariableArr* all_var)
{
    fprintf(file, "$ d(");
    fprint_tree(file, current_node, all_var);
    fprintf(file, ") = 1$\n\n");
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
    fprintf(file, ")}{");
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


void tex_dump_ln(FILE* file, Node* current_node, VariableArr* all_var)
{
    fprintf(file, "$ d(");
    fprint_tree(file, current_node, all_var);
    fprintf(file, ") = \\frac{d(");
    fprint_tree(file, current_node->right, all_var);
    fprintf(file, ")}{");
    fprint_tree(file, current_node->right, all_var);
    fprintf(file, "}$\n\n");
    fprintf(file, "Посчитаем составные части:\n\n");
}


void tex_dump_pow(FILE* file, Node* current_node, VariableArr* all_var)
{
    fprintf(file, "$ d(");
    fprint_tree(file, current_node, all_var);
    fprintf(file, ") = ");
    fprint_tree(file, current_node, all_var);
    fprintf(file, " \\cdot d(ln(");
    fprint_tree(file, current_node->left, all_var);
    fprintf(file, ") \\cdot (");
    fprint_tree(file, current_node->right, all_var);
    fprintf(file, "))$\n\n");
    fprintf(file, "Посчитаем составные части:\n\n");
}


