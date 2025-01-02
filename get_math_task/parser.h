#ifndef PARSER
#define PARSER

#include "../differenciator_h.h"
#include "token.h"


Node* GetGraph             (Token* token, VariableArr* all_var);
Node* GetNumber            (Token* token);
Node* GetE_Addition        (Token* token, VariableArr* all_var);
Node* GetT_Multiplication  (Token* token, VariableArr* all_var);
Node* GetP_Pow             (Token* token, VariableArr* all_var);
Node* Get_Heaviest_Oper   (Token* token, VariableArr* all_var);
Node* GetF_Function_one_arg(Token* token, VariableArr* all_var);
Node* GetVariable          (Token* token, VariableArr* all_var);


#endif
