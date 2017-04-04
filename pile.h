#ifndef PILE_DEFINE_H
#define PILE_DEFINE_H

#include "util.h"
#include "stdio.h"

typedef struct Etat
{
    int num_var;
    int num_val;

    int domaines[VARIABLE_MAX][VALEUR_MAX]; // Pour forward checking
}Etat;

typedef struct Pile
{
    int taille;
    int top;
    Etat etats[VARIABLE_MAX];
}Pile;

void init_pile(int n, Pile * pile);

int pile_pleine(Pile * pile);

int pile_vide(Pile * pile);

void empile(int n_var, int n_val, Pile * pile);

Etat * depile(Pile * pile);

Etat * get_top(Pile * pile);

void print_pile(Pile * pile, CSP * csp);

void get_etat(Etat * e, int * n_var, int * n_val);

#endif // PILE_DEFINE_H
