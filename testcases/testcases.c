/**
 * Test case implementation
 * Author: Jens Nelke
 * Company: Brunel Communications
 * Date: 25.01.2016
 */

#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdbool.h>

#include "testcases.h"
#include "sds.h"

/*With this flag triggers the usage of wrapped code.*/
bool useWrapped;

/**
 * First step using wrapped and mocked memcmp.
 *
 */
void simpleTest(void)
{
    useWrapped = true;
    /*Setting two equal strings*/
    sds name1 = "Klaus";
    sds name2 = "Klaus";
    /*Set mock to return 1 even if elements are equal
     * Number of values inserted into mock queue,
     * must match the number of values taken from the mock queue.
     * Otherwise cmocka will return an error
     */
    will_return(__wrap_memcmp, 1);
    /*Mock returns 1 for equal strings*/
    assert_int_equal(1, sdscmp(name1, name2));
    useWrapped = false;
}

/**
 * Sample testcase
 */
void simpleTest2(void)
{
    sds string = sdsempty();
    assert_int_equal(0, sdslen(string));
}

/**
 * Sample testcase
 */
void simpleTest3(void)
{
    sds string = sdsempty();
    sds string2 = sdscat(string,"Klaus");
    assert_int_equal(5, sdslen(string2));
}

/**
 * function is called by main it runs the tests.
 * @return error code for the tests run.
 */
int runTestCases()
{
    /**
     * Configures cmocka to write xml testreport as needed by Jenkins CI Server
     */
    const char* fileName = "./cmocka_out.xml";
    remove(fileName);
    setenv("CMOCKA_XML_FILE", fileName, 1);
    cmocka_set_message_output(CM_OUTPUT_XML);

    const struct CMUnitTest testcases1[] =
    {
    cmocka_unit_test(simpleTest),
    cmocka_unit_test(simpleTest2),
    cmocka_unit_test(simpleTest3) };

    return cmocka_run_group_tests_name("Sample Testcases", testcases1, NULL,
            NULL);
}

