#ifndef __PPC_API_H__
#define __PPC_API_H__

#include "vxWorks.h"
#include "string.h"
#include "sysLib.h"
#include "stdlib.h"
#include "intLib.h"
#include "iv.h"
#include "semLib.h"
#include "assert.h"

#include "memPartLib.h"
#include "drv/pci/pciConfigLib.h"
#include "vmlib.h"
#include "logLib.h"


typedef struct tagEXT_INT_S
{
    SEM_ID    stIntSem;
    UINT32    uiIntChan;
    UINT32    uiIntAddr;
}EXT_INT_S;

extern EXT_INT_S gstExtInt;
extern EXT_INT_S gstPabackExtInt;
extern SEM_ID   timeIntSem;

extern VOID extIntInit(VOID);
#endif

