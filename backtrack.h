#ifndef BACKTRACK_DEFINE_H
#define BACKTRACK_DEFINE_H

#include "util.h"
#include "pile.h"

int backtrack(CSP * csp);

int assignation_enfreint_contraintes(int var_curr, int val_curr, CSP *csp);

#endif // BACKTRACK_DEFINE_H
