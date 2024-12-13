#ifndef REC_DES_ALG
#define REC_DES_ALG

#include "../differenciator_h.h"
#include "token.h"

enum Status
{
    OK,
    ERROR
};

Node* GetG(Token* token, VariableArr* all_var);
Node* GetN(Token* token);
Node* GetE(Token* token, VariableArr* all_var);
Node* GetT(Token* token, VariableArr* all_var);
Node* GetP(Token* token, VariableArr* all_var);
Node* GetF(Token* token, VariableArr* all_var);
Node* GetV(Token* token, VariableArr* all_var);
#endif