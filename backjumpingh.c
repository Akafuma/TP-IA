
#include "backjumpingh.h"

int assignation_enfreint_contraintes_bjh(int var_curr, int val_curr, CSP *csp,int tab_tour[]) // Renvoie la derniere variable assigné qui partage al contrainte
{
    int con=-1;
    int ** tuples;
	for(int var_deja_assigne = 0; var_deja_assigne < csp->var_length; var_deja_assigne++) //Ici on assigne dans l'ordre, donc on a assigné toutes la variables précedant celle courante
	{

	    if(csp->num_val_assigne[var_deja_assigne]!=-1)
        {


            //On boucle sur les lignes, car elles representent les variables déjà assigné
            //int ** tuples = csp->contraintes[var_curr][var_deja_assigne]; //mauvais sens
            if(var_deja_assigne>var_curr)
                tuples = csp->contraintes[var_curr][var_deja_assigne];
            else
                tuples = csp->contraintes[var_deja_assigne][var_curr];

            if(tuples != NULL) // Il y a contraintes
            {
                //if(tuples[val_curr][csp->num_val_assigne[var_deja_assigne] ] == 0) //mauvais sens
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
	//return -1;
}

int nb_assignation_enfreint_contraintes(int var_curr, CSP *csp) // nombre de contrainte que partage la var courante avec les vars déjà assignées
{
    int nb_contraintes;
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

int choisir_var(CSP * csp) // choisie la variable qui possède le plus de contraintes avec les variables déjà assignées
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







int backjumping_h(CSP * csp)
{
    int der_var_assigne=-1;

    int DOMAINE; // flag si domaine vide alors on revient sur la dernière variable assignée
    int EMPILE;
    int nb_sol = 0;
    int num_var=0;
    int tour=0;  // pour connaître l'ordre dans lequel les vars ont été assignées

    Pile p;
    init_pile(csp->var_length, &p);
    int temp_domaines[VARIABLE_MAX][VALEUR_MAX];
    domaines_copie(temp_domaines, csp->domaines, csp);
    int contrainte_enfreinte = -1;  // pour connaitre la contrainte enfreinte courante
    int tab_contraintes[csp->var_length];  // tabl qui garde en mémoire la variable la plus profonde qui partage la contrainte avec la variable courante

    int tab_tour[csp->var_length]; // on stocke quand la var à été assignée
    for(int i=0;i<csp->var_length;i++) //INITIALISATION
    {
        tab_contraintes[i]=-1;
        csp->num_val_assigne[i] = -1;
        csp->var_assigne[num_var]= 0;
        tab_tour[num_var]=-1;
    }


    while(num_var<csp->var_length)
    {

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

                            if(tab_contraintes[num_var]==-1) // si c'est la première rencontré par la var courante
                                tab_contraintes[num_var]=contrainte_enfreinte;
                            else if(tab_tour[contrainte_enfreinte]>tab_tour[tab_contraintes[num_var]])// sinon on vérifie si il existe une contrainte avec une variable plus profonde
                                tab_contraintes[num_var]=contrainte_enfreinte;
                    }

                    temp_domaines[num_var][num_val] = 0;

                    if(contrainte_enfreinte!=-1)
                    {
                        continue;

                    }

                    else // on peut assigner la var
                    {

                        empile(num_var, num_val, &p);
                        tour++;
                        tab_tour[num_var]=tour;


                        if(pile_pleine(&p)) // on a trouvé une solution on cherche une autre valeur pour cette variable
                        {

                            nb_sol++;

                            Etat * e = depile(&p);
                            tour--;
                            tab_tour[num_var]=-1;

                            if(domaine_var_vide(temp_domaines, num_var)) // si on a trouvé une sol mais le domaine de la var courante est vide
                            {
                                DOMAINE=0;
                                der_var_assigne=e->num_var;
                            }

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
            if(!DOMAINE)  // si on est la c'est qu'on a trouvé une sol mais le domaine est vide donc on revient sur la derniere var assignée
            {
                if(num_var>der_var_assigne)
                {
                    for(;num_var>der_var_assigne;num_var--)
                    {
                        if(csp->num_val_assigne[num_var] != -1)
                        {
                            Etat * e= depile(&p);
                            tour--;


                            if(e == NULL)
                                return nb_sol;
                        }
                        reinitialiser_domaine(temp_domaines,num_var, csp->domaines);
                        tab_contraintes[num_var]=-1;
                        csp->num_val_assigne[num_var]=-1;
                        csp->var_assigne[num_var] = 0;
                        tab_tour[num_var]=-1;


                    }


                }
                else
                {

                    for(;num_var<der_var_assigne;num_var++)
                    {
                        if(csp->num_val_assigne[num_var] != -1)
                        {
                            Etat * e= depile(&p);
                            tour--;


                            if(e == NULL)
                                return nb_sol;
                        }
                        reinitialiser_domaine(temp_domaines,num_var, csp->domaines);
                        tab_contraintes[num_var]=-1;
                        csp->num_val_assigne[num_var]=-1;
                        csp->var_assigne[num_var] = 0;
                        tab_tour[num_var]=-1;


                    }
                }

                num_var=der_var_assigne;
                DOMAINE=1;

                continue;

            }
            contrainte_enfreinte=tab_contraintes[num_var];


            if(num_var>contrainte_enfreinte)
            {

                for(;num_var>contrainte_enfreinte;num_var--)
                {

                    if(csp->num_val_assigne[num_var] != -1)
                    {
                        Etat * e= depile(&p);
                        tour--;


                        if(e == NULL)
                            return nb_sol;
                    }
                    reinitialiser_domaine(temp_domaines,num_var, csp->domaines);
                    tab_contraintes[num_var]=-1;
                    csp->num_val_assigne[num_var]=-1;
                    csp->var_assigne[num_var] = 0;
                    tab_tour[num_var]=-1;


                }
            }
            else
            {
                for(;num_var<contrainte_enfreinte;num_var++)
                {
                    if(csp->num_val_assigne[num_var] != -1)
                    {
                        Etat * e= depile(&p);
                        tour--;


                        if(e == NULL)
                            return nb_sol;
                    }
                    reinitialiser_domaine(temp_domaines,num_var, csp->domaines);
                    tab_contraintes[num_var]=-1;
                    csp->num_val_assigne[num_var]=-1;
                    csp->var_assigne[num_var] = 0;
                    tab_tour[num_var]=-1;






                }
            }



            num_var = contrainte_enfreinte;





            continue;


        }
        num_var=choisir_var(csp);


    }

    return nb_sol;



}
