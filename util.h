#ifndef UTIL_H_DEFINED
#define UTIL_H_DEFINED

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

#endif //UTIL_H_DEFINED
