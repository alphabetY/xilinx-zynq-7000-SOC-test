/*
 * uart_com.h
 *
 *  Created on: 2014-7-26
 *      Author: Duran
 */
/*****************************************************************************
*
* @file uart_com.h
*
* Defines the functions and includes the proper headers for the uart_com.c.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a duran  07/26/2014 First release
* </pre>
*
******************************************************************************/
#ifndef UART_COM_H_
#define UART_COM_H_

/***************************** Include Files *********************************/
#include "xuartps.h"
#include "unistd.h"
#include <stdio.h>
#include <stdlib.h>
#include "xil_types.h"
#include "xparameters.h"

/************************** Constant Definitions ****************************/
#define UART_BAUDRATE_NOR 115200
#define UART_DEVICE_ID 0
#define SEND_BUF_SIZE 20	//define the send buffer size
#define RECV_BUF_SIZE 1		//define the receive buffer size
//define the test type in the protocol
#define TEST_TYPE_HEARTBEAT 0
#define TEST_TYPE_WDTREBOOT 1
#define TEST_TYPE_CIRCLEOVER 2
#define TEST_TYPE_ALL 10
#define TEST_TYPE_REGISTER 11
#define TEST_TYPE_CACHE 12
#define TEST_TYPE_FPU 13
#define TEST_TYPE_ALU 14
#define TEST_TYPE_MEMORY 15
#define TEST_TYPE_PERIPHERAL 16
#define TEST_TYPE_PL 17
//define the data type int the protocol
#define DATA_TYPE_UINT16 0
#define DATA_TYPE_INT16 1
#define DATA_TYPE_UINT32 2
#define DATA_TYPE_INT32 3
#define DATA_TYPE_FLOAT 4
#define DATA_TYPE_DOUBLE 5
#define DATA_TYPE_BYTE 6
//define the register number
#define REG_R0 0
#define REG_R1 1
#define REG_R2 2
#define REG_R3 3
#define REG_R4 4
#define REG_R5 5
#define REG_R6 6
#define REG_R7 7
#define REG_R8 8
#define REG_R9 9
#define REG_R10 10
#define REG_R11 11
#define REG_R12 12
#define REG_R13 13
#define REG_R14 14
//define the peripheral of the test
#define PERI_GIC 0
#define PERI_DMA 1
#define PERI_QSPI 2
//define the status of the test
#define TEST_SUCCESS 1
#define TEST_FAIL 0
//define the DMA
//option
#define DMA_OPTION_CHANNEL 0
#define DMA_OPTION_DATA 1
//channel
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3
#define DMA_CHANNEL_4 4
#define DMA_CHANNEL_5 5
#define DMA_CHANNEL_6 6
#define DMA_CHANNEL_7 7
/***************** Macros (Inline Functions) Definitions *********************/

/**************************** Type Definitions ******************************/

/************************** Function Prototypes *****************************/
//void ConvertToBytes(int origBytes, void* datas, int dataLength, char* resultBuf);
void UART_Write(int testType, int status, char* valueBuf, unsigned int bufLength);
void UART_Read(char* valueBuf);
void UART_Success(int testType);
void UART_SuccessWithInfo(int testType, char* valueBuf, unsigned int bufLength);
void UART_Fail(int testType, char* valueBuf, unsigned int bufLength);
int UART_Init(XUartPs* pXUart);
int UART_GetTypeLength(int dataType);
void UART_ToBytes(int dataType, char* value, char* dataBuf, unsigned short offset);
/************************** Variable Definitions ****************************/
//extern XUartPs XUart;

#endif /* UART_COM_H_ */
