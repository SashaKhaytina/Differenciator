#include "calculate_trivial.h"


static bool is_null(Node* current_node);
static bool is_one (Node* current_node);


static bool is_null(Node* current_node)
{
    if ((current_node->type == NUMBER) && (current_node->value == 0)) return true;
    return false;
}


static bool is_one(Node* current_node)
{
    if ((current_node->type == NUMBER) && (current_node->value == 1)) return true;
    return false;
}




void calculate_triv_add(Node* node, int* diference)
{
    assert(node);


    if (is_null(node->left)) 
    {
        (*diference)++;
        *node = {(node->right)->type, (node->right)->value, (node->right)->left, (node->right)->right};
        return;
    }

    if (is_null(node->right)) 
    {
        (*diference)++;
        *node = {(node->left)->type, (node->left)->value, (node->left)->left, (node->left)->right};
        return;
    }
}


void calculate_triv_sub(Node* node, int* diference)
{
    assert(node);


    return; // no trivial
}


void calculate_triv_mul(Node* node, int* diference)
{
    assert(node);
    printf("IN calculate_triv_mul\n");


    if (is_null(node->left) || is_null(node->right)) 
    {
        (*diference)++;
        *node = {NUMBER, 0, NULL, NULL};
        return;
    }

    if (is_one(node->left)) 
    {
        (*diference)++;
        *node = {(node->right)->type, (node->right)->value, (node->right)->left, (node->right)->right};
        return;
    }

    if (is_one(node->right)) 
    {
        (*diference)++;
        *node = {(node->left)->type, (node->left)->value, (node->left)->left, (node->left)->right};
        return;
    }
}


void calculate_triv_div(Node* node, int* diference)
{
    assert(node);


    if (is_one(node->right)) 
    {
        (*diference)++;
        *node = {(node->left)->type, (node->left)->value, (node->left)->left, (node->left)->right};
        return;
    }
}


void calculate_triv_sin(Node* node, int* diference)
{
    return;
}


void calculate_triv_cos(Node* node, int* diference)
{
    return;
}



void calculate_triv_log(Node* node, int* diference)
{
    return;
}


void calculate_triv_pow(Node* node, int* diference)
{
    if (is_null(node->left)) 
    {
        (*diference)++;
        *node = {NUMBER, 1, NULL, NULL};
        return;
    }
}