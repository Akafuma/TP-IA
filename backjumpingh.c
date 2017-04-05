
#include "backjumpingh.h"
#include <windows.h>
int assignation_enfreint_contraintes_bjh(int var_curr, int val_curr, CSP *csp,int tab_tour[])
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
                    if(var_deja_assigne>con){
                      //  printf("\n %d \n",tab_tour[var_deja_assigne]);
                        con=var_deja_assigne;}
                    continue;
                }

            }
        }
	}

     return con;
	//return -1;
}

int nb_assignation_enfreint_contraintes(int var_curr, CSP *csp)
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

int choisir_var(CSP * csp){

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
    int der=-1;

    int DOMAINE; // flag si domaine vide alors on bt
    int EMPILE;
    int nb_sol = 0;
    int num_var=0;
    int tour=0;

    Pile p;
    init_pile(csp->var_length, &p);
    int temp_domaines[VARIABLE_MAX][VALEUR_MAX];
    domaines_copie(temp_domaines, csp->domaines, csp);
    int contrainte_enfreinte = -1;  // pour connaitre la contrainte enfreinte courante
    int tab_contraintes[csp->var_length];  // tabl qui garde en mémoire la variable la plus profonde qui partage la contrainte avec la variable courante
    int tab_tour[5]={0,4,3,2,1};

    for(int i=0;i<csp->var_length;i++){
        tab_contraintes[i]=-1;
        csp->num_val_assigne[i] = -1;
        csp->var_assigne[num_var]= 0;
        //tab_tour[num_var]=-1;
        }


    while(num_var<csp->var_length)
    //while(1)
    {
        //if(contrainte_enfreinte==-1)
        //num_var=choisir_var(csp);
        printf("var choisie%d\n",num_var);
        printf("tour %d\n",tab_tour[num_var]);
       // printf("csp %d\n",csp->var_length);
        EMPILE=0;
        //if(num_var>=0){


        if(!domaine_var_vide(temp_domaines, num_var))
        {

            for(int num_val=0; num_val< csp->val_length; num_val++)
            {

                if(appartient_domaine(num_var, num_val, temp_domaines))
                {


                    csp->num_val_assigne[num_var] = num_val;
                    csp->var_assigne[num_var]= 1;


                    contrainte_enfreinte = assignation_enfreint_contraintes_bjh(num_var, num_val, csp,tab_tour);
                    printf("%d \n", contrainte_enfreinte);

                    if(contrainte_enfreinte!=-1){
                            if(tab_tour[contrainte_enfreinte]>tab_contraintes[num_var])// si on trouve une var plus profonde qui partage la contrainte on l'écrase dans le tab
                        tab_contraintes[num_var]=contrainte_enfreinte;}

                    printf("On assigne %d a la variable%d\n",num_val, num_var);

                    temp_domaines[num_var][num_val] = 0;

                    if(contrainte_enfreinte!=-1)
                    {


                        printf("%d contrainte enfreinte\n",contrainte_enfreinte);

                        continue;

                    }

                    else // on peut assigner la var
                    {



                        empile(num_var, num_val, &p);
                        tour++;

                       printf("Empile\n");



                        if(pile_pleine(&p)) // on a trouvé une solution on cherche une autre valeur pour cette variable
                        {

                            nb_sol++;

                            printf("sol trouve\n");

                            /*if(nb_sol==4)
                                return nb_sol;*/
                           // write(csp, "Solution2.txt",nb_sol);
                            Etat * e = depile(&p);
                            tour--;

                            printf("Depile\n");


                            if(domaine_var_vide(temp_domaines, num_var)){
                                DOMAINE=0;


                                der=e->num_var;}

                            continue;


                        }

                        EMPILE =1;

                        break;

                }


            }



        }
    }
    else
    {
        Etat * e= depile(&p);
        tour--;

        printf("Depile\n");
        printf("CACA\n");
        if(e == NULL)
            return nb_sol;
        reinitialiser_domaine(temp_domaines,num_var, csp->domaines);
        tab_contraintes[num_var]=-1;
        csp->num_val_assigne[num_var]=-1;
        csp->var_assigne[num_var] = 0;


        num_var=e->num_var;

        continue;

        }
    if(!EMPILE)
        {
            if(!DOMAINE)  // si on est la c'est qu'on a trouvé une sol mais le domaine est vide donc on bt
            {
                if(num_var>der)
                {
                    for(;num_var>der;num_var--)
                    {
                         if(csp->num_val_assigne[num_var] != -1){
                                Etat * e= depile(&p);
                                tour--;

                                printf("Depile\n");
                                if(e == NULL)
                                    return nb_sol;}
                        reinitialiser_domaine(temp_domaines,num_var, csp->domaines);
                        tab_contraintes[num_var]=-1;
                        csp->num_val_assigne[num_var]=-1;
                        csp->var_assigne[num_var] = 0;


                    }


                }
                else
                {

                    for(;num_var<der;num_var++)
                    {
                        if(csp->num_val_assigne[num_var] != -1){
                            Etat * e= depile(&p);
                            tour--;

                            printf("Depile\n");
                            if(e == NULL)
                                return nb_sol;}
                        reinitialiser_domaine(temp_domaines,num_var, csp->domaines);
                        tab_contraintes[num_var]=-1;
                        csp->num_val_assigne[num_var]=-1;
                        csp->var_assigne[num_var] = 0;


                    }
                }

                num_var=der;
                DOMAINE=1;

                continue;

            }
            contrainte_enfreinte=tab_contraintes[num_var];


            if(num_var>contrainte_enfreinte)
            {

                for(;num_var>contrainte_enfreinte;num_var--)
                {

                    if(csp->num_val_assigne[num_var] != -1){
                        Etat * e= depile(&p);
                        tour--;

                        printf("Depile\n");
                        if(e == NULL)
                            return nb_sol;}
                    reinitialiser_domaine(temp_domaines,num_var, csp->domaines);
                    tab_contraintes[num_var]=-1;
                    csp->num_val_assigne[num_var]=-1;
                    csp->var_assigne[num_var] = 0;

                    printf("reinit de %d\n",num_var);





                }
            }
            else
            {
                for(;num_var<contrainte_enfreinte;num_var++)
                {
                    if(csp->num_val_assigne[num_var] != -1){
                        Etat * e= depile(&p);
                        tour--;

                        printf("Depile\n");
                        if(e == NULL)
                            return nb_sol;}
                    reinitialiser_domaine(temp_domaines,num_var, csp->domaines);
                    tab_contraintes[num_var]=-1;
                    csp->num_val_assigne[num_var]=-1;
                    csp->var_assigne[num_var] = 0;

                    printf("reinit de %d\n",num_var);





                }
            }


                printf("der : %d\n",der);
                num_var = contrainte_enfreinte;





            continue;


        }
        num_var=choisir_var(csp);


    }

    return nb_sol;



}
