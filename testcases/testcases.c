#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdbool.h>

#include "testcases.h"
#include "sds.h"

bool useWrapped;
void simpleTest(void)
{
    useWrapped = true;
    sds name1 = "Klaus";
    sds name2 = "Klaus";
    will_return(__wrap_memcmp, 1);
    assert_int_equal(1, sdscmp(name1, name2));
    useWrapped = false;
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

