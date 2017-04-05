#ifndef BACKJUMPING_DEFINE_H
#define BACKJUMPING_DEFINE_H

#include "util.h"
#include "pile.h"
#include "csp_output.h"
int backjumping(CSP * csp);

int assignation_enfreint_contraintes_bj(int var_curr, int val_curr, CSP *csp);
#endif // BACKJUMPING_DEFINE_H
