/* configNet.h - network configuration header */

/*
 * Copyright (c) 2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* Copyright (C) 2006 Tundra Semiconductor */

/*
modification history
--------------------
01a,13jul06,avb  adopted from hpc2-7448/configNet.h
*/
 
#ifndef INCnetConfigh
#define INCnetConfigh

#ifdef __cplusplus
extern "C" {
#endif

#ifdef INCLUDE_NETWORK /* ignore everything if NETWORK not included */

#include <vxWorks.h>
#include "config.h"
#include <end.h>

#define TSI108_LOAD_FUNC tsi108EndLoad
  
#define TSI108_BUFF_LOAN   1

#define SYS_END_BUFF_LOAN_PRI   1
#define SYS_END_BUFF_LOAN_SEC   2

#ifdef INCLUDE_GEI8254X_END
#define END_LOAD_FUNC_PRI       sysGei8254xEndLoad
#define END_BUFF_LOAN_PRI       SYS_END_BUFF_LOAN_PRI   
#define END_LOAD_FUNC_SEC       sysGei8254xEndLoad
#define END_BUFF_LOAN_SEC       SYS_END_BUFF_LOAN_SEC   
IMPORT END_OBJ * sysGei8254xEndLoad (char *, void *);
#endif

/* The END_LOAD_STRING is defined empty and created dynamicaly */

#define END_LOAD_STRING ""      /* created in sys<device>End.c */


#if defined(INCLUDE_PRIMARY_GEI_END)
IMPORT END_OBJ * END_LOAD_FUNC_PRI (char *, void*);
#endif
#if defined(INCLUDE_SECONDARY_GEI_END)
IMPORT END_OBJ * END_LOAD_FUNC_SEC (char *, void*);
#endif

/* <devNum>:<portRegAdrs>:<phyRegAdrs>:<phyMiiAdrs>:<intNum> */

/* load string for port0 */
#define	TSI108_LOAD_STRING	"0:0xc0006000:0xc0006000:1:16"
/* load string for port1 */
#define	TSI108_LOAD_STRING1	"1:0xc0006400:0xc0006000:2:17"

IMPORT END_OBJ * TSI108_LOAD_FUNC ();

END_TBL_ENTRY endDevTbl [] =
    {
#ifdef INCLUDE_PRIMARY_GIGE
      { 0, TSI108_LOAD_FUNC, TSI108_LOAD_STRING, TSI108_BUFF_LOAN, NULL, FALSE},
#endif
#ifdef INCLUDE_SECONDARY_GIGE
      { 1, TSI108_LOAD_FUNC, TSI108_LOAD_STRING1, TSI108_BUFF_LOAN, NULL, FALSE},
#endif /* INCLUDE_SECONDARY_GIGE */
#ifdef INCLUDE_PRIMARY_GEI_END
    {0, END_LOAD_FUNC_PRI, END_LOAD_STRING, END_BUFF_LOAN_PRI, NULL},
#endif
#ifdef INCLUDE_SECONDARY_GEI_END
    {1, END_LOAD_FUNC_SEC, END_LOAD_STRING, END_BUFF_LOAN_SEC, NULL},
#endif
      { 0, END_TBL_END, NULL, 0, NULL, FALSE},
    };

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_NETWORK */
#endif /* INCnetConfigh */
