#include "util.h"
#include "generators.h"
#include "forward-checking.h"
//#include "forward-checking-test.h"
#include "backtrack.h"
#include "forward-checking-md.h"
#include "csp_output.h"
#include <time.h>

int main()
{
    CSP csp;
    
    clock_t sec;

    //generate_dames(13, &csp);
    generate_pigeons(9, &csp);
    //write_csp(&csp, "5-dames.txt");
    sec = clock();
    //int r = forward_checking(&csp);    
    //int r = backtrack(&csp);
    //int r = forward_checking_md(&csp);
    printf("Termine en %f sec\n", (float) (clock() - sec) / CLOCKS_PER_SEC);
    free_CSP(&csp);

    printf("\nOn denombre %d solutions au CSP\n", r);

	return 0;
}
