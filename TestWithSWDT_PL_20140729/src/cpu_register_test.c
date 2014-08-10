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
 * cpu_register_test.c: test the cpu's registers.
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
 *
 *   Author		Operation		Date
 *   Duran		Edit		2014-7-3
 */

#include <stdio.h>
#include <unistd.h>
//#include "platform.h"
#include "common.h"
//define the result size
#define RESULT_SIZE 9

/**
 * The function test the cpu registers.
 */
int CPURegister_Test()
{
	int isSuccess = TEST_SUCCESS;
	unsigned long i, expectedResult, result;//result used to record the result from register
	expectedResult = 255;
	result = 0;
	/* __asm("MOV r0, #255");
		__asm("MOV r1, #255");
		__asm("MOV r2, #255");
		__asm("MOV r3, #255");
	    __asm("MOV r4, #255");
	    __asm("MOV r5, #255");
	    __asm("MOV r6, #255");
	   	__asm("MOV r7, #255");
	   	__asm("MOV r8, #255");
	    __asm("MOV r9, #255");
	    __asm("MOV r10, #255");
	    __asm("MOV r12, #255");
	    __asm("MOV r14, #255");

	    //usleep(t);
	    __asm("STR r0,%0":"=m"(a));
	      printf("r 0=%10x\n\r",a);
		   // usleep(t);
	    __asm("STR r1,%0":"=m"(a));
	      printf("r 1=%10x\n\r",a);
		   // usleep(t);
	    __asm("STR r2,%0":"=m"(a));
	      printf("r 2=%10x\n\r",a);
		   // usleep(t);
	    __asm("STR r3,%0":"=m"(a));
	       printf("r 3=%10x\n\r",a);
		   // usleep(t);
	   __asm("STR r4,%0":"=m"(a));
	       printf("r 4=%10x\n\r",a);
		    //usleep(t);
	   __asm("STR r5,%0":"=m"(a));
	   	   printf("r 5=%10x\n\r",a);
		   // usleep(t);
	   __asm("STR r6,%0":"=m"(a));
	   	   printf("r 6=%10x\n\r",a);
		   // usleep(t);
	   __asm("STR r7,%0":"=m"(a));
	   	   printf("r 7=%10x\n\r",a);
		    //usleep(t);
	   __asm("STR r8,%0":"=m"(a));
	   	  printf("r 8=%10x\n\r",a);
		    //usleep(t);
	   __asm("STR r9,%0":"=m"(a));
	   	  printf("r 9=%10x\n\r",a);
		    //usleep(t);
	   __asm("STR r10,%0":"=m"(a));
	   	  printf("r10=%10x\n\r",a);
		    //usleep(t);
	   __asm("STR r12,%0":"=m"(a));
	   	  printf("r12=%10x\n\r",a);
		    //usleep(t);
	   __asm("STR r14,%0":"=m"(a));
	   	 printf("r14=%10x\n\r",a);*/

#if 0
	__asm("STR r0,%0":"=m"(result));
	printf("r0 = %10x, expected result = %10x\n\r", result, expectedResult);
	__asm("STR r1,%0":"=m"(result));
	printf("r1 = %10x, expected result = %10x\n\r", result, expectedResult);
	__asm("STR r2,%0":"=m"(result));
	printf("r2 = %10x, expected result = %10x\n\r", result, expectedResult);
	__asm("STR r3,%0":"=m"(result));
	printf("r3 = %10x, expected result = %10x\n\r", result, expectedResult);
	__asm("STR r4,%0":"=m"(result));
	printf("r4 = %10x, expected result = %10x\n\r", result, expectedResult);
	__asm("STR r5,%0":"=m"(result));
	printf("r5 = %10x, expected result = %10x\n\r", result, expectedResult);
	__asm("STR r6,%0":"=m"(result));
	printf("r6 = %10x, expected result = %10x\n\r", result, expectedResult);
	__asm("STR r7,%0":"=m"(result));
	printf("r7 = %10x, expected result = %10x\n\r", result, expectedResult);
	__asm("STR r8,%0":"=m"(result));
	printf("r8 = %10x, expected result = %10x\n\r", result, expectedResult);
	__asm("STR r9,%0":"=m"(result));
	printf("r9 = %10x, expected result = %10x\n\r", result, expectedResult);
	__asm("STR r10,%0":"=m"(result));
	printf("r10 = %10x, expected result = %10x\n\r", result, expectedResult);
	__asm("STR r11,%0":"=m"(result));
	printf("r11 = %10x, expected result = %10x\n\r", result, expectedResult);
	__asm("STR r12,%0":"=m"(result));
	printf("r12 = %10x, expected result = %10x\n\r", result, expectedResult);
	__asm("STR r13,%0":"=m"(result));
	printf("r13 = %10x, expected result = %10x\n\r", result, expectedResult);
	__asm("STR r14,%0":"=m"(result));
	printf("r14 = %10x, expected result = %10x\n\r", result, expectedResult);
#endif
	//define the result array
	char results[RESULT_SIZE] = {0};
	UART_ToBytes(DATA_TYPE_UINT32, &expectedResult, results, 1);
	UART_ToBytes(DATA_TYPE_UINT32, &result, results, 5);
	__asm("LDR r0, %0" : :"m"(expectedResult));
//	usleep(2);
	__asm("STR r0,%0":"=m"(result));
//	printf("r0 = %10x, expected result = %10x\n\r", result, expectedResult);
	if(result != expectedResult)
	{
		isSuccess = TEST_FAIL;
		results[0] = REG_R0;
		UART_Fail(TEST_TYPE_REGISTER, results, RESULT_SIZE);
	}

	result = 0;
	__asm("LDR r1, %0" : :"m"(expectedResult));
//	usleep(2);
	__asm("STR r1,%0":"=m"(result));
//	printf("r1 = %10x, expected result = %10x\n\r", result, expectedResult);
	if(result != expectedResult)
	{
		isSuccess = TEST_FAIL;
		results[0] = REG_R1;
		UART_Fail(TEST_TYPE_REGISTER, results, RESULT_SIZE);
	}


	result = 0;
	__asm("LDR r2, %0" : :"m"(expectedResult));
//	usleep(2);
	__asm("STR r2,%0":"=m"(result));
//	printf("r2 = %10x, expected result = %10x\n\r", result, expectedResult);
	if(result != expectedResult)
	{
		isSuccess = TEST_FAIL;
		results[0] = REG_R2;
		UART_Fail(TEST_TYPE_REGISTER, results, RESULT_SIZE);
	}

	result = 0;
	__asm("LDR r3, %0" : :"m"(expectedResult));
//	usleep(2);
	__asm("STR r3,%0":"=m"(result));
//	printf("r3 = %10x, expected result = %10x\n\r", result, expectedResult);
	if(result != expectedResult)
	{
		isSuccess = TEST_FAIL;
		results[0] = REG_R3;
		UART_Fail(TEST_TYPE_REGISTER, results, RESULT_SIZE);
	}

	result = 0;
	__asm("LDR r4, %0" : :"m"(expectedResult));
//	usleep(2);
	__asm("STR r4,%0":"=m"(result));
//	printf("r4 = %10x, expected result = %10x\n\r", result, expectedResult);
	if(result != expectedResult)
	{
		isSuccess = TEST_FAIL;
		results[0] = REG_R4;
		UART_Fail(TEST_TYPE_REGISTER, results, RESULT_SIZE);
	}

	result = 0;
	__asm("LDR r5, %0" : :"m"(expectedResult));
//	usleep(2);
	__asm("STR r5,%0":"=m"(result));
//	printf("r5 = %10x, expected result = %10x\n\r", result, expectedResult);
	if(result != expectedResult)
	{
		isSuccess = TEST_FAIL;
		results[0] = REG_R5;
		UART_Fail(TEST_TYPE_REGISTER, results, RESULT_SIZE);
	}

	result = 0;
	__asm("LDR r6, %0" : :"m"(expectedResult));
//	usleep(2);
	__asm("STR r6,%0":"=m"(result));
//	printf("r6 = %10x, expected result = %10x\n\r", result, expectedResult);
	if(result != expectedResult)
	{
		isSuccess = TEST_FAIL;
		results[0] = REG_R6;
		UART_Fail(TEST_TYPE_REGISTER, results, RESULT_SIZE);
	}

	result = 0;
	__asm("LDR r7, %0" : :"m"(expectedResult));
//	usleep(2);
	__asm("STR r7,%0":"=m"(result));
//	printf("r7 = %10x, expected result = %10x\n\r", result, expectedResult);
	if(result != expectedResult)
	{
		isSuccess = TEST_FAIL;
		results[0] = REG_R7;
		UART_Fail(TEST_TYPE_REGISTER, results, RESULT_SIZE);
	}

	result = 0;
	__asm("LDR r8, %0" : :"m"(expectedResult));
//	usleep(2);
	__asm("STR r8,%0":"=m"(result));
//	printf("r8 = %10x, expected result = %10x\n\r", result, expectedResult);
	if(result != expectedResult)
	{
		isSuccess = TEST_FAIL;
		results[0] = REG_R8;
		UART_Fail(TEST_TYPE_REGISTER, results, RESULT_SIZE);
	}

	result = 0;
	__asm("LDR r9, %0" : :"m"(expectedResult));
//	usleep(2);
	__asm("STR r9,%0":"=m"(result));
//	printf("r9 = %10x, expected result = %10x\n\r", result, expectedResult);
	if(result != expectedResult)
	{
		isSuccess = TEST_FAIL;
		results[0] = REG_R9;
		UART_Fail(TEST_TYPE_REGISTER, results, RESULT_SIZE);
	}

	result = 0;
	__asm("LDR r10, %0" : :"m"(expectedResult));
//	usleep(2);
	__asm("STR r10,%0":"=m"(result));
//	printf("r10 = %10x, expected result = %10x\n\r", result, expectedResult);
	if(result != expectedResult)
	{
		isSuccess = TEST_FAIL;
		results[0] = REG_R10;
		UART_Fail(TEST_TYPE_REGISTER, results, RESULT_SIZE);
	}
	//__asm("MOV r11, #255");
	//usleep(2);
	//	__asm("STR r11,%0":"=m"(a));
	//	printf("r11=%10x\n\r",a);
	/*result = 0;
	__asm("LDR r11, %0" : :"m"(expectedResult));
	usleep(2);
	__asm("STR r11,%0":"=m"(result));
	printf("r11 = %10x, expected result = %10x\n\r", result, expectedResult);*/

	result = 0;
	__asm("LDR r12, %0" : :"m"(expectedResult));
//	usleep(2);
	__asm("STR r12,%0":"=m"(result));
//	printf("r12 = %10x, expected result = %10x\n\r", result, expectedResult);
	if(result != expectedResult)
	{
		isSuccess = TEST_FAIL;
		results[0] = REG_R12;
		UART_Fail(TEST_TYPE_REGISTER, results, RESULT_SIZE);
	}
	/*__asm("MOV r14, #255");
	usleep(2);
	__asm("STR r14,%0":"=m"(a));
	printf("r14=%10x\n\r",a);*/
	if(isSuccess == TEST_SUCCESS)
		UART_Success(TEST_TYPE_REGISTER);

	return 0;
 }
