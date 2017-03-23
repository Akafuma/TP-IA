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

	int variables[VARIABLE_MAX];
	int valeurs[VALEUR_MAX];
	int domaines[VARIABLE_MAX][VALEUR_MAX];
	int **contraintes[VARIABLE_MAX][VARIABLE_MAX];
} CSP;

int appartient_domaine(int var, int val, int domaines[VARIABLE_MAX][VALEUR_MAX]);

void write_csp(const CSP * csp, const char * nom_fichier);

#endif //UTIL_H_DEFINED
