
#include "backjumping.h"


int backjumping(CSP * csp)
{


    int EMPILE;
    int nb_sol = 0;

    Pile p;
    init_pile(csp->var_length, &p);
    int temp_domaines[VARIABLE_MAX][VALEUR_MAX];
    domaines_copie(temp_domaines, csp->domaines, csp);
    int contrainte_enfreinte;










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

                    contrainte_enfreinte = assignation_enfreint_contraintes_bj(num_var, num_val, csp);

                    temp_domaines[num_var][num_val] = 0;

                    if(contrainte_enfreinte!=-1)
                    {
                        printf("%d",contrainte_enfreinte);
                        printf("contrainte enfreinte\n");

                        continue;

                    }

                    else
                    {

                        empile(num_var, num_val, &p);
                        printf("c'est ok\n");
                        contrainte_enfreinte=-1;

                        if(pile_pleine(&p))
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

        else
        {
            printf("caca");
            Etat * e = depile(&p);
            if(e == NULL)// On a dépilé une pile vide
                return nb_sol;
            reinitialiser_domaine(temp_domaines,num_var, csp->domaines);
             num_var=num_var-2;

             continue;

        }

        if(!EMPILE)
        {


            if(contrainte_enfreinte!=-1){
            if(domaine_var_vide(temp_domaines,contrainte_enfreinte))
                contrainte_enfreinte--;
            for(;num_var>contrainte_enfreinte;num_var--)
            {

                Etat * e= depile(&p);
                if(e == NULL)
                    return nb_sol;
                reinitialiser_domaine(temp_domaines,num_var, csp->domaines);
                printf("reinit de %d\n",num_var);



            }


            num_var = contrainte_enfreinte-1;
            }


            else
            {
                    /*Etat * e= depile(&p);
                    if(e == NULL)
                        return nb_sol;
                    reinitialiser_domaine(temp_domaines,num_var, csp->domaines);*/
                    num_var= num_var-2;
            }
            printf("var cour %d\n",num_var);
            continue;


        }

    }

    return nb_sol;
}








