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
 * alu_test.c: simple test application
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
 *   Duran		Add/Edit		2014-7-1
 *   Duran		Edit			2014-7-6
 */
//#include "stdio.h"
//#include "platform.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "common.h"

//define the result for uart out
#define RESULT_SIZE 8
char ALUResults[RESULT_SIZE] = {0};

//function def
int Test_Arithmeth();
int Test_Logic();
int Test_ScienceArith();
long Factorial(long n);
int Test_All();

/**
 * The function test the alu.
 */
void ALU_Test()
{
	/*int a=5,b=2,m,n,s,t,p;
	m=a-b;
	n=a+b;
	s=((m|n)^(m&&n));
	t=(m*(n>>2));
	p=s&t;
	printf("a  =%d\n\r",p);*/
	if(Test_All() == TEST_SUCCESS)
		UART_Success(TEST_TYPE_ALU);
}

/**
 * The function test the arithmometer of the alu
 * The expression is Result = (a - b + c) * d / e
 */
int Test_Arithmeth(){
	long a, b, c, d, e, expectedResult, calculatedResult;
	int isSuccess = TEST_SUCCESS;
	a = 5;
	b = 10;
	c = 13;
	d = 7;
	e = 3;
	expectedResult = 18;//(5 - 10 + 13) * 7 / 3
	calculatedResult = (a - b + c) * d / e;
//	printf("Input number a = %d, b = %d, c = %d, d = %d, e = %d, (a - b + c) * d / e = %d, expected result = %d\n\r", a, b, c, d, e, calculatedResult, expectedResult);
	if(expectedResult != calculatedResult)
	{
		isSuccess = TEST_FAIL;
		UART_ToBytes(DATA_TYPE_INT32, &expectedResult, ALUResults, 0);
		UART_ToBytes(DATA_TYPE_INT32, &calculatedResult, ALUResults, 4);
		UART_Fail(TEST_TYPE_ALU, ALUResults, RESULT_SIZE);
	}
	return isSuccess;
}

/**
 * The function test the logic operation
 * The expression is Result = !((a > b && c = d) || e <= f) && g != a
 */
int Test_Logic(){
	uint a, b, c, d, e, f, g, expectedResult, calculatedResult;
	int isSuccess = TEST_SUCCESS;
	a = 5;
	b = 4;
	c = 1;
	d = 8;
	e = 2;
	f = 9;
	g = 10;
	expectedResult = 0;//!((1 && 0) || 1) && 1
	calculatedResult = !((a > b && c == d) || e <= f) && g != a;
//	printf("Input number a = %d, b = %d, c = %d, d = %d, e = %d, f = %d, g = %d, !((a > b && c = d) || e <= f) && g != %d, expected result = %d\n\r", a, b, c, d, e, f, g, calculatedResult, expectedResult);
	if(expectedResult != calculatedResult)
	{
		isSuccess = TEST_FAIL;
		UART_ToBytes(DATA_TYPE_INT32, &expectedResult, ALUResults, 0);
		UART_ToBytes(DATA_TYPE_INT32, &calculatedResult, ALUResults, 4);
		UART_Fail(TEST_TYPE_ALU, ALUResults, RESULT_SIZE);
	}
	return isSuccess;
}

/**
 * The function test the science arithmatic
 * The expression is Result = sqrt(a!)
 */
int Test_ScienceArith(){
	int a, expectedResult, calculatedResult;
	int isSuccess = TEST_SUCCESS;
	a = 5;
	expectedResult = 10;//sqrt(120)
	calculatedResult = sqrt(Factorial(5));
//	printf("Input number a = %d, sqrt(a!) = %d, expected number = %d\n", a, calculatedResult, expectedResult);
	if(expectedResult != calculatedResult)
	{
		isSuccess = TEST_FAIL;
		UART_ToBytes(DATA_TYPE_INT32, &expectedResult, ALUResults, 0);
		UART_ToBytes(DATA_TYPE_INT32, &calculatedResult, ALUResults, 4);
		UART_Fail(TEST_TYPE_ALU, ALUResults, RESULT_SIZE);
	}
	return isSuccess;
}

/**
 * Calculate the n!
 * @param n number to be calculated
 * return n!
 */
long Factorial(long n){
	if(n == 0)
		return 1;
	else
		return n * Factorial(n-1);
}




/**
 *
 */
int Test_All(){

	return (Test_Arithmeth() == TEST_SUCCESS ||
				Test_Logic() == TEST_SUCCESS ||
				Test_ScienceArith() == TEST_SUCCESS);
}
