/*****************************************************************************
*
* @file extra_platform_init.h
*
* Defines the functions and includes the proper headers for the extra_platform.c.
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


#ifndef EXTRA_PLATFORM_INIT_H_
#define EXTRA_PLATFORM_INIT_H_
/***************************** Include Files *********************************/
//#include "platform.h"
#include "xadcps.h"
#include "xgpiops.h"
#include "xil_types.h"
#include "xscugic.h"
#include "Xil_exception.h"
#include "xscutimer.h"
#include "xscuwdt.h"
#include "platform.h"
#include "common.h"
/***************** Macros (Inline Functions) Definitions *********************/
#define ledpin 47
#define pbsw 51

/************************** Function Prototypes *****************************/
void ExtraPlatformInit(void);
void SetupInterruptSystem(XScuGic *GicInstancePtr, XGpioPs *Gpio, u16 GpioIntrId,
		XScuTimer *TimerInstancePtr, XScuWdt *WdtInstancePtr, u16 TimerIntrId, u16 WdtIntrId);
void GPIOIntrHandler(void *CallBackRef, int Bank, u32 Status);
void TimerIntrHandler(void *CallBackRef);
void WdtIntrHandle(void *CallBackRef);
extern void TestAll(void);
extern void Delay(void);

/************************** Variable Definitions ****************************/
extern XAdcPs  XADCMonInst; //XADC
extern XScuGic Intc; //GIC
extern XGpioPs Gpio; //GPIO
extern XScuWdt Wdt; //watchdog
extern XScuTimer Timer;//timer
extern int nTimeRemain;
extern int nStartTestFlag;
extern int nTestType;

#endif /* EXTRA_PLATFORM_INIT_H_ */
