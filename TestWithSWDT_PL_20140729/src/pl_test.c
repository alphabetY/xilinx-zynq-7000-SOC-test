/*
 * pl_test.c: test the PL
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
 *   Duran		Add				2014-7-8
 */
#include "pl_test.h"

#define RESULT_SIZE 8
/**
 * The function test the PL part
 */
void PL_Test()
{
//	XADC_Test();
	if(Adam_Peripheral_Test() == TEST_SUCCESS)
		UART_Success(TEST_TYPE_PL);
}

/**
 * The function test the ADC module
 */
/*void XADC_Test()
{
	//Get XADC pointer
	XAdcPs *XADCInstPtr = &XADCMonInst;

	//temperature readings
	u32 TempRawData;
	float TempData;//On-chip temperature

	//Vcc Int readings
	u32 VccIntRawData;
	float VccIntData;//The internal PL core voltage

	//Vcc Aux readings
	u32 VccAuxRawData;
	float VccAuxData;//The auxiliary PL voltage

	//Vbram readings
	u32 VBramRawData;
	float VBramData;//The PL BRAM voltage

	//VccPInt readings
	u32 VccPIntRawData;
	float VccPIntData;//The PS internal core voltage

	//VccPAux readings
	u32 VccPAuxRawData;
	float VccPAuxData;//The PS auxiliary voltage

	//Vddr readings
	u32 VDDRRawData;
	float VDDRData;//The operating voltage of the DDR RAM connected to the PS

	//print out the temperature
	printf("Following are tempurature of the board\n\r");

	TempRawData = XAdcPs_GetAdcData(XADCInstPtr, XADCPS_CH_TEMP);
	TempData = XAdcPs_RawToTemperature(TempRawData);
	printf("Raw Temp %lu Real Temp %f \n\r", TempRawData, TempData);

	VccIntRawData = XAdcPs_GetAdcData(XADCInstPtr, XADCPS_CH_VCCINT);
	VccIntData = XAdcPs_RawToVoltage(VccIntRawData);
	printf("Raw VccInt %lu Real VccInt %f \n\r", VccIntRawData, VccIntData);

	VccAuxRawData = XAdcPs_GetAdcData(XADCInstPtr, XADCPS_CH_VCCAUX);
	VccAuxData = XAdcPs_RawToVoltage(VccAuxRawData);
	printf("Raw VccAux %lu Real VccAux %f \n\r", VccAuxRawData, VccAuxData);

	//    VrefPRawData = XAdcPs_GetAdcData(XADCInstPtr, XADCPS_CH_VREFP);
	//    VrefPData = XAdcPs_RawToVoltage(VrefPRawData);
	//    printf("Raw VRefP %lu Real VRefP %f \n\r", VrefPRawData, VrefPData);

	//    VrefNRawData = XAdcPs_GetAdcData(XADCInstPtr, XADCPS_CH_VREFN);
	//    VrefNData = XAdcPs_RawToVoltage(VrefNRawData);
	//   printf("Raw VRefN %lu Real VRefN %f \n\r", VrefNRawData, VrefNData);

	VBramRawData = XAdcPs_GetAdcData(XADCInstPtr, XADCPS_CH_VBRAM);
	VBramData = XAdcPs_RawToVoltage(VBramRawData);
	printf("Raw VccBram %lu Real VccBram %f \n\r", VBramRawData, VBramData);

	VccPIntRawData = XAdcPs_GetAdcData(XADCInstPtr, XADCPS_CH_VCCPINT);
	VccPIntData = XAdcPs_RawToVoltage(VccPIntRawData);
	printf("Raw VccPInt %lu Real VccPInt %f \n\r", VccPIntRawData, VccPIntData);

	VccPAuxRawData = XAdcPs_GetAdcData(XADCInstPtr, XADCPS_CH_VCCPAUX);
	VccPAuxData = XAdcPs_RawToVoltage(VccPAuxRawData);
	printf("Raw VccPAux %lu Real VccPAux %f \n\r", VccPAuxRawData, VccPAuxData);

	VDDRRawData = XAdcPs_GetAdcData(XADCInstPtr, XADCPS_CH_VCCPDRO);
	VDDRData = XAdcPs_RawToVoltage(VDDRRawData);
	printf("Raw VccDDR %lu Real VccDDR %f \n\r", VDDRRawData, VDDRData);
}*/

/**
 * Test the PL with ax^2+bx+c expression calculation
 */
int Adam_Peripheral_Test()
{
	unsigned long expectedResults[10] = {33610, 33611, 33614, 33617, 33620, 33622, 33625, 33628, 33631, 33633};
	int isSuccess = TEST_SUCCESS;
	//results for uart out
	char results[RESULT_SIZE] = {0};
//    int Status;

    //先简单读入后写出；
	/*Status =  ADAMS_PERIPHERAL_Reg_SelfTest(XPAR_ADAMS_PERIPHERAL_0_S00_AXI_BASEADDR);
	if (Status != XST_SUCCESS) {
		xil_printf("Error: MYIP  failed\r\n");
	}
	else{
	xil_printf("MYIP selftest passed\r\n");
	}*/

    //test the expression ax^2+bx+c；
    unsigned long x;
    int i = 0;
	for(x = 0; x < 250; x = x + 25)
	{
		ADAMS_PERIPHERAL_mWriteReg(XPAR_ADAMS_PERIPHERAL_0_S00_AXI_BASEADDR, ADAMS_PERIPHERAL_S00_AXI_SLV_REG1_OFFSET, x);
		unsigned long result = ADAMS_PERIPHERAL_mReadReg(XPAR_ADAMS_PERIPHERAL_0_S00_AXI_BASEADDR, ADAMS_PERIPHERAL_S00_AXI_SLV_REG3_OFFSET);
//		printf("%lu\r\n", result);
		if(expectedResults[i] != result)
		{
			isSuccess = TEST_FAIL;
			UART_ToBytes(DATA_TYPE_UINT32, &expectedResults[i], results, 0);
			UART_ToBytes(DATA_TYPE_UINT32, &result, results, 4);
			UART_Fail(TEST_TYPE_PL, result, RESULT_SIZE);
		}
		i++;
	}
	return isSuccess;
}
