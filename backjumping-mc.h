#ifndef BACKJUMPING_MC_DEFINE_H
#define BACKJUMPING_MC_DEFINE_H

#include "util.h"
#include "pile.h"

int backjumping_mc(CSP * csp);

int assignation_enfreint_contraintes_bjh(int var_curr, int val_curr, CSP *csp,int tab_tour[]);

int nb_assignation_enfreint_contraintes(int var_curr, CSP *csp);

int choisir_var(CSP * csp);

#endif // BACKJUMPING_MC_DEFINE_H
