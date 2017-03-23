int BT(CSP * csp){

int i;
int continue=0;
int x,v,y,x_val,y_val;

int d[csp->var_length][csp->val_length];
int tab[csp->var_length];

if(var[0]==NULL)
    return(true);


else
{

    for(i=0;i<csp->var_length-1=;i++)
    {
        //x=csp->variables[i];
        d[i][0]=csp->variables[i]



        for(int j=0;j<csp->val_length;j++)
        {
            if(csp->domaines[i][j]==1)
            {
               // x_val=csp->valeurs[j];

                for(int k=0;k<csp->var_length;k++)
                {
                    if(csp->contraintes[x][k]==1)
                    {
                        remonte=k;
                        continue=1;
                        break;
                    }

                    continue=0;
                    d[i][j]=csp->valeurs[j]
                }
            }
            if(continue==0)
            {
                tab[i]=j
                break;
            }


        }

        if(continue==1)
        {
            i=remonte-1;
            j=tab[remonte];

        }


    }










}








}
