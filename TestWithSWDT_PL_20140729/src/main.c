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
 * mian.c: simple test application
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

#include "main.h"
//#include <xtime_l.h>
//#include <stdio.h>

//XAdcPs  XADCMonInst; //XADC
XScuGic Intc; //GIC
XGpioPs Gpio; //GPIO
XScuWdt Wdt; //watchdog
XScuTimer Timer;//timer
//XUartPs XUart;

int nTimeRemain = 10; //the remain time for choice
int nStartTestFlag = 1;
int nTestType = 0;
//XTime t1,t2,t3,t4,t5,t6,t7,t8,t9;

int main()
{
    //Initial platform
	//只显示出错信息，图形用户界面显示出错数据保存，模块使用频率，综合应用程序，
    ExtraPlatformInit();
    //print tips
    /*print("\n\r********************************************************");
    print("\n\r********************************************************");
	print("\n\r***********       XJTU INT  SoC SEE TEST  ********** **");
	print("\n\r********************************************************");
	print("\n\r********************************************************\r\n");*/
	//XScuWdt_LoadWdt(&Wdt, WDT_LOAD_VALUE);

//	print("Please input your choice: \n\r0:Test CPU Reg\t 1:Test Cache\t 2:Test FPU\n\r3:Test ALU\t 4:Test Memory\t 5:Test Peripheral\t 6:Test ADC\t Others: Test All\n");
	int input;
	//start the Timer
	XScuTimer_Start(&Timer);
//	Delay();

//		printf("%d \n\r",XScuWdt_ReadReg(Wdt.Config.BaseAddr, XSCUWDT_LOAD_OFFSET));
//	read(0, input, 1);
//		printf("%d \n\r",XScuTimer_GetCounterValue(&Timer));
//	XScuTimer_Stop(&Timer);

//	PL_Test();
	//start the watchdog
	XScuWdt_LoadWdt(&Wdt, WDT_LOAD_VALUE);
	XScuWdt_Start(&Wdt);
	while(1)
	{
		//read UART
		UART_Read(&input);
//		int a=1,b=1,c=1,d=1,e=1,f=1,g=1,h=1;
		switch(input)
		{
//		case 'A':
		case TEST_TYPE_REGISTER:
//			while(nStartTestFlag)
//			{

//				printf("LOOP %d cpu test \n", a);
//				XTime_GetTime(&t1);
				CPURegister_Test();
//				XTime_GetTime(&t2);
//				long  clocks1=(t2-t1);
//				printf("CPU  Test diff clocks  = %ld\n", clocks1);

//				a++;
//				Delay();
//				XScuWdt_WriteReg(XPAR_SCUWDT_0_BASEADDR, XSCUWDT_LOAD_OFFSET, WDT_LOAD_VALUE);
				XScuWdt_LoadWdt(&Wdt, WDT_LOAD_VALUE);
//			}
			break;
//		case 'B':
		case TEST_TYPE_CACHE:
//			while(nStartTestFlag)
//			{
//				printf("LOOP%d cache test\n", b);
//				XTime_GetTime(&t1);
				Cache_Test();
//				XTime_GetTime(&t2);
//				long  clocks1=(t2-t1);
//				printf("cache  Test diff clocks  = %ld\n",clocks1);

//				b++;
//				Delay();
//				XScuWdt_WriteReg(XPAR_SCUWDT_0_BASEADDR, XSCUWDT_LOAD_OFFSET, WDT_LOAD_VALUE);
				XScuWdt_LoadWdt(&Wdt, WDT_LOAD_VALUE);
//			}
			break;
//		case 'C':
		case TEST_TYPE_FPU:
//			while(nStartTestFlag)
//			{
//				printf("LOOP%d fpu test \n", c);
//				XTime_GetTime(&t1);
				FPU_Test();
//				XTime_GetTime(&t2);
//				long  clocks1=(t2-t1);
//				printf("fpu  Test diff clocks  = %ld\n", clocks1);
//				c++;
//				Delay();
//				XScuWdt_WriteReg(XPAR_SCUWDT_0_BASEADDR, XSCUWDT_LOAD_OFFSET, WDT_LOAD_VALUE);
				XScuWdt_LoadWdt(&Wdt, WDT_LOAD_VALUE);
//			}
			break;
//		case 'D':
		case TEST_TYPE_ALU:
//			while(nStartTestFlag)
//			{
//				printf("LOOP%d alu test\n", d);
//				XTime_GetTime(&t1);
				ALU_Test();
//				XTime_GetTime(&t2);
//				long  clocks1=(t2-t1);
//				printf("alu  Test diff clocks  = %ld\n", clocks1);

//				d++;
//				Delay();
//				XScuWdt_WriteReg(XPAR_SCUWDT_0_BASEADDR, XSCUWDT_LOAD_OFFSET, WDT_LOAD_VALUE);
				XScuWdt_LoadWdt(&Wdt, WDT_LOAD_VALUE);
//			}
			break;
//		case 'E':
		case TEST_TYPE_MEMORY:
//			while(nStartTestFlag)
//			{
//				printf("LOOP%d memory test \n", e);
//				XTime_GetTime(&t1);
				Memory_Test();
//				XTime_GetTime(&t2);
//				long  clocks1=(t2-t1);
//				printf("mem  Test diff clocks  = %ld\n", clocks1);

//				e++;
//				Delay();
//				XScuWdt_WriteReg(XPAR_SCUWDT_0_BASEADDR, XSCUWDT_LOAD_OFFSET, WDT_LOAD_VALUE);
				XScuWdt_LoadWdt(&Wdt, WDT_LOAD_VALUE);
//			}
			break;
//		case 'F':
		case TEST_TYPE_PERIPHERAL:
//			while(nStartTestFlag)
//			{
//				printf("LOOP%d periph test\n", f);
//				XTime_GetTime(&t1);
				Peripheral_Test();
//				XTime_GetTime(&t2);

//				long  clocks1=(t2-t1);
//				printf("peripheral  Test diff clocks  = %ld\n", clocks1);
//				f++;


//				Delay();
				XScuWdt_LoadWdt(&Wdt, WDT_LOAD_VALUE);
//			}
			break;
		case TEST_TYPE_PL:
//			while(nStartTestFlag)
//			{
//				printf("LOOP %d pl test\n", g);
//				XTime_GetTime(&t1);
				PL_Test();
//				XTime_GetTime(&t2);
//				long  clocks1=(t2-t1);

//				printf("pl Test diff clocks  = %ld\n", clocks1);

//				g++;
//				Delay();
				XScuWdt_LoadWdt(&Wdt, WDT_LOAD_VALUE);
//			}
			break;
		case TEST_TYPE_ALL:
//			while(nStartTestFlag)
//			{
//				printf("LOOP %d  all test \n", h);
//				XTime_GetTime(&t1);
				TestAll();
//				XTime_GetTime(&t2);
//				long  clocks1=(t2-t1);
//				printf("testall  Test diff clocks  = %ld\n", clocks1);

//				h++;
//				Delay();
//				XScuWdt_WriteReg(XPAR_SCUWDT_0_BASEADDR, XSCUWDT_LOAD_OFFSET, WDT_LOAD_VALUE);
				XScuWdt_LoadWdt(&Wdt, WDT_LOAD_VALUE);
//			}
		}
		//one test circle complete
		UART_Write(2, 0, NULL, 0);
	}

	return 0;
}

void TestAll()
{
//	XTime_GetTime(&t1);
	CPURegister_Test();
	//usleep(10);
//	XTime_GetTime(&t2);
	Cache_Test();
//	 XTime_GetTime(&t3);
	//hello_icache();
//	XTime_GetTime(&t4);
	FPU_Test();
//	XTime_GetTime(&t5);
	ALU_Test();
//	XTime_GetTime(&t6);
	Memory_Test();
//	XTime_GetTime(&t7);
	Peripheral_Test();
//	XTime_GetTime(&t8);
	//long  clocks2=2*(t2-t1);
	//printf("clocks  = %ld\n", clocks2);
	PL_Test();
//	XTime_GetTime(&t9);
	/*long  clocks1=(t2-t1);
	long  clocks2=(t3-t2);
	long  clocks3=(t5-t3);
	long  clocks4=(t6-t5);
	long  clocks5=(t7-t6);
	long  clocks6=(t8-t7);
    long   clocks7=(t9-t8);
	printf("CPU  Test clocks  = %ld\n", clocks1);
	printf("Dcache Test clocks  = %ld\n", clocks2);
	printf("fpu Test clocks  = %ld\n", clocks3);
	printf("alu  Test clocks  = %ld\n", clocks4);
	printf("mem Test clocks  = %ld\n", clocks5);
	printf("Peri Test clocks= %ld\n", clocks6);
	printf("Pl Test clocks= %ld\n", clocks7);*/

}

void Delay(void)
{
	int i = 0;
	for( i = 0; i < LED_DELAY; i++);//wait
}
