#include "forward-checking.h"

//Renvoi le nombre de solutions du CSP
int forward_checking(CSP * csp)
{
	int started = 0; // FLAG maybe useless
	int backtrack = 0; // FLAG
	int var_assigne[csp->var_length]; // boolean, en faire une pile ?
	
	int val_current[csp->var_length];
	
	//initialisation des tableaux
	for(int i = 0; i < csp->var_length; i++)
	{
		var_assigne[i] = 0;
		val_current[i] = 0;
	}
	
	for(int var = 0; var < csp->var_length; var++) // On parcourt les variables dans l'ordre
	{
		if(backtrack && (var < 0)) // On backtrack à partir de la racine
			return 0;//Pas de solution
		
		for(int val = 0; val < csp->val_length; val++) // On parcourt toutes les valeurs, utiliser val_assigne plutot???
		{
			if(appartient_domaine(var, val, csp->domaines)) // La valeur val appartient au domaine de la variable var
			{
				csp->num_val_assigne[var] = val; //on assigne la valeur numero val à var : var = csp->valeurs[val];
				var_assigne[var] = 1; // on a assigné la variable var
				//val_current[var] = val;
				
				int ** tuples;
				int contrainte_enfreinte;
				
				//Check si une contrainte n'est pas enfreinte
				contrainte_enfreinte = assignation_enfreint_contraintes(var, val, csp);
				
				if(contrainte_enfreinte && (val == csp->val_length - 1)) // si la dernière val du domaine de var ne satisfait pas les contraintes, on backtrack
				{
					var_assigne[var] = 0;
					var -= 2; // on revient à la variable précedente
					backtrack = 1;
					printf("backtracking");
					break;
				}
				else if(contrainte_enfreinte) //On assigne une autre valeur du domaine à la variable var, car la courante ne satisfait pas
					continue;
				
				if(var == csp->var_length - 1)//Solution trouvé
					return 1;
				
				/*
				//Application du forwardchecking ici
				//Pour chaque variable non instancié partageant une contrainte avec var on va filtrer leur domaine
				for(int contr = var + 1; contr < csp->var_length; contr++) // pour chaque contrainte non instancié : donc var + 1
				{
					tuples = csp->contraintes[var][contr];
					
					if(tuples != NULL) // la variable i et contr partagent une contrainte
					{					
						//<filtrage du domaine de la variable contr>
						//Si le domaine de contr devient vide, l'assignation est mauvaise
							continue;
							// flag pour savoir si on a épuisé le domaine, on doit backtrack et pas continue;
							
						else
							break;					
					}
					
				}
				*/
			}			
		}//END val
		
	}//END var
}
