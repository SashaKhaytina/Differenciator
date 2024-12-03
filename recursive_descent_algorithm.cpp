#include "recursive_descent_algorithm.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "tree_commands.h"
#include "math_commands.h"

// const char* const s = "2*(5+2)$";
extern int p = 0;

// Node* GetG(char* s);
// Node* GetN(char* s);
// Node* GetE(char* s);
// Node* GetT(char* s);
// Node* GetP(char* s);

// int main()
// {
//     printf("%d -answer\n", GetG());
// }

Node* GetG(char* s, VariableArr* all_var)
{
    Node* val = GetE(s, all_var);
    // printf("%d", val);
    if (s[p] != '$')
    {
        printf("ERROR\n");
        exit(0);
    }
    return val;

}

Node* GetN(char* s) 
{
    int val = 0;
    while (('0' <= s[p]) && (s[p] <= '9'))
    {
        val = val * 10 + s[p] - '0';
        p++;
    }
    return create_new_node(NUMBER, val, NULL, NULL);
}

Node* GetE(char* s, VariableArr* all_var) 
{
    Node* val = GetT(s, all_var);
    while ((s[p] == '+') || (s[p] == '-'))
    {
        char op = s[p];
        p++;
        Node* val2 = GetT(s, all_var);

        // if (op == '+') val += val2;
        // else val -= val2;
        if (op == '+') val = create_new_node(OPERATION, ADD, val, val2);
        else           val = create_new_node(OPERATION, SUB, val, val2);
    }

    return val;
}


Node* GetT(char* s, VariableArr* all_var) 
{
    Node* val = GetP(s, all_var);
    while ((s[p] == '*') || (s[p] == '/'))
    {
        char op = s[p];
        p++;
        Node* val2 = GetP(s, all_var);

        // if (op == '*') val *= val2;
        // else val /= val2;
        // cycle here (op_arr)
        if (op == '*') val = create_new_node(OPERATION, MUL, val, val2);
        else           val = create_new_node(OPERATION, DIV, val, val2);

    }

    return val;
}

Node* GetP(char* s, VariableArr* all_var) 
{
    if (s[p] == '(')
    {
        p++;
        Node* val = GetE(s, all_var);
        if (s[p] != ')') {printf("ERROR 2\n"); exit(0);}
        p++;
        return val;
    }
    else if (isalpha(s[p]) != 0) return GetV(s, all_var);
    else                         return GetN(s);
}


Node* GetV(char* s, VariableArr* all_var) 
{
    // while (isalpha(s[p]) != 0)
    // {
    //     val = val * 10 + s[p] - '0';
    //     p++;
    // }

    char val = s[p];
    int num_var = 0;





    bool know_this_var = false;
    for (size_t i = 0; i < all_var->size; i++)
    {
        // printf("%c - arr_file_tree[*point_current_letter]\n", arr_file_tree[*point_current_letter]);
        // printf("%c - all_var->arr[i].name\n", all_var->arr[i].name);

        if (all_var->arr[i].name == s[p]) { know_this_var = true; num_var = all_var->arr[i].num; printf("FIND!\n"); break; }
    }

    // printf("%d - know_this_var\n", know_this_var);

    if (!know_this_var)
    {
        all_var->size++;
        all_var->arr[all_var->size - 1] = {(int)all_var->size, s[p]};
        num_var = all_var->size; // Говорим, что ЭТОТ номер ее
    }












    p++;
    return create_new_node(VARIABLE, num_var, NULL, NULL);

}