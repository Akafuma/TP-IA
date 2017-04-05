#include "backjumping.h"
#include <windows.h>
// renvoie la valeur qui partage la contrainte ou -1

int assignation_enfreint_contraintes_bj(int var_curr, int val_curr, CSP *csp)
{
    int con=-1;
	for(int var_deja_assigne = 0; var_deja_assigne < var_curr; var_deja_assigne++) //Ici on assigne dans l'ordre, donc on a assigné toutes la variables précedant celle courante
	{
	    //On boucle sur les lignes, car elles representent les variables déjà assigné
		//int ** tuples = csp->contraintes[var_curr][var_deja_assigne]; //mauvais sens
		int ** tuples = csp->contraintes[var_deja_assigne][var_curr];

		if(tuples != NULL) // Il y a contraintes
		{
			//if(tuples[val_curr][csp->num_val_assigne[var_deja_assigne] ] == 0) //mauvais sens
			if(tuples[csp->num_val_assigne[var_deja_assigne] ][val_curr] == 0) //Tuple non valide
			{
			    if(var_deja_assigne>con)
                    con=var_deja_assigne;
                continue;
			}

		}

	}
     return con;
	//return -1;
}


int backjumping(CSP * csp)
{
    int num_val;
    int EMPILE;
    int nb_sol = 0;
    int DOMAINE;
    Pile p;
    init_pile(csp->var_length, &p);
    int temp_domaines[VARIABLE_MAX][VALEUR_MAX];
    domaines_copie(temp_domaines, csp->domaines, csp);
    int contrainte_enfreinte;  // pour connaitre la contrainte enfreinte courante
    int tab_contraintes[csp->var_length];  // tabl qui garde en mémoire la variable la plus profonde qui partage la contrainte avec la variable courante

    for(int i=0;i<csp->var_length;i++)
        tab_contraintes[i]=-1;
       // tab_contraintes[i]=VARIABLE_MAX+1;

    for(int num_var=0;num_var< csp->var_length;num_var++)  // on choisit la variable
    {
        /*if(csp->num_val_assigne[1]==7 && nb_sol==3){
            printf("0 vaut %d et 1 vaut %d\n",csp->num_val_assigne[0],csp->num_val_assigne[1]);
            return nb_sol;}*/

        EMPILE = 0;

        if(!domaine_var_vide(temp_domaines, num_var))
        {

            for(num_val = 0; num_val < csp->val_length; num_val++)
            {

                if(appartient_domaine(num_var, num_val, temp_domaines))
                {

                    csp->num_val_assigne[num_var] = num_val;

                    contrainte_enfreinte = assignation_enfreint_contraintes_bj(num_var, num_val, csp); // on stocke la variable qui enfreint ou non une contraine


                    if(contrainte_enfreinte > tab_contraintes[num_var])
                        /*while(domaine_var_vide(temp_domaines, contrainte_enfreinte)){
                                printf("%d\n",contrainte_enfreinte);
                            contrainte_enfreinte = assignation_enfreint_contraintes_bj(num_var, num_val, csp,contrainte_enfreinte);}*/
                        tab_contraintes[num_var]=contrainte_enfreinte;
                    //if(nb_sol==3){
                    //printf("On assigne %d a la variable%d\n",num_val, num_var);
                   // Sleep(1000);
                    //}

                    temp_domaines[num_var][num_val] = 0;

                    if(contrainte_enfreinte!=-1)
                    {
                      //  printf("%d %d\n",tab_contraintes[num_var],VARIABLE_MAX+1);*/
                     // if(nb_sol==3){
                        //printf("%d contrainte enfreinte\n",contrainte_enfreinte);
                        //Sleep(1000);
                       // }
                        continue;

                    }

                    else // on peut assigner la var
                    {
                        empile(num_var, num_val, &p);

                       // printf("c'est ok\n");

                        if(pile_pleine(&p)) // on a trouvé une solution on cherche une autre valeur pour cette variable
                        {
                            nb_sol++;
                           // if(nb_sol==3){
                            //printf("\nsol trouve\n");
                            //Sleep(1000);
                           // }
                            write(csp, "Solution.txt",nb_sol);
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

        else
        {
            Etat * e = depile(&p);
            if(e == NULL)// On a dépilé une pile vide
                return nb_sol;

            reinitialiser_domaine(temp_domaines, num_var, csp->domaines);
            tab_contraintes[num_var]=-1;
            num_var=num_var-2;
            continue;
        }

        if(!EMPILE)
        {


                if(DOMAINE==0){

                    Etat * e = depile(&p);
                    if(e == NULL)// On a dépilé une pile vide
                        return nb_sol;

                    reinitialiser_domaine(temp_domaines, num_var, csp->domaines);
                    tab_contraintes[num_var]=-1;
                   // num_var = num_var - 2;
                   //printf("%d",num_var);
                    num_var=num_var-2;



                    DOMAINE=1;
                    continue;}


                contrainte_enfreinte=tab_contraintes[num_var];
               // printf("%d\n",contrainte_enfreinte);
                if(domaine_var_vide(temp_domaines, contrainte_enfreinte))
                   contrainte_enfreinte--;




                for(;num_var>contrainte_enfreinte;num_var--)
                {

                    Etat * e= depile(&p);
                    if(e == NULL)
                        return nb_sol;
                    reinitialiser_domaine(temp_domaines,num_var, csp->domaines);
                    tab_contraintes[num_var]=-1;
                    //if(nb_sol==3){
                    //printf("reinit de %d 0 vaut %d\n",num_var,csp->num_val_assigne[0]);
                    //Sleep(1000);
                   // }
                }


                num_var = contrainte_enfreinte-1;

                //contrainte_enfreinte=-1;

            continue;


        }

    }

    return nb_sol;
}
