#include "forward-checking.h"

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
                    domaines_courant[num_var][num_val] = 0;

                    domaines_copie(tmp, domaines_courant, csp);

                    filtrer_domaine(csp, tmp, num_var, num_val);

                    if(domaines_vide(tmp, num_var, csp))
                    {
                        continue;
                    }
                    else
                    {
                        empile(num_var, num_val, &p);
                        Etat * e = get_top(&p);
                        domaines_copie(e->domaines, domaines_courant, csp);//on empile l'état avant filtrage

                        domaines_copie(domaines_courant, tmp, csp);

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
            domaines_copie(domaines_courant, e->domaines, csp);

            continue;
        }

    }//END FOR num_var

    return nb_sol;
}
