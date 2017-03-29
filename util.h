#ifndef UTIL_H_DEFINED
#define UTIL_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VARIABLE_MAX 25
#define VALEUR_MAX 25

typedef struct CSP
{
    int var_length;
    int val_length;

    int num_val_assigne[VARIABLE_MAX];  // Stocke le numéro de la valeur assigné à la variable, soit var l'indice d'une variable assigné
                                        //La valeur de var = csp.valeurs[csp.num_val_assigne[var]];
    int var_assigne[VARIABLE_MAX]; //Tableau de bool pour savoir si la var est assigné
    //inutile pour l'instant

	int variables[VARIABLE_MAX];
	int valeurs[VALEUR_MAX];
	int domaines[VARIABLE_MAX][VALEUR_MAX];
	int **contraintes[VARIABLE_MAX][VARIABLE_MAX];
} CSP;

int appartient_domaine(int num_var, int num_val, int domaine[VARIABLE_MAX][VALEUR_MAX]);

int domaine_var_vide(int domaine[VARIABLE_MAX][VALEUR_MAX], int num_var);

int domaines_vide(int domaines[VARIABLE_MAX][VALEUR_MAX], int var_curr, CSP * csp);

void domaines_copie(int target[VARIABLE_MAX][VALEUR_MAX], int source[VARIABLE_MAX][VALEUR_MAX], CSP * csp);

void reinitialiser_domaine(int domaine[VARIABLE_MAX][VALEUR_MAX], int num_var, int modele[VARIABLE_MAX][VALEUR_MAX]);

int assignation_enfreint_contraintes(int var_curr, int val_curr, CSP *csp);
//int assignation_enfreint_contraintes_bj(int var_curr, int val_curr, CSP *csp);
//int assignation_enfreint_contraintes_bjj(int var_curr, int val_curr, CSP *csp);


//FORWARDCHECKING FUNC

void filtrer_domaine(CSP * csp, int domaine[VARIABLE_MAX][VALEUR_MAX], int var_assigne, int val_assigne);

#endif //UTIL_H_DEFINED
