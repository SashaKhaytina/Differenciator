#include "calculate_trivial.h"


static bool is_null(Node* current_node);
static bool is_one (Node* current_node);
static void add_node_value(Node* node, Node* node2);


static bool is_null(Node* current_node)
{
    if (current_node == NULL) return false;

    if ((current_node->type == NUMBER) && (current_node->value.num == 0)) return true;
    return false;
}

static void add_node_value(Node* node, Node* node2)
{
    if      (node->type == NUMBER)    node->value.num     = node2->value.num;
    else if (node->type == VARIABLE)  node->value.var_num = node2->value.var_num;
    else if (node->type == OPERATION) node->value.op_num  = node2->value.op_num;
}


static bool is_one(Node* current_node)
{
    if (current_node == NULL) return false;


    if ((current_node->type == NUMBER) && (current_node->value.num == 1)) return true;
    return false;
}




void calculate_triv_add(Node* node, int* diference)
{
    assert(node);


    if (is_null(node->left)) 
    {
        (*diference)++;
        // *node = {(node->right)->type, (node->right)->value, (node->right)->left, (node->right)->right}; 
        node->type = (node->right)->type;

        // if      (node->type == NUMBER)    node->value.num     = (node->right)->value.num;
        // else if (node->type == VARIABLE)  node->value.var_num = (node->right)->value.var_num;
        // else if (node->type == OPERATION) node->value.op_num  = (node->right)->value.op_num;
        add_node_value(node, node->right);

        node->left  = (node->right)->left;
        node->right = (node->right)->right;

        return;
    }

    else if (is_null(node->right)) 
    {
        (*diference)++;
        // *node = {(node->left)->type, (node->left)->value, (node->left)->left, (node->left)->right};
        node->type  = (node->left)->type;
        add_node_value(node, node->left);
        node->left  = (node->left)->left;
        node->right = (node->left)->right;
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
        // *node = {NUMBER, 0, NULL, NULL};/////
        node->type      = NUMBER;
        node->value.num = 0;
        node->left      = NULL;
        node->right     = NULL;
        return;
    }

    else if (is_one(node->left)) 
    {
        (*diference)++;
        // *node = {(node->right)->type, (node->right)->value, (node->right)->left, (node->right)->right};
        node->type  = (node->right)->type;
        add_node_value(node, node->right);
        node->left  = (node->right)->left;
        node->right = (node->right)->right;
        return;
    }

    else if (is_one(node->right)) 
    {
        (*diference)++;
        // *node = {(node->left)->type, (node->left)->value, (node->left)->left, (node->left)->right};
        node->type  = (node->left)->type;
        add_node_value(node, node->left);
        node->left  = (node->left)->left;
        node->right = (node->left)->right;
        return;
    }
}


void calculate_triv_div(Node* node, int* diference)
{
    assert(node);


    if (is_one(node->right)) 
    {
        (*diference)++;
        // *node = {(node->left)->type, (node->left)->value, (node->left)->left, (node->left)->right};
        node->type  = (node->left)->type;
        add_node_value(node, node->left);
        node->left  = (node->left)->left;
        node->right = (node->left)->right;
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
        // *node = {NUMBER, 1, NULL, NULL};
        node->type      = NUMBER;
        node->value.num = 1;
        node->left      = NULL;
        node->right     = NULL;
        return;
    }
}