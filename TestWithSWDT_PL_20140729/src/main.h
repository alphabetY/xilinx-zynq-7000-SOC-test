/******************************************************************************
*
*       XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"
*       AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND
*       SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,
*       OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,
*       APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION
*       THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,
*       AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE
*       FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY
*       WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE
*       IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR
*       REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF
*       INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*       FOR A PARTICULAR PURPOSE.
*
*       (c) Copyright 2009 Xilinx Inc.
*       All rights reserved.
*
******************************************************************************/
/*****************************************************************************/
/**
*
* @file main.h
*
* Defines the functions and includes the proper headers for the board_test_app.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a duran  04/22/2014 First release
* </pre>
*
******************************************************************************/

#ifndef MAIN_H_
#define MAIN_H_
/***************************** Include Files *********************************/

/*-------menu.h's old header--------start---*/
#include "xparameters.h"	/* defines XPAR values */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*-------menu.h's old header--------end---*/
/*-------test.c's old header--------start-*/
#include "stdio.h"
#include <ctype.h>
#include "xparameters.h"
#include "xil_printf.h"
#include "xil_cache.h"
#include "xtime_l.h"
/*-------test.c's old header--------end-*/
/*-------new header------------------start-*/
#include "common.h"
#include "xscuwdt_hw.h"
#include "xscuwdt.h"
#include "xscugic.h"
#include "xgpiops.h"
#include "xscutimer.h"
/*-------new header------------------end-*/

/************************** Constant Definitions ****************************/
#define LED_DELAY     100000000
/***************** Macros (Inline Functions) Definitions *********************/
// Macros to enable/disable caches.
#ifndef ENABLE_ICACHE
#define ENABLE_ICACHE()		Xil_ICacheEnable()
#endif
#ifndef	ENABLE_DCACHE
#define ENABLE_DCACHE()		Xil_DCacheEnable()
#endif
#ifndef	DISABLE_ICACHE
#define DISABLE_ICACHE()	Xil_ICacheDisable()
#endif
#ifndef DISABLE_DCACHE
#define DISABLE_DCACHE()	Xil_DCacheDisable()
#endif

/**************************** Type Definitions ******************************/

/************************** Function Prototypes *****************************/
extern int CPURegister_Test(void);
extern int Memory_Test(void);
extern int FPU_Test(void);
extern int ALU_Test(void);
extern int Cache_Test(void);
extern int Peripheral_Test(void);

void delay(void);
void testAll(void);

/************************** Variable Definitions ****************************/


#endif /* MAIN_H_ */
