#include "generators.h"

CSP * generate_pigeons(int n)
{	
	CSP *csp;
	
	csp->variables = malloc(sizeof(int) * n);
	for(int i = 0; i < n; i++)
		csp->variables[i] = i;
		
	csp->valeurs = malloc(sizeof(int) * n - 1);
	for(int i = 0; i < n - 1; i++)
		csp->valeurs[i] = i;
		
	csp->domaines = malloc(sizeof(int*) * n);
	for(int i = 0; i < n ; i++)
		csp->domaines[i] = malloc(sizeof(int) * (n - 1));
	for(int l = 0; l < n; l++)
	{
		for(int c = 0; c < n - 1; c++)
			csp->domaines[l][c] = 1;
	}
	
	/* La matrice contraintes à 4 ETOILES */
	
	csp->contraintes = malloc(sizeof(int***) * n);
	for(int i = 0; i < n; i++)
		csp->contraintes[i] = malloc(sizeof(int**) * n);
	
	
	int **t = csp->contraintes[i][j];
	
	return csp;
}

int main()
{
	return 0;
}
