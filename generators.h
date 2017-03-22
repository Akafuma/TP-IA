#ifndef GENERATORS_H_DEFINED
#define GENERATORS_H_DEFINED

#include "util.h"
#include <stdlib.h>
#include <stdio.h>

void generate_pigeons(int n, CSP * csp);

void generate_dames(int n, CSP * csp);

void free_CSP(CSP * csp);

#endif // GENERATORS_H_DEFINED
