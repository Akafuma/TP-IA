#include "forward-checking-md.h"

void filtrer_domaine_md(CSP * csp, int domaines[VARIABLE_MAX][VALEUR_MAX], int var_assigne, int val_assigne)
{
    for(int nvar = 0; nvar < csp->var_length; nvar++)
    {
        if(csp->var_assigne[nvar] == 0)
        {
            int ** tuples;
            tuples = csp->contraintes[var_assigne][nvar];

            if(tuples != NULL)
            {
                for(int nval = 0; nval < csp->val_length; nval++)
                {
                    if(tuples[val_assigne][nval] == 0)
                        domaines[nvar][nval] = 0;
                }
            }
        }
    }
}

int domaines_vide_md(CSP * csp, int domaines[VARIABLE_MAX][VALEUR_MAX])
{
    for(int var = 0; var < csp->var_length; var++)
    {
        if(csp->var_assigne[var] == 0)
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
    }
    return 0;
}

int choisir_variable_md(CSP * csp, int domaines[VARIABLE_MAX][VALEUR_MAX])
{
    int var_choisi = 0;
    int min = VALEUR_MAX + 1;
    for(int var = 0; var < csp->var_length; var++)
    {
        if(csp->var_assigne[var] == 0)
        {
            int count = 0;
            for(int val = 0; val < csp->val_length; val++)
            {
                if(domaines[var][val] == 1)
                    count++;
            }
            if(count == 0)//domaine vide
                return -1;

            if(count < min)
            {
                min = count;
                var_choisi = var;
            }
        }
    }
    return var_choisi;
}

//Renvoi le nombre de solutions du CSP
int forward_checking_md(CSP * csp)
{
    int nb_sol = 0;
    int EMPILE;

    int tmp[VARIABLE_MAX][VALEUR_MAX];
    int domaines_courant[VARIABLE_MAX][VALEUR_MAX];
    domaines_copie(domaines_courant, csp->domaines, csp);

    Pile p;
    init_pile(csp->var_length, &p);

    int num_var = 0;

    while(1)
    {
        num_var = choisir_variable_md(csp, domaines_courant);

        EMPILE = 0;

        if(num_var >= 0)
        {
            for(int num_val = 0; num_val < csp->val_length; num_val++)
            {
                if(appartient_domaine(num_var, num_val, domaines_courant))
                {
                    domaines_courant[num_var][num_val] = 0;
                    csp->var_assigne[num_var] = 1;
                    csp->num_val_assigne[num_var] = num_val; // On assigne

                    domaines_copie(tmp, domaines_courant, csp);

                    filtrer_domaine_md(csp, tmp, num_var, num_val);

                    if(domaines_vide_md(csp, tmp))
                    {
                        continue;
                    }
                    else
                    {
                        empile(num_var, num_val, &p);
                        Etat * e = get_top(&p);
                        domaines_copie(e->domaines, domaines_courant, csp);//on empile l'état avant filtrage;

                        domaines_copie(domaines_courant, tmp, csp);

                        if(pile_pleine(&p))
                        {
                            nb_sol++;
                            //print_pile(&p, csp);
                            depile(&p);

                            csp->var_assigne[num_var] = 0;

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
            csp->var_assigne[num_var] = 0;
            Etat * e = depile(&p);
            if(e == NULL) // Racine
                return nb_sol;

            csp->var_assigne[e->num_var] = 0;
            domaines_copie(domaines_courant, e->domaines, csp);

            continue;
        }

    }//END WHILE

    return nb_sol;
}
