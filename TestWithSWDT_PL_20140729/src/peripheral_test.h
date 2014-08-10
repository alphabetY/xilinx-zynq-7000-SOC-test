/*
 * @file peripheral_test.h
 *
 *  Created on: May 28, 2014
 *      Author: Duran
 */

#ifndef PERIPHERAL_TEST_H_
#define PERIPHERAL_TEST_H_

/***************************** Include Files *********************************/
#include "xscugic.h"
#include "xstatus.h"
#include "common.h"
/************************** Function Prototypes *****************************/

extern int ScuGicInterruptSetup(XScuGic *IntcInstancePtr, u16 DeviceId);
extern int XDmaPs_Example_W_Intr(XScuGic *GicPtr, u16 DeviceId);



#endif /* PERIPHERAL_TEST_H_ */
