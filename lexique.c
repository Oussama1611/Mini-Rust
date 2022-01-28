#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexique.h"
#include "erreurs.h"
#include "syntax.h"
#define SIZE_TOKENS 19


FILE* file;
Symbol* symbol;
TSym_Cour Sym_Cour;
int COUNTER = 0;

int arriere;
const char* mots_cles[SIZE_TOKENS][2] = { {"fn","FN_TOKEN"}, {"const","CONST_TOKEN"},{"let","LET_TOKEN"}, 
{"mut","MUT_TOKEN"},{"if","IF_TOKEN"},{"else","ELSE_TOKEN"},{"false","FALSE_TOKEN"},{"true","TRUE_TOKEN"},
{"while","WHILE_TOKEN"},{"loop","LOOP_TOKEN"},{"for","FOR_TOKEN"},{"bool","BOOL_TOKEN"},{"in","IN_TOKEN"},{"continue","CONTI_TOKEN"},
{"break","BREAK_TOKEN"},{"struct","STRUCT_TOKEN"},{"String","STRING_TYPE_TOKEN"},{"println","PRINT_TOKEN"},{"return","RETURN_TOKEN"}};

const int codes[SIZE_TOKENS] = {FN_TOKEN, CONST_TOKEN, LET_TOKEN, MUT_TOKEN, IF_TOKEN, ELSE_TOKEN, FALSE_TOKEN, TRUE_TOKEN, WHILE_TOKEN, LOOP_TOKEN, FOR_TOKEN, BOOL_TOKEN, IN_TOKEN, CONTI_TOKEN, BREAK_TOKEN, STRUCT_TOKEN, STRING_TYPE_TOKEN, PRINT_TOKEN, RETURN_TOKEN};

void symbol_suivant(){
    if(arriere){
        symbol->c = arriere;           
        arriere = 0;
        return;
    } else {
        symbol->c = fgetc(file);
        if(symbol->c == '\n') COUNTER++;
    }
}

void revenir_arriere(){
    arriere = symbol->c;
}
char* to_string(){
    char* str = calloc(2, sizeof(char));
    str[0] = symbol->c;
    str[1] = '\0';
    return str;
}
void assign_nom_token(char* mot){
    int i;
    for(i=0;i<sizeof(codes)/sizeof(int);i++){
        if(!strcmp(mot,mots_cles[i][0])){
            Sym_Cour.CODE=codes[i];
            strcpy(Sym_Cour.NOM, mots_cles[i][1]);
            break;
        } else {
            Sym_Cour.CODE=ID_TOKEN;
            strcpy(Sym_Cour.NOM, mot); // avant les regles semantiques on a: strcpy(Sym_Cour.NOM, "ID_TOKEN");
        }
    
    } 
    //printf("%s\t",mot);
}

void lire_mot(){
    char *mot = calloc(2, sizeof(char));
    char* nombre = calloc(2, sizeof(char));
    char* C = calloc(2, sizeof(char));
    C[0] = symbol->c;
    C[1] = '\0';
    if(symbol->c=='i' || symbol->c=='u'){
        symbol_suivant();
        if(isdigit(symbol->c)){
            while (isdigit(symbol->c))
            {
                strcat(nombre, to_string());
                symbol_suivant();
            }
            revenir_arriere();
            Sym_Cour.CODE=NUM_TYPE_TOKEN;
            strcpy(Sym_Cour.NOM,"NUM_TYPE_TOKEN");
            //printf("%c%s\t",C[0],nombre);
            free(nombre);
            return;

        } else  strcat(mot,C);
 
    }   
    while((isalnum(symbol->c) || symbol->c =='_')){
        strcat(mot, to_string());
        symbol_suivant();
    }
    revenir_arriere();
    assign_nom_token(mot);
    free(mot);
    free(C);
}
void sauter_espace(){
    while(symbol->c==' ' || symbol->c=='\t' || symbol->c=='\n' || symbol->c=='\r') {
        symbol_suivant();
    }
}

void lire_nombre(){
    char* nombre = calloc(2, sizeof(char));
    while (isdigit(symbol->c))
    {
        strcat(nombre, to_string());
        symbol_suivant();
    }
    revenir_arriere();
    Sym_Cour.CODE=NUM_TOKEN;
    strcpy(Sym_Cour.NOM,"NUM_TOKEN");
    Sym_Cour.val=atoi(nombre); //  on ajoute la valeur de nombre apres consideration des regles semantiques
    //printf("%s\t",nombre); 
    free(nombre);
   
}

void sauter_commentaire(){
    if(symbol->c=='/'){
        symbol_suivant();
        if(symbol->c=='/'){
            while(symbol->c!='\n'){
                symbol_suivant();
            }
            symbol_suivant();
        }
    }
    sauter_espace();
    if(symbol->c =='/') sauter_commentaire();
}


void lire_special(){

    if (symbol->c==')'){
        Sym_Cour.CODE = PF_TOKEN;
        strcpy(Sym_Cour.NOM,"PF_TOKEN");
        //printf(")\t");
        return;
    }
    if(symbol->c=='('){
        symbol_suivant();
        if (symbol->c==')'){
            Sym_Cour.CODE = UNIT_TOKEN;
            strcpy(Sym_Cour.NOM,"UNIT_TOKEN");
            //printf("()\t");
            return;
        } else {
            revenir_arriere();
            Sym_Cour.CODE = PO_TOKEN;
            strcpy(Sym_Cour.NOM,"PO_TOKEN");
            //printf("(\t");
            return;
        }
    }
    if(symbol->c=='{'){
        Sym_Cour.CODE = ACCOLO_TOKEN;
        strcpy(Sym_Cour.NOM,"ACCOLO_TOKEN");
        //printf("{\t");
        return;
    }
    if (symbol->c=='}'){
        Sym_Cour.CODE = ACCOLF_TOKEN;
        strcpy(Sym_Cour.NOM,"ACCOLF_TOKEN");
        //printf("}\t");
        return;
    } 
    if(symbol->c==';'){
        Sym_Cour.CODE = PV_TOKEN;
        strcpy(Sym_Cour.NOM,"PV_TOKEN");
        //printf(";\t");
        return;
    }
    if(symbol->c=='['){
        Sym_Cour.CODE = CROCHO_TOKEN;
        strcpy(Sym_Cour.NOM,"CROCHO_TOKEN");
        //printf("[\t");
        return;
    }
    if(symbol->c==']'){
        Sym_Cour.CODE = CROCHF_TOKEN;
        strcpy(Sym_Cour.NOM,"CROCHF_TOKEN");
        //printf("]\t");
        return;
    }

    if(symbol->c=='+'){
        Sym_Cour.CODE = PLUS_TOKEN;
        strcpy(Sym_Cour.NOM,"PLUS_TOKEN");
        //printf("+\t");
        return;
    }
    if(symbol->c=='*'){
        Sym_Cour.CODE = MULT_TOKEN;
        strcpy(Sym_Cour.NOM,"MULTI_TOKEN");
        //printf("*\t");
        return;
    }
    if(symbol->c=='/'){ 
        Sym_Cour.CODE = DIV_TOKEN;
        strcpy(Sym_Cour.NOM,"DIV_TOKEN");
        //printf("/\t");
        return;
    }
    if(symbol->c==','){
        Sym_Cour.CODE = VIR_TOKEN;
        strcpy(Sym_Cour.NOM,"VIR_TOKEN");
        //printf(",\t");
        return;
    }
    if(symbol->c =='"'){
        Sym_Cour.CODE = GUILL_TOKEN;
        strcpy(Sym_Cour.NOM,"GUILL_TOKEN");
        //printf("\"\t");
        return;
    }
    if(symbol->c=='%'){
        Sym_Cour.CODE = REST_TOKEN;
        strcpy(Sym_Cour.NOM,"REST_TOKEN");
        //printf("%c\t",symbol->c);
        return;
    }
    if (symbol->c=='.'){
        symbol_suivant();
        if(symbol->c=='.'){
            Sym_Cour.CODE = RANG_TOKEN;
            strcpy(Sym_Cour.NOM,"RANG_TOKEN");
            //printf("..\t");
            return;
        } else {
            revenir_arriere();
            Sym_Cour.CODE = PT_TOKEN;
            strcpy(Sym_Cour.NOM,"PT_TOKEN");
            //printf(".\t");
            return;
        }
    }
    if(symbol->c==':'){
        Sym_Cour.CODE = COL_TOKEN;
        strcpy(Sym_Cour.NOM,"COL_TOKEN");
        //printf(":\t");
        return;
    }

    if (symbol->c=='<'){
        symbol_suivant();
        if(symbol->c=='='){
            Sym_Cour.CODE = INFEG_TOKEN;
            strcpy(Sym_Cour.NOM,"INFEG_TOKEN");
            //printf("<=\t");
            return;
        }
        else{
            revenir_arriere();
            Sym_Cour.CODE=INF_TOKEN;
            strcpy(Sym_Cour.NOM,"INF_TOKEN");
            //printf("<\t");
            return;
        }
        
    }
    if(symbol->c=='-'){
        symbol_suivant();
        if(symbol->c=='>'){
            Sym_Cour.CODE = RETURN_TYPE_TOKEN;
            strcpy(Sym_Cour.NOM,"RETURN_TYPE_TOKEN");
            //printf("->\t");
            return;
        } else {
            revenir_arriere();
            Sym_Cour.CODE = MOINS_TOKEN;
            strcpy(Sym_Cour.NOM,"MOINS_TOKEN");
            //printf("-\t");
            return;
        }
    }
    if (symbol->c=='='){
        symbol_suivant();
        if(symbol->c=='='){
            Sym_Cour.CODE = COMP_TOKEN;
            strcpy(Sym_Cour.NOM,"COMP_TOKEN");
            //printf("==\t");
            return;
        } else {
            revenir_arriere();
            Sym_Cour.CODE = AFF_TOKEN;
            strcpy(Sym_Cour.NOM,"AFF_TOKEN");
            //printf("=\t");
            return;
        }
    }  
    if (symbol->c=='!'){
        symbol_suivant();
        if(symbol->c=='='){
            Sym_Cour.CODE = DIFF_TOKEN;
            strcpy(Sym_Cour.NOM,"DIFF_TOKEN");
            //printf("!=\t");
            return;
        } else {
            revenir_arriere();
            Sym_Cour.CODE = NON_TOKEN;
            strcpy(Sym_Cour.NOM,"NON_TOKEN");
            //printf("!\t");
            return;
        }
    }    
    if (symbol->c=='>'){
        symbol_suivant();
        if(symbol->c=='='){
            Sym_Cour.CODE = SUPEG_TOKEN;
            strcpy(Sym_Cour.NOM,"SUPEG_TOKEN");
            //printf(">=\t");
            return;
        }
        else{
            revenir_arriere();
            Sym_Cour.CODE=SUP_TOKEN;
            strcpy(Sym_Cour.NOM,"SUP_TOKEN");
            //printf(">\t");
            return;
        }
        
    }

}

void print_token(){ // fonction pour afficher les tokens 
    //printf("%s\n",Sym_Cour.NOM);
}

void token_suivant(){

    sauter_espace(); 
    sauter_commentaire();
    sauter_espace();
    if(ispunct(symbol->c)){
        lire_special();
        //print_token();
        return;
    }
    if(isdigit(symbol->c)){
        lire_nombre();
        //print_token();
        return;  
    }
    if(isalpha(symbol->c)){
        lire_mot();
        //print_token();
        return;
    }
    if (symbol->c==EOF)
    {
        Sym_Cour.CODE=END_TOKEN;
        strcpy(Sym_Cour.NOM,"END_TOKEN");
        //print_token();
        return;
    }
}    

