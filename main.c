#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include "dut.h"
#include "testcases.h"

int main(int argc, const char* argv[])
{
    int error = 0;
    printf("\nTesting with CUnit\n\n");

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
