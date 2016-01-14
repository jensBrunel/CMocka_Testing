#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

#include "testcases.h"
#include "dut.h"

void simpleTest(void)
{

    assert_int_equal(2, funca(2));
}

void simpleTest2(void)
{

    assert_int_equal(2, funca(3));
}

void simpleTest3(void)
{

    assert_int_equal(1, funca(1));
}

int runTestCases()
{
    const struct CMUnitTest testcases[] =
    {
    cmocka_unit_test(simpleTest),
    cmocka_unit_test(simpleTest2),
    cmocka_unit_test(simpleTest3) };

    return cmocka_run_group_tests_name("Sample Testcases", testcases, NULL,
            NULL);
}

