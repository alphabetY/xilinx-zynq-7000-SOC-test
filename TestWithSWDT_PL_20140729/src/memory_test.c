/*
268173312 * Copyright (c) 2009 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A 
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR 
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION 
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE 
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO 
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO 
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE 
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY 
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 */
/*
 * memory_test.c: Test memory ranges present in the Hardware Design.
 *
 * This application runs with D-Caches disabled. As a result cacheline requests
 * will not be generated.
 *
 * For MicroBlaze/PowerPC, the BSP doesn't enable caches and this application
 * enables only I-Caches. For ARM, the BSP enables caches by default, so this
 * application disables D-Caches before running memory tests.
 */

#include "memory_test.h"
//#include "common.h"

//define the results for uart out
#define RESULT_SIZE 12

//define the results
char memResults[RESULT_SIZE] = {0};

//256k测试问题
struct memory_range_s memory_ranges[] = {
	/* ps7_qspi_linear_0 memory will not be tested since it is a flash memory */
	{
		"ps7_ddr_0",
		"ps7_ddr",
		XPAR_PS7_DDR_0_S_AXI_BASEADDR,
		MEM_RANGE_LENGTH,
	},
	/* ps7_ram_0 memory will not be tested since application resides in the same memory */
	{
		"ps7_ram_1",
		"ps7_ram",
		XPAR_PS7_RAM_1_S_AXI_BASEADDR,
		MEM_RANGE_LENGTH,
	},
};

/*****************************************************************************
*
* Perform a destructive 16-bit wide memory test.
*
* @param    Addr is a pointer to the region of memory to be tested.
* @param    Words is the length of the block.
* @param    Pattern is the constant used for the constant Pattern test, if 0,
*           0xDEADBEEF is used.
*
* @return
*
* - TEST_FAIL is returned for a failure
* - TEST_SUCCESS is returned for a pass
*
* @note
*
* Used for spaces where the address range of the region is smaller than
* the data width. If the memory range is greater than 2 ** Width,
* the patterns used in XIL_TESTMEM_WALKONES and XIL_TESTMEM_WALKZEROS will
* repeat on a boundry of a power of two making it more difficult to detect
* addressing errors. The XIL_TESTMEM_INCREMENT and XIL_TESTMEM_INVERSEADDR
* tests suffer the same problem. Ideally, if large blocks of memory are to be
* tested, break them up into smaller regions of memory to allow the test
* patterns used not to repeat over the region tested.
*
*****************************************************************************/
int TestMem16(u16 *Addr, u32 Words, u16 Pattern)
{
	u32 I;
	u32 J;
	u16 Val;
	u16 FirtVal;
	u16 Word;

	Xil_AssertNonvoid(Words != 0);

	/*
	 * variable initialization
	 */
	Val = XIL_TESTMEM_INIT_VALUE;
	FirtVal = XIL_TESTMEM_INIT_VALUE;

	/*
	 * Generate an initial value for
	 * memory testing
	 */

	if (Pattern == 0) {
		Val = 0xA55A;
	}
	else {
		Val = Pattern;
	}
	/*
	 * Fill the memory with fixed Pattern
	 */
	for (I = 0L; I < Words; I++) {
		/* write memory location */
		Addr[I] = Val;
	}
	/*
	 * Check every word within the words
	 * of tested memory and compare it
	 * with the fixed Pattern
	 */

	for (I = 0L; I < Words; I++) {
		/* read memory location */
		Word = Addr[I];
		if (Word != Val) {
			UART_ToBytes(DATA_TYPE_UINT16, &Word, memResults, 8);
			UART_Fail(TEST_TYPE_MEMORY, memResults, RESULT_SIZE);
			return TEST_FAIL;
		}
	}
	/* Successfully passed memory test ! */

	return TEST_SUCCESS;
}

int test_memory_range(struct memory_range_s *range)
{
    int isSuccess;
    //def. the tips
    char *ptesting_tips[TEST_DATA_NUMBER] = { "0xAAAA", "0x5555", "0xa5a5", "0x5a5a", "0x0000", "0xffff" };
    char *psuccess_tip = "PASSED!";
    char *pfailure_tip = "FAILED!";
    //def. the testing data
    u16 ntesting_datas[TEST_DATA_NUMBER] = { 0xAAAA, 0x5555, 0xa5a5, 0x5a5a, 0x0000, 0xffff };

    //status = Xil_TestMem32((u32*)range->base, 16256, 0xAAAA5555, XIL_TESTMEM_ALLMEMTESTS);
    //if (status == XST_SUCCESS)
             //printf("o1  =y\n\r");
    //uart
    UART_ToBytes(DATA_TYPE_UINT32, &range->base, memResults, 0);

    int i;
    for(i = 0; i < TEST_DATA_NUMBER; i++)
    {
//    	print("test data is: ");
//    	print(ptesting_tips[i]);
//    	print("\t");
    	//uart_start
    	UART_ToBytes(DATA_TYPE_UINT16, &ntesting_datas[i], memResults, 4);

    	isSuccess = TestMem16((u16*)range->base, range->size, ntesting_datas[i]);
    	/*if(isSuccess == TEST_SUCCESS)
    		UART_Success(TEST_TYPE_MEMORY);
    	else
    	{
    		UART_ToBytes(DATA_TYPE_UINT32, &range->base, results, 0);
    		UART_ToBytes(DATA_TYPE_UINT32, &ntesting_datas[i], results, 4);
    		UART_Fail(TEST_TYPE_MEMORY, results, RESULT_SIZE);
    	}*/
//    	print(status == XST_SUCCESS? psuccess_tip : pfailure_tip);
//    	print("\n\r");
    }
    return isSuccess;
}

/**
 * The function test the memory
 */
int Memory_Test()
{
	int isSuccess = TEST_SUCCESS;
	const int nmemory_ranges = 2;
    int i;
    for (i = 0; i < nmemory_ranges; i++)
    {
        if(test_memory_range(&memory_ranges[i]) == TEST_FAIL)
        	isSuccess = TEST_FAIL;
    }
    if(isSuccess == TEST_SUCCESS)
    	UART_Success(TEST_TYPE_MEMORY);

    return 0;
}
