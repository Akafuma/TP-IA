int BT(CSP * csp){

int i,j;
int bj=0;
int EMPILE; 
int nb_sol = 0;

Pile p;
init_pile(cs⁻>var_length, &p);
int temp_domaines[VARIABLE_MAX][VALEUR_MAX];
domaines_copie(temp_domaines, csp->domaines, csp);
	
int d[csp->var_length]={0};
int tab[csp->val_length];
int modif[csp->var_length]={0};

int **tuples=NULL;

	




for(i=0;i<csp->var_length-1=;i++)  // on choisit la variable
{
	if(modif[i]==1)   // tester plutot si on a deja fait un domaine

	for(j=0;j<csp->val_length;j++) // on choisit une valeur
    {
		
		if(csp->domaines[i][j]==1) // si la valeur appartient au domaine
        {
            d[i]=csp->valeurs[i];   // assignation
			for(int k=0;k<i;k++) // on parcourt les var deja assignées
            {
				if(csp->contraintes[i][k]!=NULL) // si il y a une contrainte on verifie qu'elle ne soit pas enfreinte
                {
					tuples=csp->contraintes[i][k];
					if(tuples[i][d[k]])     // si tuple valide
					{
						bj=0;
						continue;
					}
					else   // sinon on prépare le backjump
					{
                        remonte=k;   // remonte prend la valeur de la variable qui partage la contrainte violée
                        bj=1;        // bj nous indique que l'on ne peut pas assigner une autre valeur pour l'instant
                        break;
					}

                //bj=0;
                //d[i][j]=csp->valeurs[j]
				}
			}
        if(bj==0)
        {
			tab[i]=j   // tab stocke la case du tableau de valeurs que l'on a choisit d'assigner
            break;
        }


		}

    /*if(bj==1)
    {
		i=remonte-1;
        j=tab[remonte];

    }*/


	}
	if(bj==1)
    {
		i=remonte-1;
        j=tab[remonte];
        modif[i]=1;

    }
	

}

for(int n=0 ; n<csp->var_length ; n++)
{
	if(d[i]==0)
	{
		printf("inconsistant");
		return (0);
	}
}

printf("consistant");
return (1);

}
