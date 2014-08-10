/*
 * peripheral_test.c
 *
 *  Created on: May 28, 2014
 *      Author: Duran
 */
#include "peripheral_test.h"

//pre-compile info for uart
#define RESULT_SIZE 1

/**
 * The function test the peripheral. GIC, DMA, QSPI
 */
int Peripheral_Test()
{
	//define results for uart out
	char results[RESULT_SIZE];

    static XScuGic intc;

	int Status;

	//test the GIC
	results[0] = PERI_GIC;
	Status = ScuGicSelfTest(XPAR_PS7_SCUGIC_0_DEVICE_ID);
	if (Status == XST_SUCCESS) {
//		printf("General Interrupt Control test success!\n\r");
		UART_SuccessWithInfo(TEST_TYPE_PERIPHERAL, results, RESULT_SIZE);
	}
	else {
//		printf("General Interrupt Control test fail!\n\r");
		UART_Fail(TEST_TYPE_PERIPHERAL, results, RESULT_SIZE);
	}

	//setup GIC
	Status = ScuGicInterruptSetup(&intc, XPAR_PS7_SCUGIC_0_DEVICE_ID);
	/*if (Status == XST_SUCCESS) {
//		printf("General Interrupt Control init success!\n\r");
	}
	else {
//		printf("General Interrupt Control init fail!\n\r");
	}*/

	//test the DMA
	results[0] = PERI_DMA;
	Status = DMA_Test(&intc,XPAR_PS7_DMA_S_DEVICE_ID);
	if (Status == XST_SUCCESS) {
//		printf("DMA test success!\n\r");
		UART_SuccessWithInfo(TEST_TYPE_PERIPHERAL, results, RESULT_SIZE);
	}
	/*else {
//		printf("DMA test fail!\n\r");
	}*/

	//test the QSPI
	results[0] = PERI_QSPI;
	Status = QspiPsSelfTest(XPAR_PS7_QSPI_0_DEVICE_ID);
	if (Status == XST_SUCCESS) {
//		printf("QSPI test success!\n\r");
		UART_SuccessWithInfo(TEST_TYPE_PERIPHERAL, results, RESULT_SIZE);
	}
	else {
//		printf("QSPI test fail!\n\r");
		UART_Fail(TEST_TYPE_PERIPHERAL, results, RESULT_SIZE);
	}

   /*Peripheral Test will not be run for ps7_uart_1
     because it has been selected as the STDOUT device */

   return 0;
}

