#include "util.h"
#include "generators.h"
#include "forward-checking.h"
#include "backtrack.h"
#include "forward-checking-md.h"
#include "backjumping.h"
#include "csp_output.h"
#include <time.h>

int main()
{
    CSP csp;
    int r;
    clock_t debut, fin;
    clock();

    generate_dames(8, &csp);

    debut = clock();
    r = backjumping(&csp);
    fin = clock();
    printf("Backjump termine en %f sec\n", (float) (fin - debut) / CLOCKS_PER_SEC);
    
    printf("\nOn denombre %d solutions au CSP\n", r);

    free_CSP(&csp);


	return 0;
}
