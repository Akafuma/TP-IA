#include "util.h"
#include "generators.h"
#include "forward-checking.h"
#include "backtrack.h"
#include "forward-checking-md.h"
#include "csp_output.h"
#include <time.h>

int main()
{
    CSP csp;
    int r;
    clock_t debut, fin;
    int nb_exec = 1;
    /*
    for(int i = 12; i < 13; i++)
    {
        float sum = 0;
        //generate_dames(i, &csp);
        generate_pigeons(i, &csp); // pigeons-12 = 31s pour FC

        for(int j = 0; j < nb_exec; j++)
        {
            debut = clock();
            backtrack(&csp);
            //forward_checking(&csp);
            //forward_checking_md(&csp);
            fin = clock();

            sum += (float) (fin - debut) / CLOCKS_PER_SEC;
        }
        printf("Temps moyen pour resoudre %d-pigeons : %f\n", i, sum / nb_exec);
        free_CSP(&csp);
    }
    */

    for(int i = 1; i < 13; i++)
    {
        //generate_dames(i, &csp);
        generate_pigeons(i, &csp);

        printf("%d-pigeons, ", i);
        //r = backtrack(&csp);
        //r = forward_checking(&csp);
        r = forward_checking_md(&csp);
        free_CSP(&csp);
    }


    /*
    generate_dames(10, &csp);
    //generate_pigeons(11, &csp); // critique � 11

    //write_csp(&csp, "5-dames.txt");

    debut = clock();
    r = forward_checking(&csp);
    fin = clock();
    printf("FC termine en %f sec\n", (float) (fin - debut) / CLOCKS_PER_SEC);
    printf("On a visite %d noeuds\n", r);

    debut = clock();
    r = forward_checking_md(&csp);
    fin = clock();
    printf("FCMD termine en %f sec\n", (float) (fin - debut) / CLOCKS_PER_SEC);
    printf("On a visite %d noeuds\n", r);

    debut = clock();
    r = backtrack(&csp);
    fin = clock();
    printf("BT termine en %f sec\n", (float) (fin - debut) / CLOCKS_PER_SEC);
    printf("On a visite %d noeuds\n", r);


    free_CSP(&csp);

    //printf("\nOn denombre %d solutions au CSP\n", r);
    */

	return 0;
}
