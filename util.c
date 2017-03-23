#include "util.h"

int appartient_domaine(int var, int val, int domaines[VARIABLE_MAX][VALEUR_MAX])
{
	return domaines[var][val];
}
