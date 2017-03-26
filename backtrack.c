#include "backtrack.h"

//Combiner pile + bool assigne[VAR_MAX], on choisit une variable à assigner,si vide, alors solution
//Le dépilage renvoi la variable, que l'on peut désassigner

int backtrack(CSP * csp)
{
    int EMPILE;
    int nb_sol = 0;

    Pile p;
    init_pile(csp->var_length, &p);

    int temp_domaines[VARIABLE_MAX][VALEUR_MAX];
    domaines_copie(temp_domaines, csp->domaines, csp);

    for(int num_var = 0; num_var < csp->var_length; num_var++)
    {
        EMPILE = 0;

        if(!domaine_var_vide(temp_domaines, num_var))
        {
            for(int num_val = 0; num_val < csp->val_length; num_val++)
            {

                if(appartient_domaine(num_var, num_val, temp_domaines))
                {
                    //on essaye d'assigner la num_val valeur à la num_var variable
                    csp->num_val_assigne[num_var] = num_val;

                    int contrainte_enfreinte = assignation_enfreint_contraintes(num_var, num_val, csp);

                    temp_domaines[num_var][num_val] = 0; //On note que la valeur a été affecté/essayé

                    if(contrainte_enfreinte)//On tente d'assigner une nouvelle valeur
                    {
                        continue;
                    }
                    else //Affection correcte
                    {
                        empile(num_var, num_val, &p);


                        if(pile_pleine(&p))//SOLUTION
                        {
                            nb_sol++;
                            //print_pile(&p, csp);
                            //On dépile pour continuer à chercher toutes les solutions
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
            if(e == NULL)// On a dépilé une pile vide
                return nb_sol;

            reinitialiser_domaine(temp_domaines, num_var, csp->domaines);

            num_var = num_var - 2;
            continue;
        }

    }//END FOR num_var

    return nb_sol;
}
