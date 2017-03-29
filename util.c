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

/*
 * Renvoi 1 si l'assignation de la variable num var_curr à l'assignation numero val_curr enfreint au moins une contrainte
 * Renvoi 0 sinon
 */
int assignation_enfreint_contraintes(int var_curr, int val_curr, CSP *csp)
{
	for(int var_deja_assigne = 0; var_deja_assigne < var_curr; var_deja_assigne++) //Ici on assigne dans l'ordre, donc on a assigné toutes la variables précedant celle courante
	{
	    //On boucle sur les lignes, car elles representent les variables déjà assigné
		//int ** tuples = csp->contraintes[var_curr][var_deja_assigne]; //mauvais sens
		int ** tuples = csp->contraintes[var_deja_assigne][var_curr];

		if(tuples != NULL) // Il y a contraintes
		{
			//if(tuples[val_curr][csp->num_val_assigne[var_deja_assigne] ] == 0) //mauvais sens
			if(tuples[csp->num_val_assigne[var_deja_assigne] ][val_curr] == 0) //Tuple non valide
                return 1;
		}

	}

	return 0;
}

/***********************************************
 *         FORWARDCHECKING FUNCTIONS
 ***********************************************/

void filtrer_domaine(CSP * csp, int domaine[VARIABLE_MAX][VALEUR_MAX], int var_assigne, int val_assigne)
{
    //On boucle sur les colonnes, car elles représentent les variables non assignés
    for(int nvar = var_assigne + 1; nvar < csp->var_length; nvar++)
    {
        int ** tuples = csp->contraintes[var_assigne][nvar];

        if(tuples != NULL)
        {
            for(int nval = 0; nval < csp->val_length; nval++)
            {
                if(tuples[val_assigne][nval] == 0)
                    domaine[nvar][nval] = 0;
            }
        }
    }
}
