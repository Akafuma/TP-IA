#ifndef GENERATORS_H_DEFINED
#define GENERATORS_H_DEFINED

#include "util.h"
#include <stdlib.h>
#include <stdio.h>

CSP * generate_pigeons(int n);

CSP * generate_dames(int n);

void free_CSP(CSP * csp);

#endif // GENERATORS_H_DEFINED
