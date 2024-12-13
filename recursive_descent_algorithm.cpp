#include "recursive_descent_algorithm.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "tree_commands.h"
#include "math_commands.h"




void print_node_now(Node* cur_node, VariableArr* all_var)
{
    if (cur_node->type == NUMBER) printf("%d\n", cur_node->value.num);
    if (cur_node->type == VARIABLE) printf("%s\n", all_var->arr[cur_node->value.var_num - 1].name);
    if (cur_node->type == OPERATION) printf("%s\n", op_arr[cur_node->value.op_num].name);
    // printf("TOKEN[%d] (Node) = {%d - type, %d - value}\n", i, token->array[i].type, token->array[i].value);
}



Node* GetG(Token* token, VariableArr* all_var)
{
    assert(token);
    assert(all_var);


    Node* val = GetE(token, all_var);

    bool operation = (token->array[token->current_ind].type == OPERATION);
    if (!operation || token->array[token->current_ind].value.op_num != DOLL) // if node->type not DEFAULT
    {
        printf("ERROR\n");
        exit(0);
    }
    return val;

}


Node* GetN(Token* token) 
{
    assert(token);


    printf("IN N\n");
    if (token->array[token->current_ind].type == NUMBER) 
    {
        token->current_ind++; 
        return &token->array[token->current_ind - 1];
    }
    printf("ERROR SYNTAX. want num in %d token\n", token->current_ind); // position will be better!
    return NULL;
}


Node* GetE(Token* token, VariableArr* all_var) 
{
    assert(token);
    assert(all_var);


    printf("IN E\n");
    Node* val = GetT(token, all_var);

    bool operation = (token->array[token->current_ind].type == OPERATION);
    while (operation && ((token->array[token->current_ind].value.op_num == ADD) || (token->array[token->current_ind].value.op_num == SUB)))
    {
        Node* op_tok = &token->array[token->current_ind];
        token->current_ind++;

        Node* val2 = GetT(token, all_var);
        operation = (token->array[token->current_ind].type == OPERATION);

        op_tok->left = val;
        op_tok->right = val2;
        val = op_tok;
    }

    return val;
}


Node* GetT(Token* token, VariableArr* all_var) 
{
    assert(token);
    assert(all_var);


    printf("IN T\n");

    Node* val = GetP(token, all_var);

    bool operation = (token->array[token->current_ind].type == OPERATION);
    while (operation && ((token->array[token->current_ind].value.op_num == MUL) || (token->array[token->current_ind].value.op_num == DIV)))
    {
        Node* op_tok = &token->array[token->current_ind];

        token->current_ind++;

        Node* val2 = GetP(token, all_var);
        operation = (token->array[token->current_ind].type == OPERATION);

        op_tok->left = val;
        op_tok->right = val2;
        val = op_tok;

    }

    return val;
}














// Node* GetPow(Token* token, VariableArr* all_var) 
// {
//     assert(token);
//     assert(all_var);


//     printf("IN TPow\n");
    
//     Node* val = GetP(token, all_var);

//     bool operation = (token->array[token->current_ind].type == OPERATION);
//     while (operation && ((token->array[token->current_ind].value == MUL) || (token->array[token->current_ind].value == DIV)))
//     {
//         Node* op_tok = &token->array[token->current_ind];

//         token->current_ind++;

//         Node* val2 = GetP(token, all_var);
//         operation = (token->array[token->current_ind].type == OPERATION);

//         op_tok->left = val;
//         op_tok->right = val2;
//         val = op_tok;

//     }

//     return val;
// }




































Node* GetP(Token* token, VariableArr* all_var) 
{
    assert(token);
    assert(all_var);


    printf("IN P\n");

    bool operation = (token->array[token->current_ind].type == OPERATION);
    if (operation)
    {
        if (token->array[token->current_ind].value.op_num == OPEN_SKOB) // (
        {
            token->current_ind++;
            Node* val = GetE(token, all_var);
            
            operation = (token->array[token->current_ind].type == OPERATION);
            if (operation && (token->array[token->current_ind].value.op_num != CLOSE_SKOB)) printf("ERROR SYNTAX. Want ')'\n"); 

            token->current_ind++;
            //________________________________IS POW?_________________________________________
            // return val;





            operation = (token->array[token->current_ind].type == OPERATION);
            if (operation && (token->array[token->current_ind].value.op_num == POW))
            {
                Node* op_tok = &token->array[token->current_ind];
                token->current_ind++;

                // operation = (token->array[token->current_ind].type == OPERATION);
                // if (operation && (token->array[token->current_ind].value != OPEN_SKOB)) printf("ERROR SYNTAX. Want '('\n"); 
                // token->current_ind++;
                // Node* val2 =  GetE(token, all_var);

                // operation = (token->array[token->current_ind].type == OPERATION);
                // if (operation && (token->array[token->current_ind].value != CLOSE_SKOB)) printf("ERROR SYNTAX. Want ')'\n"); 
                // token->current_ind++;
                Node* val2 =  GetN(token); // вместо верхнего

                op_tok->left  = val;
                op_tok->right = val2;

                return op_tok;
            }
            













            return val;

        }
        else
        {
            Node* val = GetF(token, all_var);
            if (val != NULL) return val;
        }
    }
    
    else if (token->array[token->current_ind].type == VARIABLE) return GetV(token, all_var); // тут что-то не то. Логика странная
    else                                                        return GetN(token);
}


Node* GetF(Token* token, VariableArr* all_var) 
{
    assert(token);
    assert(all_var);


    printf("IN F\n");


    if ((token->array[token->current_ind].value.op_num == SIN) || (token->array[token->current_ind].value.op_num == COS) || (token->array[token->current_ind].value.op_num == LOG)) // степень сюда нельзя!!!!!!
    {
        Node* op_tok = &token->array[token->current_ind];

        token->current_ind++;


        bool operation = (token->array[token->current_ind].type == OPERATION);
        if (operation && (token->array[token->current_ind].value.op_num != OPEN_SKOB)) {printf("ERROR SYNTAX. Want '('\n");}
        token->current_ind++;

        Node* val = GetE(token, all_var); // Inside "function"

        if (operation && (token->array[token->current_ind].value.op_num != CLOSE_SKOB)) {printf("ERROR SYNTAX. Want ')'\n");}
        token->current_ind++;


        op_tok->left = NULL; 
        op_tok->right = val;

        return op_tok;

    }

    return NULL;
}



Node* GetV(Token* token, VariableArr* all_var) 
{
    assert(token);
    assert(all_var);


    printf("IN V\n");
    if (token->array[token->current_ind].type == VARIABLE) {token->current_ind++; return &token->array[token->current_ind - 1];}
    printf("ERROR SYNTAX. Want var\n");
    return NULL; 
}
































































// // const char* const s = "2*(5+2)$";
// extern int p = 0;

// // Node* GetG(char* s);
// // Node* GetN(char* s);
// // Node* GetE(char* s);
// // Node* GetT(char* s);
// // Node* GetP(char* s);

// // int main()
// // {
// //     printf("%d -answer\n", GetG());
// // }

// Node* GetG(char* s, VariableArr* all_var)
// {
//     Node* val = GetE(s, all_var);
//     // printf("%d", val);
//     if (s[p] != '$') // if node->type not DEFAULT
//     {
//         printf("ERROR\n");
//         exit(0);
//     }
//     return val;

// }

// Node* GetN(char* s) 
// {
//     int val = 0;
//     while (('0' <= s[p]) && (s[p] <= '9'))
//     {
//         val = val * 10 + s[p] - '0';
//         p++;
//     }
//     return create_new_node(NUMBER, val, NULL, NULL);
// }

// Node* GetE(char* s, VariableArr* all_var) 
// {
//     Node* val = GetT(s, all_var);
//     while ((s[p] == '+') || (s[p] == '-'))
//     {
//         char op = s[p];
//         p++;
//         Node* val2 = GetT(s, all_var);

//         // if (op == '+') val += val2;
//         // else val -= val2;
//         if (op == '+') val = create_new_node(OPERATION, ADD, val, val2);
//         else           val = create_new_node(OPERATION, SUB, val, val2);
//     }

//     return val;
// }


// Node* GetT(char* s, VariableArr* all_var) 
// {
//     Node* val = GetP(s, all_var);
//     while ((s[p] == '*') || (s[p] == '/'))
//     {
//         char op = s[p];
//         p++;
//         Node* val2 = GetP(s, all_var);

//         // if (op == '*') val *= val2;
//         // else val /= val2;
//         // cycle here (op_arr)
//         if (op == '*') val = create_new_node(OPERATION, MUL, val, val2);
//         else           val = create_new_node(OPERATION, DIV, val, val2);

//     }

//     return val;
// }

// Node* GetP(char* s, VariableArr* all_var) 
// {
//     if (s[p] == '(')
//     {
//         p++;
//         Node* val = GetE(s, all_var);
//         if (s[p] != ')') {printf("ERROR 2\n"); exit(0);} // TODO: wtf
//         p++;
//         return val;
//     }
//     else if (isalpha(s[p]) != 0) return GetV(s, all_var);
//     else                         return GetN(s);
// }


// Node* GetV(char* s, VariableArr* all_var) 
// {
//     // // while (isalpha(s[p]) != 0)
//     // // {
//     // //     val = val * 10 + s[p] - '0';
//     // //     p++;
//     // // }

//     // char val = s[p];
//     // int num_var = 0;

//     // // TODO: CREATE NEW FUNCTIONS (find_variable, insert_new_variable)
//     // bool know_this_var = false;
//     // for (size_t i = 0; i < all_var->size; i++)
//     // {
//     //     // printf("%c - arr_file_tree[*point_current_letter]\n", arr_file_tree[*point_current_letter]);
//     //     // printf("%c - all_var->arr[i].name\n", all_var->arr[i].name);

//     //     if (all_var->arr[i].name == s[p]) 
//     //     { 
//     //         know_this_var = true; 
//     //         num_var = all_var->arr[i].num; 
//     //         printf("FIND!\n"); 
//     //         break;  // 
//     //     }
//     // }

//     // // printf("%d - know_this_var\n", know_this_var);

//     // if (!know_this_var)
//     // {
//     //     all_var->size++;
//     //     all_var->arr[all_var->size - 1] = {(int)all_var->size, s[p]};
//     //     num_var = all_var->size; // Говорим, что ЭТОТ номер ее
//     // }

//     // p++;
//     // return create_new_node(VARIABLE, num_var, NULL, NULL);

// }