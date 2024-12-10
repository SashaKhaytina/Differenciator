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




void calculate_triv_add(Node* node)
{
    assert(node);


    if (is_null(node->left)) 
    {
        *node = {(node->right)->type, (node->right)->value, (node->right)->left, (node->right)->right};
        return;
    }

    if (is_null(node->right)) 
    {
        *node = {(node->left)->type, (node->left)->value, (node->left)->left, (node->left)->right};
        return;
    }
}


void calculate_triv_sub(Node* node)
{
    assert(node);


    return; // no trivial
}


void calculate_triv_mul(Node* node)
{
    assert(node);
    printf("IN calculate_triv_mul\n");


    if (is_null(node->left) || is_null(node->right)) 
    {
        printf("AAAAAAAAAAa\n");
        *node = {NUMBER, 0, NULL, NULL};
        return;
    }

    if (is_one(node->left)) 
    {
        *node = {(node->right)->type, (node->right)->value, (node->right)->left, (node->right)->right};
        return;
    }

    if (is_one(node->right)) 
    {
        *node = {(node->left)->type, (node->left)->value, (node->left)->left, (node->left)->right};
        return;
    }
}


void calculate_triv_div(Node* node)
{
    assert(node);


    if (is_one(node->right)) 
    {
        *node = {(node->left)->type, (node->left)->value, (node->left)->left, (node->left)->right};
        return;
    }
}