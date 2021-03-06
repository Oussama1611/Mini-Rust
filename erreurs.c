#include <stdio.h>
#include <stdlib.h>
#include "erreurs.h"

char* erreurs[] = {
    "FN_ERROR", "RETURN_ERROR", "RETURN_TYPE_ERROR", "CONST_ERROR", "LET_ERROR", "MUT_ERROR", "IF_ERROR", "ELSE_ERROR", "WHILE_ERROR","LOOP_ERROR", "FOR_ERROR", 
    "CONTI_ERROR", "BREAK_ERROR", "RANG_ERROR","FALSE_ERROR", "TRUE_ERROR", "NON_ERROR", "PV_ERROR", "PT_ERROR", "COL_ERROR", "PLUS_ERROR", "MOINS_ERROR", "STRUCT_ERROR",
    "MULT_ERROR", "DIV_ERROR", "REST_ERROR", "OR_ERROR", "AND_ERROR", "VIR_ERROR", "AFF_ERROR", "INF_ERROR", "INFEG_ERROR", "SUP_ERROR", "SUPEG_ERROR", 
    "DIFF_ERROR", "COMP_ERROR", "PO_ERROR", "PF_ERROR", "ACCOLO_ERROR", "ACCOLF_ERROR", "CROCHO_ERROR", "CROCHF_ERROR", "FIN_ERROR", "BOOL_ERROR", "ERREUR_ERROR", "NUM_ERROR", "NUM_TYPE_ERROR", "STRING_TYPE_ERROR", "UNIT_ERROR","GUILL_ERROR", "ID_ERROR", 
    "END_ERROR",
    // complex ERRORs :
    "TYPE_ERROR", "INSTR_ERROR", "EXPR_ERROR","DECL_ERROR","PRINT_ERROR",
    // semantic errors :
    "REDECL_ID_ERROR", "UNDECL_ID_ERROR", "UNCHANGED_CONST_ERREUR", "ILLEGAL_ARG"
};




void Erreur(ERRORS_LEX er, int counter){
    if(er < 56)
        printf("\nErreur syntaxique :\033[0;31m %s \n\t Dans la ligne : %d\n\n",erreurs[er],counter+1);
    else 
        printf("\nErreur sémantique :\033[0;33m %s \n\t Dans la ligne : %d\n\n",erreurs[er],counter+1);
    exit(EXIT_FAILURE);
}