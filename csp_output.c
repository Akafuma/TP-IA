#include "csp_output.h"

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
