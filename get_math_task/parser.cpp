#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../tree_s__commands/tree_commands.h"
#include "../math/math_commands.h"

// void print_node_now(Node* cur_node, VariableArr* all_var);




// (token->current_ind < token->size) - it is very sad. We can do operation '\n' like '$'. 
// And everywhere (token->current_ind < token->size)?


Node* GetGraph(Token* token, VariableArr* all_var)
{
    assert(token);
    assert(all_var);


    Node* val = GetE_Addition(token, all_var);

    // bool operation = (token->array[token->current_ind]->type == OPERATION);
    // if ((token->array[token->current_ind]->type != OPERATION) || token->array[token->current_ind]->value.op_num != DOLL) // if node->type not DEFAULT
    // {
    //     printf("ERROR\n");
    // }

    return val;

}


Node* GetNumber(Token* token) 
{
    assert(token);


    if (token->array[token->current_ind]->type == NUMBER) 
    {
        token->current_ind++; 
        return token->array[token->current_ind - 1];
    }
    printf("ERROR SYNTAX. want num in %ld token\n", token->current_ind); // position will be better!
    return NULL;
}


Node* GetE_Addition(Token* token, VariableArr* all_var) 
{
    assert(token);
    assert(all_var);


    Node* val = GetT_Multiplication(token, all_var);

    while ((token->current_ind < token->size) 
            &&
            ((token->array[token->current_ind]->type == OPERATION) && 
            ((token->array[token->current_ind]->value.op_num == ADD) || 
             (token->array[token->current_ind]->value.op_num == SUB))))
    {
        Node* op_tok = token->array[token->current_ind];
        token->current_ind++;

        Node* val2 = GetT_Multiplication(token, all_var);

        op_tok->left = val;
        op_tok->right = val2;
        val = op_tok;
    }

    return val;
}


Node* GetT_Multiplication(Token* token, VariableArr* all_var) 
{
    assert(token);
    assert(all_var);


    Node* val = GetP_Pow(token, all_var);

    while ((token->current_ind < token->size)                        
            &&
           ((token->array[token->current_ind]->type == OPERATION)  && 
          ((token->array[token->current_ind]->value.op_num == MUL) || 
           (token->array[token->current_ind]->value.op_num == DIV))))
    {
        Node* op_tok = token->array[token->current_ind];

        token->current_ind++;

        Node* val2 = GetP_Pow(token, all_var);

        op_tok->left = val;
        op_tok->right = val2;
        val = op_tok;

    }

    return val;
}




Node* GetP_Pow(Token* token, VariableArr* all_var)
{
    assert(token);
    assert(all_var); 


    Node* val = Get_Heaviest_Oper(token, all_var);

    while ((token->current_ind < token->size)                       
            &&
            token->array[token->current_ind]->type == OPERATION && 
            token->array[token->current_ind]->value.op_num == POW)
    {
        Node* op_tok = token->array[token->current_ind];

        token->current_ind++;

        Node* val2 = Get_Heaviest_Oper(token, all_var);
        
        
        op_tok->left = val;
        op_tok->right = val2;
        val = op_tok;           // A^B^C = (A^B)^C
    }

    return val;
}




Node* Get_Heaviest_Oper(Token* token, VariableArr* all_var)
{
    assert(token);
    assert(all_var); 


    if ((token->array[token->current_ind]->type == OPERATION))
    {
        if (token->array[token->current_ind]->value.op_num == OPEN_SKOB) 
        {
            token->current_ind++;
            Node* val = GetE_Addition(token, all_var);
            
            if ((token->array[token->current_ind]->type == OPERATION) && 
                (token->array[token->current_ind]->value.op_num != CLOSE_SKOB)) 
                printf("ERROR SYNTAX. Want ')'\n"); 

            token->current_ind++;


            return val;

        }
        else
        {
            Node* val = GetF_Function_one_arg(token, all_var);
            if (val != NULL) return val;
        }
    }
    
    else if (token->array[token->current_ind]->type == VARIABLE) return GetVariable(token, all_var);
    else                                                         return GetNumber(token);
    return NULL;
}


Node* GetF_Function_one_arg(Token* token, VariableArr* all_var) 
{
    assert(token);
    assert(all_var);


    if ((token->array[token->current_ind]->value.op_num == SIN) || 
        (token->array[token->current_ind]->value.op_num == COS) || 
        (token->array[token->current_ind]->value.op_num == LN))
    {

        Node* op_tok = token->array[token->current_ind];

        token->current_ind++;

        if ((token->array[token->current_ind]->type == OPERATION) && 
            (token->array[token->current_ind]->value.op_num != OPEN_SKOB)) 
            printf("ERROR SYNTAX. Want '('\n");
        token->current_ind++;

        Node* val = GetE_Addition(token, all_var); 

        if ((token->array[token->current_ind]->type == OPERATION) && 
            (token->array[token->current_ind]->value.op_num != CLOSE_SKOB)) 
            printf("ERROR SYNTAX. Want ')'\n");
        token->current_ind++;


        op_tok->left = NULL; 
        op_tok->right = val;

        return op_tok;

    }

    return NULL;
}


Node* GetVariable(Token* token, VariableArr* all_var) 
{
    assert(token);
    assert(all_var);


    if (token->array[token->current_ind]->type == VARIABLE) 
    {
        token->current_ind++; 
        return token->array[token->current_ind - 1];
    }
    printf("ERROR SYNTAX. Want var\n");
    return NULL; 
}



// void print_node_now(Node* cur_node, VariableArr* all_var)
// {
//     assert(cur_node);
//     if (cur_node->type == NUMBER) printf("%d\n", cur_node->value.num);
//     if (cur_node->type == VARIABLE) printf("%s\n", all_var->arr[cur_node->value.var_num - 1].name);
//     if (cur_node->type == OPERATION) printf("%s\n", op_arr[cur_node->value.op_num].name);
//     // printf("TOKEN[%d] (Node) = {%d - type, %d - value}\n", i, token->array[i].type, token->array[i].value);
// }
