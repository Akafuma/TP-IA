
#include "backjumping.h"

// renvoie la valeur qui partage la contrainte ou -1

int assignation_enfreint_contraintes_bj(int var_curr, int val_curr, CSP *csp)
{
	for(int var_deja_assigne = 0; var_deja_assigne < var_curr; var_deja_assigne++) //Ici on assigne dans l'ordre, donc on a assign� toutes la variables pr�cedant celle courante
	{
	    //On boucle sur les lignes, car elles representent les variables d�j� assign�
		//int ** tuples = csp->contraintes[var_curr][var_deja_assigne]; //mauvais sens
		int ** tuples = csp->contraintes[var_deja_assigne][var_curr];

		if(tuples != NULL) // Il y a contraintes
		{
			//if(tuples[val_curr][csp->num_val_assigne[var_deja_assigne] ] == 0) //mauvais sens
			if(tuples[csp->num_val_assigne[var_deja_assigne] ][val_curr] == 0) //Tuple non valide
                return var_deja_assigne;
		}

	}

	return -1;
}


int backjumping(CSP * csp)
{
    int EMPILE;
    int nb_sol = 0;

    Pile p;
    init_pile(csp->var_length, &p);
    int temp_domaines[VARIABLE_MAX][VALEUR_MAX];
    domaines_copie(temp_domaines, csp->domaines, csp);
    int contrainte_enfreinte = -1;  // pour connaitre la contrainte enfreinte courante
    int tab_contraintes[csp->var_length];  // tabl qui garde en m�moire la variable la plus profonde qui partage la contrainte avec la variable courante

    for(int i=0;i<csp->var_length;i++)
        tab_contraintes[i]=VARIABLE_MAX+1;

    for(int num_var=0;num_var< csp->var_length;num_var++)  // on choisit la variable
    {
		
        EMPILE = 0;

        if(!domaine_var_vide(temp_domaines, num_var))
        {
			
            for(int num_val = 0; num_val < csp->val_length; num_val++)
            {

                if(appartient_domaine(num_var, num_val, temp_domaines))
                {

                    csp->num_val_assigne[num_var] = num_val;                    

                    contrainte_enfreinte = assignation_enfreint_contraintes_bj(num_var, num_val, csp); // on stocke la variable qui enfreint ou non une contraine
                    if(contrainte_enfreinte < tab_contraintes[num_var]  && (contrainte_enfreinte != -1))
						tab_contraintes[num_var]=contrainte_enfreinte;
                    
                    printf("On assigne %d a la variable%d\n",num_val, num_var);
                    
                    temp_domaines[num_var][num_val] = 0;

                    if(contrainte_enfreinte!=-1)
                    {
                      //  printf("%d %d\n",tab_contraintes[num_var],VARIABLE_MAX+1);*/
                        printf("%d",contrainte_enfreinte);
                        printf("contrainte enfreinte\n");
                        continue;

                    }

                    else // on peut assigner la var
                    {
                        empile(num_var, num_val, &p);
                       // printf("c'est ok\n");

                        if(pile_pleine(&p)) // on a trouv� une solution on cherche une autre valeur pour cette variable
                        {
                            nb_sol++;
                            printf("sol trouve\n");
                            depile(&p);
                        
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
                contrainte_enfreinte=tab_contraintes[num_var];
                for(;num_var>contrainte_enfreinte;num_var--)
                {

                    Etat * e= depile(&p);
                    if(e == NULL)
                        return nb_sol;
                    reinitialiser_domaine(temp_domaines,num_var, csp->domaines);
                    tab_contraintes[num_var]=VARIABLE_MAX+1;
                    printf("reinit de %d\n",num_var);

                }


                num_var = contrainte_enfreinte-1;

            
            continue;


        }

    }

    return nb_sol;
}

