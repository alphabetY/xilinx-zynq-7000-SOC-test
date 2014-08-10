/*
 * uart_com.c
 *
 *  Created on: 2014-7-26
 *      Author: Duran
 */
#include "uart_com.h"

/**
 * Initialize the UART
 * @param *pXUart instantce of XUart
 */
int UART_Init(XUartPs* pXUart)
{
	//the config of UART
	XUartPs_Config *pXUart_Config;
	//Lookup the config for UART
	pXUart_Config = XUartPs_LookupConfig(UART_DEVICE_ID);
	//set the boudrate
	pXUart->BaudRate = UART_BAUDRATE_NOR;
	//save the status of Init
	int status;
	//init the config
	status = XUartPs_CfgInitialize(pXUart, pXUart_Config, pXUart_Config->BaseAddress);
	if (status != XST_SUCCESS)
	{
//		print("UART INIT FAILED\n\r");
		return XST_FAILURE;
	}
	//enable the UART
	XUartPs_EnableUart(pXUart);
	//return true
	return 1;
}

/**
 * Send the data to the UART using the pre-defined protocol
 *
 */
void UART_Write(int testType, int status, char* valueBuf, unsigned int bufLength)
{
	//define the send buffer
	char sendBuf[SEND_BUF_SIZE] = {0};
	//init the protocal
	sendBuf[0] = (char) testType;
	sendBuf[1] = (char) status;
	//calculate the data length
	sendBuf[2] = (char) bufLength;
	//convert the type to bytes
	int i;
	for(i = 0; i < sendBuf[2]; i++)
	{
		sendBuf[i + 3] = valueBuf[i];
	}
	//send the buffer to the UART
	write(UART_DEVICE_ID, sendBuf, SEND_BUF_SIZE);
}

/**
 * Receive the data from the UART using the pre-defined protocol
 */
void UART_Read(char* valueBuf)
{
	//define the receive buffer
	char recvBuf[RECV_BUF_SIZE] = {0};
	//receive from UART
	read(UART_DEVICE_ID, recvBuf, RECV_BUF_SIZE);
	//convert to valueBuf
	int i;
	for(i = 0; i < RECV_BUF_SIZE; i++)
	{
		valueBuf[i] = recvBuf[i];
	}
}

/**
 * Convert the Origin Type buf to byte buffer
 */
/*void ConvertToBytes(int typeLength, char* datas, int dataLength, char* resultBuf)
{
	int i;

	for(i = 0; i < dataLength; i++)
	{//for the variable in the buffer
		for(j = 0; j < typeLength; j++)
		{//for one variable
			resultBuf[j] = datas[i];
		}
	}
}*/
/**
 * Notify the PC via UART of the success of the test
 */
void UART_Success(int testType)
{
	UART_Write(testType, TEST_SUCCESS, NULL, 0);
}

/**
 * Notify the PC via UART of the success of the test
 */
void UART_SuccessWithInfo(int testType, char* valueBuf, unsigned int bufLength)
{
	UART_Write(testType, TEST_SUCCESS, valueBuf, bufLength);
}

/**
 * Notify the PC via UART of the failure of the test
 */
void UART_Fail(int testType, char* valueBuf, unsigned int bufLength)
{
	UART_Write(testType, TEST_FAIL, valueBuf, bufLength);
}

/**
 * Get data type length
 */
int UART_GetTypeLength(int dataType)
{
	int typeLength;
	switch(dataType)
	{
	case DATA_TYPE_UINT16:
		typeLength = sizeof(unsigned short);
		break;
	case DATA_TYPE_INT16:
		typeLength = sizeof(short);
		break;
	case DATA_TYPE_UINT32:
		typeLength = sizeof(unsigned long);
		break;
	case DATA_TYPE_INT32:
		typeLength = sizeof(long);
		break;
	case DATA_TYPE_FLOAT:
		typeLength = sizeof(float);
		break;
	case DATA_TYPE_DOUBLE:
		typeLength = sizeof(double);
		break;
	case DATA_TYPE_BYTE:
		typeLength = sizeof(char);
	}
	return typeLength;
}

/**
 * transfer other value type to byte array
 */
void UART_ToBytes(int dataType, char* value, char* dataBuf, unsigned short offset)
{
	//get type length
	int typeLength = UART_GetTypeLength(dataType);
	int i;
	//transfer
	for(i = 0; i < typeLength; i++)
	{
		dataBuf[offset + i] = value[i];
	}
}
