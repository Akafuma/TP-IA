#ifndef UTIL_H_DEFINED
#define UTIL_H_DEFINED

#include <stdio.h>
#include <stdlib.h>

#define VARIABLE_MAX 50
#define VALEUR_MAX 100

typedef struct CSP
{
    int var_length;
    int val_length;
    
    int num_val_assigne[VARIABLE_MAX]; // Stocke le numéro de la valeur assigné à la variable, soit var l'indice d'une variable assigné
											//La valeur de var = csp.valeurs[csp.num_val_assigne[var]];

	int variables[VARIABLE_MAX];
	int valeurs[VALEUR_MAX];
	int domaines[VARIABLE_MAX][VALEUR_MAX];
	int **contraintes[VARIABLE_MAX][VARIABLE_MAX];
} CSP;

int appartient_domaine(int var, int val, int domaines[VARIABLE_MAX][VALEUR_MAX]);

void write_csp(const CSP * csp, const char * nom_fichier);

int assignation_enfreint_contraintes(int var_curr, int val_curr, CSP *csp);

#endif //UTIL_H_DEFINED
