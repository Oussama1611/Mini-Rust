#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexique.h"
#include "erreurs.h"
#include "syntax.h"

extern FILE* file;
extern Symbol* symbol;
extern TSym_Cour Sym_Cour;


int main(int argc, char* argv[]){

    
    //Il faut spécifier le nom du fichier a analyser : 
    if(argc != 2){
        printf("Le fichier a analyser n'etait pas donne!\n");
        exit(EXIT_FAILURE);
    }

    //Initialiser le symbol :
    symbol = calloc(1, sizeof(char));

    //Ouverture de fichier : 
    file = fopen(argv[1], "r");

    if(file ==NULL){
        printf("On ne peut pas ouvrir le fichier ");
        exit(0);
    }
    symbol_suivant();
    token_suivant();
    while (Sym_Cour.CODE != END_TOKEN)
    {
        DECL(); // commencement d'analyse syntaxique : DECL = DECLARATION GLOBALE
    }

    printf("\n \033[0;32m Your code is compiled succefully !\n\n");

    
    return 0;
}