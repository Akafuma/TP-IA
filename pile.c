#include "pile.h"

void init_pile(int n, Pile * pile)
{
    pile->taille = n;
    pile->top = -1;
}

int pile_pleine(Pile * pile)
{
    return (pile->top == pile->taille - 1);
}

int pile_vide(Pile * pile)
{
    return (pile->top == -1);
}

void empile(int n_var, int n_val, Pile * pile)
{
    if(pile_pleine(pile))
    {
        printf("Echec empilage, la pile est pleine\n");
        exit(EXIT_FAILURE);
    }

    pile->top++;
    pile->etats[pile->top].num_var = n_var;
    pile->etats[pile->top].num_val = n_val;
}

Etat * depile(Pile * pile)
{
    Etat * e;
    if(pile_vide(pile))
        return NULL;

    e = &pile->etats[pile->top--];
    return e;
}

Etat * get_top(Pile * pile)
{
    if(!pile_vide(pile))
        return &pile->etats[pile->top];
    return NULL;
}

void print_pile(Pile * pile, CSP * csp)
{
    printf("Une solution :\n\n");
    for(int i = 0; i < pile->taille; i++)
    {
        Etat * e = &pile->etats[i];
        int nvar, nval;
        get_etat(e, &nvar, &nval);

        printf("Variable %d affecte a %d\n", csp->variables[nvar], csp->valeurs[nval]);
    }
    printf("\n");
}

void get_etat(Etat * e, int * n_var, int * n_val)
{
    *n_var = e->num_var;
    *n_val = e->num_val;
}
