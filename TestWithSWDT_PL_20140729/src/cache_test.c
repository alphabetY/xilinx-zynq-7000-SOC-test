/*
 * Copyright (c) 2009-2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * cache_test.c: Test cache
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include "stdio.h"
//#include "platform.h"

#include "xil_cache.h"
#include "xil_testcache.h"

#include "common.h"
//define the result size
#define RESULT_SIZE 8

extern void xil_printf(const char *ctrl1, ...);

#define DATA_LENGTH 128

static u32 Data[DATA_LENGTH];


/**
* Perform DCache all related API test such as Xil_DCacheFlush and
* Xil_DCacheInvalidate. This test function writes a constant value
* to the Data array, flushes the DCache, writes a new value, then invalidates
* the DCache.
*
* @return
*     - TEST_SUCCESS is returned for a pass
*     - TEST_FAIL is returned for a failure
*/
int TestDCacheRange(void)
{
	int Index;
	int Status;
	unsigned long testingData = 0xA0A00505;
	u32 Value;

//	xil_printf("----Cache Range Test --\n\r");

	//init the data array
	for (Index = 0; Index < DATA_LENGTH; Index++)
		Data[Index] = testingData;

//	xil_printf("    initialize Data done:\r\n");
	//flush data to cache
	Xil_DCacheFlushRange((u32)Data, DATA_LENGTH * sizeof(u32));

//	xil_printf("    flush range done\r\n");
	//modify the data array
	for (Index = 0; Index < DATA_LENGTH; Index++)
		Data[Index] = Index + 3;
	//invalidate dcache
	Xil_DCacheInvalidateRange((u32)Data, DATA_LENGTH * sizeof(u32));

//	xil_printf("    invalidate dcache range done\r\n");

	Status = TEST_SUCCESS;

	//define the result
	char results[RESULT_SIZE] = {0};
	UART_ToBytes(DATA_TYPE_UINT32, &testingData, results, 0);

	for (Index = 7; Index < DATA_LENGTH - 1; Index++) {
		Value = Data[Index];
		if (Value != testingData) {
			Status = TEST_FAIL;
//			xil_printf("Data[%d] = %x\r\n", Index, Value);
			UART_ToBytes(DATA_TYPE_UINT32, &testingData, results, 0);
			UART_ToBytes(DATA_TYPE_UINT32, &Value, results, 4);
			UART_Fail(TEST_TYPE_CACHE, results, RESULT_SIZE);
//			break;
		}
	}
	/*if (!Status) {
//		xil_printf("  ------ Invalidate worked\r\n");
		UART_Success(TEST_TYPE_CACHE);
	}*/
//	else {
//		xil_printf("Error: Invalidate dcache range not working\r\n");
//	}

//	xil_printf("-- Cache Range Test Complete --\r\n");
	return Status;
}

/**
* Perform Xil_ICacheInvalidateRange() on a few function pointers.
*
* @return
*
*     - TEST_SUCCESS is returned for a pass
*     The function will hang if it fails.
*/
int TestICacheRange(void)
{

	Xil_ICacheInvalidateRange((u32)Xil_TestICacheRange, 1024);
	Xil_ICacheInvalidateRange((u32)Xil_TestDCacheRange, 1024);
	Xil_ICacheInvalidateRange((u32)Xil_TestDCacheAll, 1024);

//	xil_printf("-- Invalidate icache range done --\r\n");

	return TEST_SUCCESS;
}

/**
* Perform Xil_ICacheInvalidate().
*
* @return
*
*     - TEST_SUCCESS is returned for a pass
*     The function will hang if it fails.
*/
int TestICacheAll(void)
{
	Xil_ICacheInvalidate();
//	xil_printf("-- Invalidate icache all done --\r\n");
	return TEST_SUCCESS;
}

int Cache_Test()
{

	//enable the cache
    Xil_ICacheEnable();
    Xil_DCacheEnable();

    //test data cache
    if(TestDCacheRange() == TEST_SUCCESS
    		|| TestICacheRange() == TEST_SUCCESS //test instruction cache
    		|| TestICacheAll() == TEST_SUCCESS)
    	UART_Success(TEST_TYPE_CACHE);

    return 0;
}


