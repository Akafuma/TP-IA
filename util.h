#ifndef UTIL_H_DEFINED
#define UTIL_H_DEFINED

typedef struct CSP
{
	int *variables;
	int *valeurs;
	int **domaines;
	int ****contraintes;	
} CSP;

#endif //UTIL_H_DEFINED
