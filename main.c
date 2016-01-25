/**
 * Main function of the test suite
 * Author: Jens Nelke
 * Company: Brunel Communications
 * Date: 25.01.2016
 */

#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include "sds.h"
#include "testcases.h"

int main(int argc, const char* argv[])
{
    int error = 0;
    printf("\nTesting with CMocka\n\n");

    if (0 == argc)
    {
        if (argv != NULL)
        {

        }
    }
    error = runTestCases();
    if (0 != error)
    {
        printf("Running tests failed!");
    }
    return error;
}
