#include "util.h"

int appartient_domaine(int var, int val, int domaines[VARIABLE_MAX][VALEUR_MAX])
{
	return domaines[var][val];
}

/*
 * Renvoi 1 si l'assignation de la variable num var_curr à l'assignation numero val_curr enfreint au moins une contrainte
 * Renvoi 0 sinon
 */
int assignation_enfreint_contraintes(int var_curr, int val_curr, CSP *csp)
{	
	for(int var_deja_assigne = 0; var_deja_assigne < var_curr; var_deja_assigne++) //Ici on assigne dans l'ordre, donc on a assigné toutes la variables précedant celle courante
	{
		int ** tuples = csp->contraintes[var_curr][var_deja_assigne];
					
		if(tuples != NULL) // Il y a contraintes
		{
			if(tuples[val_curr][csp->num_val_assigne[var_deja_assigne] ] == 0) //Tuple non valide
				return 1;
		}
	}
		
	return 0;
}


void write_csp(const CSP * csp, const char * nom_fichier)
{
    FILE *f = NULL;

    f = fopen(nom_fichier, "w");

    if(f == NULL)
    {
        printf("Error fopen\n");
        exit(EXIT_FAILURE);
    }

    fprintf(f, "CSP %s : \n", nom_fichier);
    fprintf(f, "Nombre de variables : %d\n", csp->var_length);
    fprintf(f, "Nombre de valeurs : %d\n\n", csp->val_length);

    fprintf(f, "Tableau Variables : \n");
    for(int i = 0; i < csp->var_length; i++)
        fprintf(f, "%d\t", csp->variables[i]);
    fprintf(f, "\n");
    fprintf(f, "\n");

    fprintf(f, "Tableau Valeurs : \n");
    for(int i = 0; i < csp->val_length; i++)
        fprintf(f, "%d\t", csp->valeurs[i]);
    fprintf(f, "\n");
    fprintf(f, "\n");

    fprintf(f, "Table Domaines : \n");
    for(int i = 0; i < csp->var_length; i++)
    {
        for(int k = 0; k < csp->val_length; k++)
        {
            fprintf(f, "%d\t", csp->domaines[i][k]);
        }
        fprintf(f, "\n");
    }
    fprintf(f, "\n");
    fprintf(f, "\n");

    fprintf(f, "Table Contraintes :\n");
    for(int i = 0; i < csp->var_length; i++)
    {
        for(int k = 0; k < csp->var_length; k++)
        {
            if(csp->contraintes[i][k] == NULL)
                fprintf(f, "NULL\t");
            else
                fprintf(f, "%d\t", (int) csp->contraintes[i][k]);
        }
        fprintf(f, "\n");
    }
    fprintf(f, "\n");
    fprintf(f, "\n");

    for(int i = 0; i < csp->var_length; i++)
    {
        for(int k = 0; k < csp->var_length; k++)
        {
            int ** tuples = csp->contraintes[i][k];
            if(tuples != NULL)
            {
                fprintf(f, "Table relation %d %d\n", i, k);
                fprintf(f, " \t\t");

                for(int c = 0; c < csp->val_length; c++)
                {
                    fprintf(f, "%d\t", csp->valeurs[c]);
                }
                fprintf(f, "\n");
                fprintf(f, "\n");

                for(int l = 0; l < csp->val_length; l++)
                {
                    fprintf(f, "%d\t\t", csp->valeurs[l]);

                    for(int c = 0; c < csp->val_length; c++)
                    {
                        fprintf(f, "%d\t", tuples[l][c]);
                    }
                    fprintf(f, "\n");
                }
                fprintf(f, "\n");
                fprintf(f, "\n");
            }
        }
    }
}
