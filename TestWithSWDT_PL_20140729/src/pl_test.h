/*****************************************************************************
*
* @file pl_test.h
*
* Defines the functions and includes the proper headers for the PL test.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a duran  07/08/2014 First release
* </pre>
*
******************************************************************************/
#ifndef PL_TEST_H_
#define PL_TEST_H_

/***************************** Include Files *********************************/

#include "xparameters.h"	/* defines XPAR values */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xadcps.h"
#include "xil_types.h"
#include "xscugic.h"
#include "common.h"
#include "Adams_Peripheral.h"
/************************** Constant Definitions ****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/**************************** Type Definitions ******************************/

/************************** Function Prototypes *****************************/
void PL_Test();
void XADC_Test();
int Adam_Peripheral_Test();

/************************** Variable Definitions ****************************/
//extern XAdcPs  XADCMonInst; //XADC


#endif /* PL_TEST_H_ */
