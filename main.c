#include <stdio.h>
#include "dut.h"
#include "testcases.h"
#include "Basic.h"

int main( int argc, const char* argv[] )
{
   CU_ErrorCode error = CUE_SUCCESS;
	printf( "\nTesting with CUnit\n\n" );

	if(0 == argc)
	{
		if(argv != NULL)
		{

		}
	}
	error = setTestCases();
        if(error == CUE_SUCCESS)
        {
	   /* Run all tests using the CUnit Basic interface */
	   CU_basic_set_mode(CU_BRM_VERBOSE);
	   CU_basic_run_tests();
	   CU_cleanup_registry();
        }
return 0;
}
