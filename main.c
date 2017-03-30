#include "util.h"
#include "generators.h"
#include "forward-checking.h"
#include "backtrack.h"
#include "forward-checking-md.h"
#include "csp_output.h"

int main()
{
    CSP csp;

    generate_dames(9, &csp);
    //generate_pigeons(8, &csp);
    //write_csp(&csp, "5-dames.txt");
    int r = forward_checking(&csp);
    //int r = backtrack(&csp);
    //int r = forward_checking_md(&csp);
    free_CSP(&csp);

    printf("\nOn denombre %d solutions au CSP\n", r);

	return 0;
}
