#include "free.h"

#include <stdio.h>
#include <stdlib.h>

void free_tree(Node* node)
{
    assert(node);
    printf("%p - node, %p - node left, %p - node right\n", node, node->left, node->right);


    if (node->left  != NULL) { free_tree(node->left);  node->left  = NULL; }
    if (node->right != NULL) { free_tree(node->right); node->right = NULL; }
    printf("%p - node, %p - node left, %p - node right\n", node, node->left, node->right);
    free(node);    
}


void free_val(VariableArr* all_var)
{
    for (int i = 0; i < all_var->size; i++)
    {
        free(all_var->arr[i].name); all_var->arr[i].name = NULL;
    }
}


void free_tokens(Token* token)
{
    free(token->array); token->array = NULL;
}


void free_needless_tokens(Token* token)
{
    for (int i = 0; i < token->size; i++)
    {
        if (token->array[i]->type == OPERATION && (token->array[i]->value.op_num == OPEN_SKOB || token->array[i]->value.op_num == CLOSE_SKOB))
        {
            free((token->array[i])); token->array[i] = NULL;
        }
    }
}