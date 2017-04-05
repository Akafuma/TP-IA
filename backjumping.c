#include "backjumping.h"

// renvoie la valeur qui partage la contrainte ou -1
int assignation_enfreint_contraintes_bj(int var_curr, int val_curr, CSP *csp)
{
    int con = -1;
	for(int var_deja_assigne = 0; var_deja_assigne < var_curr; var_deja_assigne++)
	{
		int ** tuples = csp->contraintes[var_deja_assigne][var_curr];

		if(tuples != NULL) // Il y a contraintes
		{
		    #ifdef PRINT_CONTRAINTES
                    nb_contraintes++;
            #endif //PRINT_CONTRAINTES
			if(tuples[csp->num_val_assigne[var_deja_assigne] ][val_curr] == 0) //Tuple non valide
			{
			    if(var_deja_assigne>con)
                    con = var_deja_assigne;
                continue;
			}
		}
	}
    return con;
}

int backjumping(CSP * csp)
{
    int num_val;
    int EMPILE;
    int nb_sol = 0;
    int DOMAINE;

    #ifdef PRINT_NOEUD
        double nb_noeud = 0;
    #endif // PRINT_NOEUD
    #ifdef PRINT_CONTRAINTES
        nb_contraintes = 0;
    #endif //PRINT_CONTRAINTES

    Pile p;
    init_pile(csp->var_length, &p);

    int temp_domaines[VARIABLE_MAX][VALEUR_MAX];
    domaines_copie(temp_domaines, csp->domaines, csp);
    int contrainte_enfreinte;  // pour connaitre la contrainte enfreinte courante
    int tab_contraintes[csp->var_length];  // tableau qui garde en mémoire la variable la plus profonde qui partage la contrainte avec la variable courante

    for(int i=0;i<csp->var_length;i++)
        tab_contraintes[i]=-1;

    for(int num_var=0;num_var< csp->var_length;num_var++)  // on choisit la variable
    {
        EMPILE = 0;

        if(!domaine_var_vide(temp_domaines, num_var))
        {

            for(num_val = 0; num_val < csp->val_length; num_val++)
            {

                if(appartient_domaine(num_var, num_val, temp_domaines))
                {

                    csp->num_val_assigne[num_var] = num_val;

                    contrainte_enfreinte = assignation_enfreint_contraintes_bj(num_var, num_val, csp); // on stocke la variable qui enfreint ou non une contrainte

                    if(contrainte_enfreinte > tab_contraintes[num_var])
                        tab_contraintes[num_var]=contrainte_enfreinte;

                    temp_domaines[num_var][num_val] = 0;
                    #ifdef PRINT_NOEUD
                        nb_noeud++;
                    #endif // PRINT_NOEUD

                    if(contrainte_enfreinte!=-1)
                    {
                        continue;
                    }

                    else // on peut assigner la var
                    {
                        empile(num_var, num_val, &p);

                        if(pile_pleine(&p)) // on a trouvé une solution on cherche une autre valeur pour cette variable
                        {
                            nb_sol++;
                            #ifdef PRINT_SOL
                                print_pile(&p, csp);
                            #endif // PRINT_SOL
                            depile(&p);

                            if(domaine_var_vide(temp_domaines, num_var))
                                DOMAINE=0;
                            continue;
                        }

                        EMPILE =1;

                        break;
                    }

                }
            } // for val
        }

        if(!EMPILE)
        {
            if(DOMAINE==0)
            {
                Etat * e = depile(&p);
                if(e == NULL)// On a dépilé une pile vide
                {
                    #ifdef PRINT_NOEUD
                        printf("Noeuds visite %f\n", nb_noeud);
                    #endif // PRINT_NOEUD
                    #ifdef PRINT_CONTRAINTES
                        printf("Contraintes explorees : %f\n", nb_contraintes);
                    #endif //PRINT_CONTRAINTES
                        return nb_sol;
                }

                reinitialiser_domaine(temp_domaines, num_var, csp->domaines);
                tab_contraintes[num_var]=-1;
                num_var=num_var-2;

                DOMAINE=1;
                continue;
            }

            contrainte_enfreinte=tab_contraintes[num_var];

            if(domaine_var_vide(temp_domaines, contrainte_enfreinte))
                contrainte_enfreinte--;

            for(;num_var>contrainte_enfreinte;num_var--)
            {
                Etat * e = depile(&p);
                if(e == NULL)
                {
                    #ifdef PRINT_NOEUD
                        printf("Noeuds visite %f\n", nb_noeud);
                    #endif // PRINT_NOEUD
                    #ifdef PRINT_CONTRAINTES
                        printf("Contraintes explorees : %f\n", nb_contraintes);
                    #endif //PRINT_CONTRAINTES
                        return nb_sol;
                }

                reinitialiser_domaine(temp_domaines,num_var, csp->domaines);
                tab_contraintes[num_var]=-1;
            }

            num_var = contrainte_enfreinte-1;

        continue;
        }

    }

    return nb_sol;
}
