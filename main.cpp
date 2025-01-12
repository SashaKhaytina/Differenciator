#include "differenciator_h.h"
#include "math/math_commands.h"
#include "dump/for_dump.h"
#include "tree_s__commands/tree_commands.h"
#include "get_math_task/input_tree.h"
#include "get_math_task/token.h"
#include "math/differentiation.h"
#include "tree_s__commands/free.h"
#include "dump/tex_dump.h"


int main()
{
    FILE* file = fopen(FILE_MATH, "r");
    Tree tree = {};

    ForDump dumps_counter = 0; // why do you need this type

    VariableArr all_var = {};

    Token token = {};


    get_tree(file, &tree, &all_var, &token);

    dump(tree.root, &dumps_counter, &all_var);



    // SOLVE_____________________________________________________________________________________________________________

    solve(tree.root);
    dump(tree.root, &dumps_counter, &all_var);


    // // DIFF______________________________________________________________________________________________________________

    FILE* file_tex = fopen(FILE_TEX, "w");
    tex_dump_title(file_tex);

    Tree diff_tree = {};

    diff_tree.root = diff(tree.root, file_tex, &all_var);

    solve(diff_tree.root);

    dump(diff_tree.root, &dumps_counter, &all_var);
    tex_dump_end_title(file_tex);


    fclose(file);
    fclose(file_tex);

    free_tree(tree.root);
    free_tokens(&token);

    free_tree(diff_tree.root); diff_tree.root = NULL;
    free_val(&all_var);
}

