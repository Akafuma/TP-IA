
#ifndef BACKJUMPING_H_DEFINE_H
#define BACKJUMPING_H_DEFINE_H

#include "util.h"
#include "pile.h"

int backjumping_h(CSP * csp);
//int assignation_enfreint_contraintes_bjj(int var_curr, int val_curr, CSP *csp);
//int assignation_enfreint_contraintes_bj(int var_curr, int val_curr, CSP *csp);
int nb_assignation_enfreint_contraintes(int var_curr, CSP *csp);
int choisir_var(CSP * csp);
#endif // BACKJUMPING_H_DEFINE_H
