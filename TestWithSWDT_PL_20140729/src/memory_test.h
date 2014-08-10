/*****************************************************************************
*
* @file memory_test.h
*
* Defines the functions and includes the proper headers for the memory_test.c.
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

#ifndef __MEMORY_CONFIG_H_
#define __MEMORY_CONFIG_H_

/***************************** Include Files *********************************/
#include <stdio.h>
#include "xparameters.h"
#include "xil_types.h"
#include "xstatus.h"
#include "xil_testmem.h"
//#include "platform.h"
#include "xtime_l.h"
#include "common.h"
/************************** Constant Definitions ****************************/
#define	MEM_RANGE_LENGTH	1024	// define the testing memory length
#define	TEST_DATA_NUMBER	6	// define the testing data number
/**************************** Type Definitions ******************************/
struct memory_range_s {
    char *name;
    char *ip;
    unsigned base;	//testing mem.'s base address
    unsigned size;	//testing mem.'s rang length
};

/************************** Function Prototypes *****************************/


/************************** Variable Definitions ****************************/
struct memory_range_s memory_ranges[TEST_DATA_NUMBER];
int n_memory_ranges;

#endif/* MEMORY_TEST_H_ */
