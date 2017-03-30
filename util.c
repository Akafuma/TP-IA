#include "util.h"

int appartient_domaine(int num_var, int num_val, int domaine[VARIABLE_MAX][VALEUR_MAX])
{
	return domaine[num_var][num_val];
}

int domaine_var_vide(int domaine[VARIABLE_MAX][VALEUR_MAX], int num_var)
{
    for(int i = 0; i < VALEUR_MAX; i++)
        if(domaine[num_var][i] == 1)
            return 0;
    return 1;
}

int domaines_vide(int domaines[VARIABLE_MAX][VALEUR_MAX], int var_curr, CSP * csp)
{
    for(int var = var_curr + 1; var < csp->var_length; var++)
    {
        int s = 0;
        for(int val = 0; val < csp->val_length; val++)
        {
            if(domaines[var][val] == 1)
            {
                s = 1;
                break;
            }
        }
        if(s == 0)
            return 1;
    }
    return 0;
}

void domaines_copie(int target[VARIABLE_MAX][VALEUR_MAX], int source[VARIABLE_MAX][VALEUR_MAX], CSP * csp)
{
    memcpy(target, source, (sizeof(int) * VARIABLE_MAX * VALEUR_MAX));
}

void reinitialiser_domaine(int domaine[VARIABLE_MAX][VALEUR_MAX], int num_var, int modele[VARIABLE_MAX][VALEUR_MAX])
{
    for(int i = 0; i < VALEUR_MAX; i++)
        domaine[num_var][i] = modele[num_var][i];
}
