#ifndef FORWARDCHECKING_MD_DEFINE_H
#define FORWARDCHECKING_MD_DEFINE_H

#include "util.h"
#include "pile.h"

int forward_checking_md(CSP * csp);

int choisir_variable_md(CSP * csp, int domaines[VARIABLE_MAX][VALEUR_MAX]);

void filtrer_domaine_md(CSP * csp, int domaines[VARIABLE_MAX][VALEUR_MAX], int var_assigne, int val_assigne);

int domaines_vide_md(CSP * csp, int domaines[VARIABLE_MAX][VALEUR_MAX]);

#endif //FORWARDCHECKING_MD_DEFINE_H

