#include "forward-checking-test.h"

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
                    domaine[nvar][nval]--;
            }
        }
    }
}

void defiltrer_domaine((CSP * csp, int domaine[VARIABLE_MAX][VALEUR_MAX], int var_assigne, int val_assigne)
{
    for(int nvar = var_assigne + 1; nvar < csp->var_length; nvar++)
    {
        int ** tuples = csp->contraintes[var_assigne][nvar];

        if(tuples != NULL)
        {
            for(int nval = 0; nval < csp->val_length; nval++)
            {
                if(tuples[val_assigne][nval] == 0)
                    domaine[nvar][nval]++;
            }
        }
    }
}

//Renvoi le nombre de solutions du CSP
int forward_checking(CSP * csp)
{
    int nb_sol = 0;
    int EMPILE;

    int tmp[VARIABLE_MAX][VALEUR_MAX];
    int domaines_courant[VARIABLE_MAX][VALEUR_MAX];
    domaines_copie(domaines_courant, csp->domaines, csp);

    Pile p;
    init_pile(csp->var_length, &p);

    for(int num_var = 0; num_var < csp->var_length; num_var++)
    {
        EMPILE = 0;

        if(!domaine_var_vide(domaines_courant, num_var))
        {

            for(int num_val = 0; num_val < csp->val_length; num_val++)
            {
                if(appartient_domaine(num_var, num_val, domaines_courant))
                {
                    csp->num_val_assigne[num_var] = num_val; // On assigne
                    domaines_courant[num_var][num_val]--;

                    filtrer_domaine(csp, domaines_courant, num_var, num_val);

                    if(domaines_vide(tmp, num_var, csp))
                    {
						defiltrer_domaine(csp, domaines_courant, num_var, num_val);
                        continue;
                    }
                    else
                    {
                        empile(num_var, num_val, &p);

                        if(pile_pleine(&p))
                        {
                            nb_sol++;
                            //print_pile(&p, csp);
                            depile(&p);

                            continue;
                        }
                        EMPILE = 1;
                        break;
                    }
                }
            }//END FOR num_val
        }

        if(!EMPILE)
        {
            //BACKTRACK
            Etat * e = depile(&p);
            if(e == NULL) // Racine
                return nb_sol;

            num_var = num_var - 2;
            defiltrer_domaine(csp, domaines_courant, e->num_var, e->num_val);

            continue;
        }

    }//END FOR num_var

    return nb_sol;
}
