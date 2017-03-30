#ifndef FORWARDCHECKINGTEST_DEFINE_H
#define FORWARDCHECKINGTEST_DEFINE_H

#include "util.h"
#include "pile.h"

int forward_checking(CSP * csp);

void filtrer_domaine(CSP * csp, int domaine[VARIABLE_MAX][VALEUR_MAX], int var_assigne, int val_assigne);

#endif //FORWARDCHECKING_DEFINE_H
