#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "semantique.h"
#include "erreurs.h"
#include "lexique.h"


extern TSym_Cour Sym_Cour;


int idf_existe(){
    int i;
    if(Sym_Cour.CODE == ID_TOKEN){
        for(i=0;i<MAX_IDFS_NBRE;i++) {
            if(!strcmp(Sym_Cour.NOM,T_IDFS[i].NOM))
                return i;
        }
        return -1;
    } return -1;
}

void ajouter_idf(TSYM TIDF){
    int i;
    for(i=0;i<MAX_IDFS_NBRE;i++) {
        if(!strcmp(T_IDFS[i].NOM,"")) {
            strcpy(T_IDFS[i].NOM, Sym_Cour.NOM);
            T_IDFS[i].TIDF = TIDF;
            return; 
        }    
    } printf("TABLE DES IDS EST REMPLIE !!\n");
}








