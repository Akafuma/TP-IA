#include "util.h"


//Renvoi le nombre de solutions du CSP
int forward_checking(CSP * csp)
{
	int started = 0; // FLAG
	int val_assigne[csp->var_length] = { 0 };
	int var_assigne[csp->var_length] = { 0 }; // boolean
	//faire un tableau socke l'indice de la val ou on s'est arreté avant de break; enfait c'est val_assigne je crois
	int val_current
	
	for(int var = 0; var < csp->var_length; var++) // On parcourt les variables dans l'ordre
	{
		if(started)
			return 0; // Pas de solution
		if(!started)
			started = 1;
		
		for(int val = 0; val < csp-->val_length; val++) // On parcourt toutes les valeurs, utiliser val_assigne plutot???
		{
			if(appartient_domaine(var, val, csp->domaines)) // La valeur val appartient au domaine de la variable var
			{
				val_assigne[var] = val; //on assigne val à var
				var_assigne[var] = 1; // on a assigné la variable var
				
				for(int contr = 0; contr < csp->var_length; contr++) // pour chaque contrainte
				{
					int ** tuples = csp->contraintes[var][contr];
					
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
			}			
		}//END val
		if(var_assigne[var] == 0) // Echec de l'affectation de la variable, on backtrack
			var - 1;
	}//END var
}
