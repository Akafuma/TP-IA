#include "backjumping-mc.h"

int assignation_enfreint_contraintes_bjh(int var_curr, int val_curr, CSP *csp,int tab_tour[]) // Renvoie la derniere variable assign� qui partage al contrainte
{
    int con=-1;
    int ** tuples;
	for(int var_deja_assigne = 0; var_deja_assigne < csp->var_length; var_deja_assigne++) //Ici on assigne dans l'ordre, donc on a assign� toutes la variables pr�cedant celle courante
	{

	    if(csp->num_val_assigne[var_deja_assigne]!=-1)
        {
            //On boucle sur les lignes, car elles representent les variables d�j� assign�
            if(var_deja_assigne>var_curr)
                tuples = csp->contraintes[var_curr][var_deja_assigne];
            else
                tuples = csp->contraintes[var_deja_assigne][var_curr];

            if(tuples != NULL) // Il y a contraintes
            {
                #ifdef PRINT_CONTRAINTES
                    nb_contraintes++;
                #endif //PRINT_CONTRAINTES

                if(tuples[csp->num_val_assigne[var_deja_assigne] ][val_curr] == 0) //Tuple non valide
                {
                    if(con==-1)
                        con=var_deja_assigne;
                    else if(tab_tour[var_deja_assigne]>tab_tour[con])
                        con=var_deja_assigne;
                    continue;
                }
            }
        }
	}

    return con;
}

int nb_assignation_enfreint_contraintes(int var_curr, CSP *csp) // nombre de contrainte que partage la var courante avec les vars d�j� assign�es
{
    int nb_contraintes=0;
    int num_var=0;

    while(num_var!=csp->var_length)
    {
        if(csp->var_assigne[num_var]!=-1)
        {
            int ** tuples = csp->contraintes[num_var][var_curr];
            if(tuples!=NULL)
                nb_contraintes++;
        }
        num_var++;
    }

    return nb_contraintes;
}

int choisir_var(CSP * csp) // choisie la variable qui poss�de le plus de contraintes avec les variables d�j� assign�es
{
    int var_choisie=-1;
    int nb_contrainte_curr=-1;

    for(int num_var=0;num_var<csp->var_length;num_var++)
    {

        if(csp->num_val_assigne[num_var]==-1)
        {
            if(nb_assignation_enfreint_contraintes(num_var, csp)>nb_contrainte_curr)
            {
                var_choisie=num_var;
                nb_contrainte_curr=nb_assignation_enfreint_contraintes(num_var, csp);
            }
        }
    }

    return var_choisie;
}


int backjumping_mc(CSP * csp)
{
    int EMPILE;
    int nb_sol = 0;
    int num_var=0;
    int tour=0;  // pour conna�tre l'ordre dans lequel les vars ont �t� assign�es

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
    int contrainte_enfreinte = -1;  // pour connaitre la contrainte enfreinte courante
    int tab_contraintes[csp->var_length];  // tabl qui garde en m�moire la variable la plus profonde qui partage la contrainte avec la variable courante

    int tab_tour[csp->var_length]; // on stocke quand la var � �t� assign�e
    for(int i=0;i<csp->var_length;i++) //INITIALISATION
    {
        tab_contraintes[i]=-1;
        csp->num_val_assigne[i] = -1;
        csp->var_assigne[i]= 0;
        tab_tour[i]=-1;
    }

    while(1)
    {
        if(tab_tour[num_var]==-1){
        tour++;
        tab_tour[num_var]=tour;}
        EMPILE=0;

        if(!domaine_var_vide(temp_domaines, num_var))
        {
            for(int num_val=0; num_val< csp->val_length; num_val++)
            {
                if(appartient_domaine(num_var, num_val, temp_domaines))
                {
                    csp->num_val_assigne[num_var] = num_val;
                    csp->var_assigne[num_var]= 1;

                    contrainte_enfreinte = assignation_enfreint_contraintes_bjh(num_var, num_val, csp,tab_tour);

                    if(contrainte_enfreinte!=-1) // si on a une contrainte
                    {
                            if(tab_contraintes[num_var]==-1) // si c'est la premi�re rencontr� par la var courante
                                tab_contraintes[num_var]=contrainte_enfreinte;
                            else if(tab_tour[contrainte_enfreinte]>tab_tour[tab_contraintes[num_var]])// sinon on v�rifie si il existe une contrainte avec une variable plus profonde
                                tab_contraintes[num_var]=contrainte_enfreinte;
                    }

                    temp_domaines[num_var][num_val] = 0;
                    #ifdef PRINT_NOEUD
                        nb_noeud++;
                    #endif // PRINT_NOEUD

                    if(contrainte_enfreinte!=-1)
                        continue;

                    else // on peut assigner la var
                    {
                        empile(num_var, num_val, &p);
                        if(pile_pleine(&p)) // on a trouv� une solution on cherche une autre valeur pour cette variable
                        {
                            nb_sol++;
                            #ifdef PRINT_SOL
                                print_pile(&p, csp);
                            #endif // PRINT_SOL

                            Etat * e = depile(&p);
                            continue;
                        }
                        EMPILE =1;
                        break;
                    }
                }
            }
        }

        if(!EMPILE)
        {
            contrainte_enfreinte=tab_contraintes[num_var];
            if(contrainte_enfreinte==-1)
            {
                #ifdef PRINT_NOEUD
                    printf("Noeuds visite %f\n", nb_noeud);
                #endif // PRINT_NOEUD
                #ifdef PRINT_CONTRAINTES
                    printf("Contraintes explorees : %f\n", nb_contraintes);
                #endif //PRINT_CONTRAINTES
                return nb_sol;
            }

            if(num_var>contrainte_enfreinte)
            {
                for(;num_var>contrainte_enfreinte;num_var--)
                {
                    if(csp->num_val_assigne[num_var] != -1)
                    {
                        if(tab_tour[num_var]>tab_tour[contrainte_enfreinte])
                        {
                            Etat * e= depile(&p);
                            tour--;
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
                            csp->num_val_assigne[num_var]=-1;
                            csp->var_assigne[num_var] = 0;
                            tab_tour[num_var]=-1;
                        }
                    }

                }
            }
            else
            {
                for(;num_var<contrainte_enfreinte;num_var++)
                {
                    if(csp->num_val_assigne[num_var] != -1)
                    {
                        if(tab_tour[num_var]>tab_tour[contrainte_enfreinte])
                        {
                            Etat * e= depile(&p);
                            tour--;
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
                            csp->num_val_assigne[num_var]=-1;
                            csp->var_assigne[num_var] = 0;
                            tab_tour[num_var]=-1;
                        }
                    }
                }
            }
            num_var = contrainte_enfreinte;
            continue;
        }
        num_var=choisir_var(csp);
    }

    return nb_sol;
}
