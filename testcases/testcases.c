#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

#include "testcases.h"
#include "sds.h"

void simpleTest(void)
{

    assert_int_equal(0, sdscmp("Klaus", "Klaus"));
}

void simpleTest2(void)
{
    sds string = sdsempty();
    assert_int_equal(0, sdslen(string));
}

void simpleTest3(void)
{
    sds string = sdsempty();
    sds string2 = sdscat(string,"Klaus");
    assert_int_equal(5, sdslen(string2));
}

int runTestCases()
{
    const char* fileName = "./cmocka_out.xml";
    remove(fileName);
    setenv("CMOCKA_XML_FILE", fileName, 1);
    cmocka_set_message_output(CM_OUTPUT_XML);

    const struct CMUnitTest testcases[] =
    {
    cmocka_unit_test(simpleTest),
    cmocka_unit_test(simpleTest2),
    cmocka_unit_test(simpleTest3) };

    return cmocka_run_group_tests_name("Sample Testcases", testcases, NULL,
            NULL);
}

