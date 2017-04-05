
#ifndef BACKJUMPINGH_DEFINE_H
#define BACKJUMPINGH_DEFINE_H

#include "util.h"
#include "pile.h"
#include "csp_output.h"
int backjumping_h(CSP * csp);

int assignation_enfreint_contraintes_bjh(int var_curr, int val_curr, CSP *csp);
int nb_assignation_enfreint_contraintes(int var_curr, CSP *csp);
int choisir_var(CSP * csp);
#endif // BACKJUMPINGH_DEFINE_H
