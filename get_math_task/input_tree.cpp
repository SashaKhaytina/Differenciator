#include "input_tree.h"

#include "parser.h"
#include "token.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "../math/math_commands.h"
#include "../tree_s__commands/tree_commands.h"


static size_t size_file    (FILE* file);



static size_t size_file(FILE* file)
{
    size_t size = 0;

    fseek(file, 0, SEEK_END);
    size = (size_t) ftell(file);
    fseek(file, 0, SEEK_SET);

    return size;
}


void get_tree(FILE* file, Tree* tree, VariableArr* all_var)
{
    Token token = {};
    size_t len_text = size_file(file);

    char arr_file_tree[MAX_TOKEN_S_ARR_SIZE] = {};

    size_t count_symbol = fread(arr_file_tree, sizeof(char), len_text, file);
    if (count_symbol != len_text) printf("ERROR read file\n");

    init_token(&token, len_text);

    get_token(&token, arr_file_tree, all_var);

    tree->root = GetGraph(&token, all_var);
}


