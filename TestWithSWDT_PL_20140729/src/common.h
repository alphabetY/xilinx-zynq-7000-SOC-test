/*****************************************************************************
*
* @file common.h
*
* Defines the functions and includes and constants used in the project.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a duran  07/28/2014 First release
* </pre>
*
******************************************************************************/

#ifndef __COMMON_H_
#define __COMMON_H_

/***************************** Include Files *********************************/
#include "uart_com.h"

/************************** Constant Definitions ****************************/
#define TEST_SUCCESS 1
#define TEST_FAIL 0
//XADC
#define XPAR_AXI_XADC_0_DEVICE_ID 0

//GPIO
#define GPIO_DEVICE_ID		XPAR_XGPIOPS_0_DEVICE_ID
#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID
#define GPIO_INTERRUPT_ID	XPS_GPIO_INT_ID

//Timer
#define TIMER_DEVICE_ID		XPAR_XSCUTIMER_0_DEVICE_ID
//#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID
#define TIMER_IRPT_INTR		XPAR_SCUTIMER_INTR
#define TIMER_LOAD_VALUE	0x20000000


//Watchdog
#define WDT_DEVICE_ID         XPAR_SCUWDT_0_DEVICE_ID
//#define INTC_DEVICE_ID        XPAR_SCUGIC_SINGL_DEVICE_ID
#define WDT_IRPT_INTR         XPAR_SCUWDT_INTR
#define WDT_LOAD_VALUE        0xFFFFFFFF
/**************************** Type Definitions ******************************/


/************************** Function Prototypes *****************************/


/************************** Variable Definitions ****************************/

#endif/* MEMORY_TEST_H_ */
