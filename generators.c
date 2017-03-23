#include "generators.h"

/*
 * Renvoi 1 si les 2 couples appartiennent à une meme diagonale
 * 0 sinon
 */
int meme_diagonale(int l1, int c1, int l2, int c2)
{
    // diagonale /
    if(l1 + c1 == l2 + c2) // si la somme des deux indices est la meme, alors ils partagent la diagonale
        return 1;

    /*diagonale \ */

    int base_l, base_c, goal_l, goal_c;

    //on va parcourir la diagonale du haut vers le bas, on cherche donc le couple le  plus haut placé
    if(l1 > l2 && c1 > c2) //(l2,c2) est le plus haut
    {
        base_l = l2;
        base_c = c2;
        goal_l = l1;
        goal_c = c1;
    }
    else if(l1 < l2 && c1 < c2) //(l1, c1) est le plus haut
    {
        base_l = l1;
        base_c = c1;
        goal_l = l2;
        goal_c = c2;
    }
    else // si les indices d'un des deux couples ne sont pas strictement plus grand, alors ils ne sont pas sur la meme diagonale
        return 0;

    while(base_l != goal_l)// on parcourt la diagonale de haut en bas
    {
        base_l++;
        base_c++;
    }

    return (base_c == goal_c); // base_l est égale à goal_l, on vérifie si on a pu atteindre le but en parcourant la diagonale
}

void generate_dames(int n, CSP * csp)
{
    if(n > VARIABLE_MAX)
        n = VARIABLE_MAX;

    csp->var_length = n;
    csp->val_length = n;

    //INIT VARIABLES & VALEURS
    for(int i = 0; i < n; i++)
    {
        csp->variables[i] = i;
        csp->valeurs[i] = i;
    }

    //INIT TABLE DOMAINE
    for(int l = 0; l < n; l++)
    {
        for(int c = 0; c < n; c++)
            csp->domaines[l][c] = 1;
    }

    //INIT CONSTRAINTS

    for(int l = 0, start = 0; l < n; l++, start++)
    {
        for(int c = start; c < n; c++)
        {
            if(c == l)  //Une variable ne porte pas de contraintes avec elle meme
            {
                csp->contraintes[l][c] = NULL;
                continue;
            }

            int ** tuples = NULL;
            //Allocation
            tuples = malloc(sizeof(int *) * n);
            for(int i = 0; i < n; i++)
                tuples[i] = malloc(sizeof(int) * n);

            //INIT TUPLES COMPATIBLES
            for(int u = 0; u < n; u++)
            {
                for(int v = 0; v < n; v++)
                {
                    tuples[u][v] = 1;

                    if(u == v) // meme colonne
                        tuples[u][v] = 0;
                    else if(meme_diagonale(l, u, c, v))
                        tuples[u][v] = 0;
                }
            }

            csp->contraintes[l][c] = tuples;
        }
    }
}

void generate_pigeons(int n, CSP * csp)
{
    if(n > VARIABLE_MAX)
        n = VARIABLE_MAX;

    csp->var_length = n;
    csp->val_length = n - 1;

    //INIT VARIABLES
    for(int i = 0; i < n; i++)
        csp->variables[i] = i;

    //INIT VALEURS
    for(int i = 0; i < n - 1; i++)
        csp->valeurs[i] = i;

    //INIT TABLE DOMAINE
    for(int l = 0; l < n; l++)
    {
        for(int c = 0; c < n - 1; c++)
            csp->domaines[l][c] = 1;
    }

    //INIT CONSTRAINTS
    for(int l = 0, start = 0; l < n; l++, start++)
    {
        for(int c = start; c < n; c++)
        {
            if(c == l)  //Une variable ne porte pas de contraintes avec elle meme
            {
                csp->contraintes[l][c] = NULL;
                continue;
            }

            int **tuples = NULL;
            //Allocation
            tuples = malloc(sizeof(int *) * (n - 1));
            for(int i = 0; i < n - 1; i++)
                tuples[i] = malloc(sizeof(int) * (n - 1));

            //INIT TUPLES COMPATIBLES
            for(int u = 0; u < n - 1; u++)
            {
                for(int v = 0; v < n - 1; v++)
                {
                    if(v != u)
                        tuples[u][v] = 1;
                    else
                        tuples[u][v] = 0;
                }
            }
            csp->contraintes[l][c] = tuples;
        }
    }
}

void free_CSP(CSP* csp)
{
    int n = csp->var_length;
    int m = csp->val_length;

    for(int l = 0; l < n; l++)
    {
        for(int c = 0; c < n; c++)
        {
            int ** tuples = csp->contraintes[l][c];

            if(tuples != NULL)
            {
                for(int i = 0; i < m; i++)
                    free(tuples[i]);
                free(tuples);
            }
        }
    }
}

int main()
{
    CSP csp;

    //generate_dames(8, &csp);
    generate_pigeons(7, &csp);
    //write_csp(&csp, "8-dames.txt");
    write_csp(&csp, "7-pigeons.txt");
    free_CSP(&csp);
    printf("Alright;\n");
	return 0;
}
