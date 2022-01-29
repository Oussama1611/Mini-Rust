#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexique.h"
#include "erreurs.h"
#include "syntax.h"



extern TSym_Cour Sym_Cour;
extern int COUNTER;
extern T_TAB_IDF  T_IDFS[MAX_IDFS_NBRE];

void Test_Symbole(CODES_LEX cl, ERRORS_LEX er)
{   
    if (Sym_Cour.CODE == cl)
    {   
        symbol_suivant();
        token_suivant(); // c'est ainsi pour passer au token suivant
    }
    else
        Erreur(er,COUNTER);  
}

void Test_Symbole_ID(CODES_LEX cl,TSYM TIDF, ERRORS_LEX er) // FONCTION POUR L'ANALYSE SEMANTIQUE TEST DES ID_TOKEN
{   
    int i = idf_existe();
    if(TIDF == TINSTR ){
        if(TIDF == TINSTR && i == -1) // SI LE ID EST DE TYPE INSTR ET QU'IL NE FIGURE PAS DANS LA TABLE DES SYMBOLES
            Erreur(UNDECL_ID_ERROR,COUNTER); // UTILISER UNE VARIABLE SANS DECLARATION   
        else{
            switch(T_IDFS[i].TIDF){
                case TMUT: // ON FAIT RIEN SI L'IDENTIFIFANT EST DE TYPE MUTABLE
                    break;
                case TLET:
                    Erreur(UNCHANGED_CONST_ERREUR,COUNTER);  
                    break;  
                case TCONST:
                    Erreur(UNCHANGED_CONST_ERREUR,COUNTER);
                    break;    
                default:
                    break;
            }
        }    
    }
    else if(TIDF == TARG && i!=-1) // SI LE ID EST DE TYPE ARG ET ELLE FIGURE DANS LA TABLE DES SYMBOLES
        Erreur(ILLEGAL_ARG,COUNTER);  // UTILISER UNE VARIABLE DEJA DECLARE COMME ARGUMENT DANS UNE FONCTION 
    else if (idf_existe() != -1){
        Erreur(REDECL_ID_ERROR,COUNTER); // REDECLARATION ERREUR : IDF_EXISTE + TYPE ID <> TYPE INSTRUCTION
    } else {
        ajouter_idf(TIDF); // AJOUTER L'ID S'IL N'EXISTE PAS DANS LA TABLES DES SYMBOLES
    } 
    if (Sym_Cour.CODE == cl )
    {   
        symbol_suivant();
        token_suivant(); 
    }
    else
        Erreur(er, COUNTER);  
}


void DECL(){
    if(Sym_Cour.CODE == STRUCT_TOKEN) DECL_STRUCT(); else DECL_FON();
    return;
}

void DECL_STRUCT(){
    Test_Symbole(STRUCT_TOKEN,STRUCT_ERROR);
    Test_Symbole_ID(ID_TOKEN,TSTRUCT,ID_ERROR);
    Test_Symbole(ACCOLO_TOKEN,ACCOLF_ERROR);
    while(Sym_Cour.CODE != ACCOLF_TOKEN){
        Test_Symbole(ID_TOKEN, ID_ERROR);
        Test_Symbole(COL_TOKEN, COL_ERROR);
        if(Sym_Cour.CODE == NUM_TYPE_TOKEN)
            Test_Symbole(NUM_TYPE_TOKEN, NUM_TYPE_ERROR);
        else Test_Symbole(STRING_TYPE_TOKEN,TYPE_ERROR);   
        Test_Symbole(VIR_TOKEN,VIR_ERROR);
    }
    Test_Symbole(ACCOLF_TOKEN,ACCOLF_ERROR);
}

void DECL_FON(){
    Test_Symbole(FN_TOKEN,FN_ERROR);
    Test_Symbole_ID(ID_TOKEN,TFONC,ID_ERROR);
    if(Sym_Cour.CODE == UNIT_TOKEN) Test_Symbole(UNIT_TOKEN, UNIT_ERROR);
    else {
        Test_Symbole(PO_TOKEN,PO_ERROR);
        while(Sym_Cour.CODE != PF_TOKEN){
            if(Sym_Cour.CODE == VIR_TOKEN) Test_Symbole(VIR_TOKEN,VIR_ERROR);
            ARG();
        }
        Test_Symbole(PF_TOKEN,PF_ERROR);
    }    
    if(Sym_Cour.CODE == RETURN_TYPE_TOKEN){
        Test_Symbole(RETURN_TYPE_TOKEN,RETURN_TYPE_ERROR);
        TYPE();
    }    
    BLOC(1,0);
}
void TYPE(){
    switch (Sym_Cour.CODE)
    {
    case NUM_TYPE_TOKEN:
        Test_Symbole(NUM_TYPE_TOKEN,NUM_TYPE_ERROR);
        break;
    case BOOL_TOKEN:
        Test_Symbole(BOOL_TOKEN,BOOL_ERROR);
        break;
    case UNIT_TOKEN:
        Test_Symbole(UNIT_TOKEN,UNIT_ERROR);
        break;
    case STRING_TYPE_TOKEN:
        Test_Symbole(STRING_TYPE_TOKEN, STRING_TYPE_ERROR);
        break;    
    default:
        Erreur(TYPE_ERROR,COUNTER);
    }

}

void ARG(){
    Test_Symbole_ID(ID_TOKEN,TARG,ID_ERROR);
    Test_Symbole(COL_TOKEN,COL_ERROR);
    TYPE();
}

void BLOC(int fun_indicator, int loops_indicator){
    Test_Symbole(ACCOLO_TOKEN,ACCOLO_ERROR);
    while(Sym_Cour.CODE != ACCOLF_TOKEN){        
        if(Sym_Cour.CODE == FN_TOKEN ) 
        {if(fun_indicator) DECL_FON(); else Erreur(DECL_ERROR,COUNTER);}
        else INSTR(loops_indicator);
    }
    Test_Symbole(ACCOLF_TOKEN,ACCOLF_ERROR);
}



void INSTR(int loops_indicator){
    switch (Sym_Cour.CODE)
    {
    case ID_TOKEN:
        Test_Symbole_ID(ID_TOKEN,TINSTR,ID_ERROR);
        Test_Symbole(AFF_TOKEN,AFF_ERROR);
        EXPR();
        if(Sym_Cour.CODE ==PV_TOKEN) Test_Symbole(PV_TOKEN,PV_ERROR);  else {EXPR(); break;}
        break;
    case LET_TOKEN:
        Test_Symbole(LET_TOKEN,LET_ERROR);
        if(Sym_Cour.CODE == MUT_TOKEN) {Test_Symbole(MUT_TOKEN,MUT_ERROR); Test_Symbole_ID(ID_TOKEN,TMUT,ID_ERROR);}
        else Test_Symbole_ID(ID_TOKEN,TLET,ID_ERROR);
        if(Sym_Cour.CODE == COL_TOKEN){
            if(Sym_Cour.CODE == NUM_TYPE_TOKEN)
                Test_Symbole(NUM_TYPE_TOKEN, NUM_TYPE_ERROR);
            else Test_Symbole(STRING_TYPE_TOKEN,TYPE_ERROR);   
        }
        if(Sym_Cour.CODE == AFF_TOKEN) {Test_Symbole(AFF_TOKEN,AFF_ERROR); EXPR();}
        Test_Symbole(PV_TOKEN,PV_ERROR);
        
        break;
    case CONST_TOKEN:
        Test_Symbole(CONST_TOKEN, CONST_ERROR);
        Test_Symbole_ID(ID_TOKEN,TCONST,ID_ERROR);
        Test_Symbole(COL_TOKEN, COL_ERROR);
        if(Sym_Cour.CODE == NUM_TYPE_TOKEN)
            Test_Symbole(NUM_TYPE_TOKEN, NUM_TYPE_ERROR);
        else Test_Symbole(STRING_TYPE_TOKEN,TYPE_ERROR);    
        Test_Symbole(AFF_TOKEN,AFF_ERROR);
        EXPR();
        Test_Symbole(PV_TOKEN,PV_ERROR);
        break;
    case WHILE_TOKEN:
        WHILE();
        break;
    case LOOP_TOKEN:
        LOOP();
        break;
    case FOR_TOKEN:
        FOR();
        break;
    case IF_TOKEN:
        IF(loops_indicator);
        break;
    case CONTI_TOKEN :
       if(loops_indicator)
            {Test_Symbole(CONTI_TOKEN, CONTI_ERROR); Test_Symbole(PV_TOKEN, PV_ERROR);}
        else Erreur(CONTI_ERROR, COUNTER); 
        break;
    case BREAK_TOKEN:
        if(loops_indicator)
            {Test_Symbole(BREAK_TOKEN, BREAK_ERROR);  Test_Symbole(PV_TOKEN, PV_ERROR);}
        else Erreur(BREAK_ERROR, COUNTER);    
        break; 
    case RETURN_TOKEN:
        Test_Symbole(RETURN_TOKEN, RETURN_ERROR);  
        EXPR();
        Test_Symbole(PV_TOKEN,PV_ERROR);
        break;    
    case PRINT_TOKEN:
        PRINT();
        break;             
    default:
        Erreur(INSTR_ERROR, COUNTER);
    }
}
void IF(int indic){
    Test_Symbole(IF_TOKEN,IF_ERROR);
    EXPR();
    BLOC(0,indic);
    if(Sym_Cour.CODE == ELSE_TOKEN) {
        Test_Symbole(ELSE_TOKEN,ELSE_ERROR);
        if(Sym_Cour.CODE == IF_TOKEN) IF(indic); else BLOC(0,indic);
    }

}
void WHILE(){
    Test_Symbole(WHILE_TOKEN, WHILE_ERROR);
    EXPR();
    BLOC(0,1);

}
void LOOP(){
    Test_Symbole(LOOP_TOKEN, LOOP_ERROR);
    BLOC(0,1);
}
void FOR(){
    Test_Symbole(FOR_TOKEN,FOR_ERROR);
    Test_Symbole_ID(ID_TOKEN,TINSTR,ID_ERROR);
    Test_Symbole(PO_TOKEN,PO_ERROR);
    Test_Symbole(NUM_TOKEN,NUM_ERROR);
    Test_Symbole(RANG_TOKEN,RANG_ERROR);
    Test_Symbole(NUM_TOKEN,NUM_ERROR);
    Test_Symbole(PF_TOKEN,PF_ERROR);
    BLOC(0,1);
    
}
void EXPR(){
    switch (Sym_Cour.CODE)
    {
    case NUM_TOKEN:
        Test_Symbole(NUM_TOKEN,NUM_ERROR);
        if(IS_OPR()) {OPR(); EXPR();}
        break;
    case ID_TOKEN:
        Test_Symbole_ID(ID_TOKEN,TINSTR,ID_ERROR);
        if(Sym_Cour.CODE == PO_TOKEN){
            Test_Symbole(PO_TOKEN, PO_ERROR); 
            ARG_VERI();
            Test_Symbole(PF_TOKEN, PF_ERROR);
            break;
        }
        if(Sym_Cour.CODE == UNIT_TOKEN) {Test_Symbole(UNIT_TOKEN,UNIT_ERROR); break;}
        if(IS_OPR()) {OPR(); EXPR();}
        break;
    case UNIT_TOKEN :
        Test_Symbole(UNIT_TOKEN, UNIT_ERROR);
        break;    
    case TRUE_TOKEN:
        Test_Symbole(TRUE_TOKEN,TRUE_ERROR);
        if(IS_OPR()) {OPR(); EXPR();}
        break;
    case FALSE_TOKEN:
        Test_Symbole(FALSE_TOKEN,FALSE_ERROR);
        if(IS_OPR()) {OPR(); EXPR();}
        break;
    case PO_TOKEN:
        Test_Symbole(PO_TOKEN,PO_ERROR);
        EXPR();
        Test_Symbole(PF_TOKEN,PF_ERROR);
        break;
    case MOINS_TOKEN:
        NEG();
        EXPR();
        break;
    case NON_TOKEN:
        NEG();
        EXPR();
        break;        
    default:
        if(Sym_Cour.CODE == PV_TOKEN) return;
        Erreur(EXPR_ERROR, COUNTER);
    }   
}

void ARG_VERI() {
    EXPR();
    if(Sym_Cour.CODE == VIR_TOKEN) {Test_Symbole(VIR_TOKEN, VIR_ERROR); ARG_VERI();}
    else return;
}

void OPR(){
    switch (Sym_Cour.CODE)
    {
    case COMP_TOKEN:
        Test_Symbole(COMP_TOKEN,COMP_ERROR);
        break;
    case DIFF_TOKEN:
        Test_Symbole(DIFF_TOKEN,DIFF_ERROR);
        break;
    case INF_TOKEN:
        Test_Symbole(INF_TOKEN,INF_ERROR);
        break;
    case INFEG_TOKEN:
        Test_Symbole(INFEG_TOKEN,INFEG_ERROR);
        break;
    case SUP_TOKEN:
        Test_Symbole(SUP_TOKEN,SUP_ERROR);
        break;
    case SUPEG_TOKEN:
        Test_Symbole(SUPEG_TOKEN,SUPEG_ERROR);
        break;
    case PLUS_TOKEN:
        Test_Symbole(PLUS_TOKEN,PLUS_ERROR);
        break;
    case MOINS_TOKEN:
        Test_Symbole(MOINS_TOKEN,MOINS_ERROR);
        break;
    case MULT_TOKEN:
        Test_Symbole(MULT_TOKEN,MULT_ERROR);
        break;
    case DIV_TOKEN:
        Test_Symbole(DIV_TOKEN,DIV_ERROR);
        break;
    case REST_TOKEN:
        Test_Symbole(REST_TOKEN,REST_ERROR);
        break;
    case OR_TOKEN:
        Test_Symbole(OR_TOKEN,OR_ERROR);
        break;
    case AND_TOKEN:
        Test_Symbole(AND_TOKEN,AND_ERROR);
        break;
    case AFF_TOKEN:
        Test_Symbole(AFF_TOKEN,AFF_ERROR);
        break;
    default:
        break;
    }    
}

void PRINT(){
    Test_Symbole(PRINT_TOKEN,PRINT_ERROR);
    Test_Symbole(NON_TOKEN,NON_ERROR);
    Test_Symbole(PO_TOKEN,PO_ERROR);
    if(Sym_Cour.CODE == GUILL_TOKEN){
        Test_Symbole(GUILL_TOKEN,GUILL_ERROR);
        while (Sym_Cour.CODE != GUILL_TOKEN)
        {
            symbol_suivant();
            token_suivant(); 
        }
        Test_Symbole(GUILL_TOKEN,GUILL_ERROR);
    } else Test_Symbole_ID(ID_TOKEN,TINSTR,ID_ERROR);
    Test_Symbole(PF_TOKEN,PF_ERROR);
    Test_Symbole(PV_TOKEN,PV_ERROR);
}

void NEG(){
    if(Sym_Cour.CODE == MOINS_TOKEN) Test_Symbole(MOINS_TOKEN,MOINS_ERROR);
    if(Sym_Cour.CODE == NON_TOKEN) Test_Symbole(NON_TOKEN,NON_ERROR);
}

// fonction auxilaire pour le teste des operateurs 

int IS_OPR(){
    if(Sym_Cour.CODE == COMP_TOKEN || Sym_Cour.CODE == DIFF_TOKEN 
        || Sym_Cour.CODE == INF_TOKEN || Sym_Cour.CODE == INFEG_TOKEN || Sym_Cour.CODE == SUP_TOKEN || 
        Sym_Cour.CODE == SUPEG_TOKEN || Sym_Cour.CODE == PLUS_TOKEN || Sym_Cour.CODE == MOINS_TOKEN || 
        Sym_Cour.CODE == MULT_TOKEN || Sym_Cour.CODE == DIV_TOKEN || Sym_Cour.CODE == REST_TOKEN || 
        Sym_Cour.CODE == AND_TOKEN || Sym_Cour.CODE == OR_TOKEN || Sym_Cour.CODE == AFF_TOKEN ) 
        return 1; else return 0;
}


