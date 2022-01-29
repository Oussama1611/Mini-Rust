
#ifndef _SEMANTIQUE_H_
#define _SEMANTIQUE_H_

#define MAX_IDFS_NBRE 40
typedef enum {
    TINSTR, // ce type est specialelement pour distinguer les IDs lors des instructions
    TMUT, // type MUTABLE : let mut a = 1;
    TLET, // type LET : let a = 0;
    TCONST, // type const let a : i32 = 6;
    TFONC, // type FN : fn fonction(){...}
    TSTRUCT, // type STRUCT : struct qwerty{...}
    TARG, // type argument des fonctions 
} TSYM;


typedef struct {
    char NOM[20];
    TSYM TIDF ;
}T_TAB_IDF;



// T_TAB_IDF  T_IDFS[MAX_IDFS_NBRE];

int idf_existe();
void ajouter_idf(TSYM TIDF);
void mettre_a_jour_idf();
void mettre_a_jour_nbre();

#endif