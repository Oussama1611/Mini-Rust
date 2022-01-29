#ifndef _COMPILA_H
#define _COMPILA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>



typedef struct {
    char c;
} Symbol;


// L'énumération des classes lexicales : 
typedef enum {
    FN_TOKEN, RETURN_TOKEN, RETURN_TYPE_TOKEN, CONST_TOKEN, LET_TOKEN, MUT_TOKEN, IF_TOKEN, ELSE_TOKEN, WHILE_TOKEN,LOOP_TOKEN, FOR_TOKEN, 
    CONTI_TOKEN, BREAK_TOKEN, RANG_TOKEN,FALSE_TOKEN, TRUE_TOKEN, NON_TOKEN, PV_TOKEN, PT_TOKEN, COL_TOKEN, PLUS_TOKEN, MOINS_TOKEN, STRUCT_TOKEN,
    MULT_TOKEN, DIV_TOKEN, REST_TOKEN, OR_TOKEN, AND_TOKEN, VIR_TOKEN, AFF_TOKEN, INF_TOKEN, INFEG_TOKEN, SUP_TOKEN, SUPEG_TOKEN, PRINT_TOKEN, GUILL_TOKEN,
    DIFF_TOKEN, COMP_TOKEN, PO_TOKEN, PF_TOKEN, ACCOLO_TOKEN, ACCOLF_TOKEN, CROCHO_TOKEN,IN_TOKEN, CROCHF_TOKEN, FIN_TOKEN, BOOL_TOKEN, ERREUR_TOKEN, NUM_TOKEN, STRING_TYPE_TOKEN, NUM_TYPE_TOKEN, UNIT_TOKEN, ID_TOKEN, 
    END_TOKEN,
} CODES_LEX;

// type du symbole courant
typedef struct { 
    CODES_LEX CODE; 
    char NOM[20]; 
    int val;
} TSym_Cour;

// counteur des lignes 
// int COUNTER;

//Les prototypes des fonctions : 

void symbol_suivant();
void revenir_arriere();
char* to_string();
void assign_nom_token(char* mot);
void lire_mot();
void sauter_espace();
void lire_nombre();
void sauter_commentaire();
void lire_special();
void print_token();
void token_suivant();

#endif