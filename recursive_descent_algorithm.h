#ifndef REC_DES_ALG
#define REC_DES_ALG

#include "differenciator_h.h"
#include "token.h"

// Node* GetG(char* s, VariableArr* all_var);
// Node* GetN(char* s);
// Node* GetE(char* s, VariableArr* all_var);
// Node* GetT(char* s, VariableArr* all_var);
// Node* GetP(char* s, VariableArr* all_var);
// Node* GetV(char* s, VariableArr* all_var);
Node* GetG(Token* token, VariableArr* all_var);
Node* GetN(Token* token);
Node* GetE(Token* token, VariableArr* all_var);
Node* GetT(Token* token, VariableArr* all_var);
Node* GetP(Token* token, VariableArr* all_var);
Node* GetV(Token* token, VariableArr* all_var);
#endif