/* sysDuart.h - MPC834x duart driver */

/* 
 * Copyright 1984-2006 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only persuant to the terms
 * of an applicable Wind River license agreement
 */

/* Copyright 1996, 1998 Motorola, Inc. */

/*
modification history
--------------------
01b,08mar06,kds  Fix XTAL code
01a,28feb05,dtr  created for MPC834x Duart device.
*/

/*
This file contains I/O addresses and related constants for the
MPC 834x Duart device.
*/

#ifndef	__INCsysDuarth
#define	__INCsysDuarth

#ifdef __cplusplus
extern "C" {
#endif

/* external variables */

/* Duart Port Defininitions */

#define COM1        		"/tyCo/0"             /* duart com port 1 */
#define COM2        		"/tyCo/1"             /* duart com port 2 */

#define COM1_MEM_BASE      	0x0500		      /* com3 pci mem offset */
#define COM2_MEM_BASE      	0x0600	 	      /* com4 pci mem offset */

#define COM1_LOCAL_MEM_BASE    	0x4500		      /* com3 local mem offset */
#define COM2_LOCAL_MEM_BASE    	0x4600	 	      /* com4 local mem offset */

#define COM1_ADR        	((ULONG) CCSBAR + (ULONG) COM1_LOCAL_MEM_BASE)
#define COM2_ADR        	((ULONG) CCSBAR + (ULONG) COM2_LOCAL_MEM_BASE)

#define N_DUART_CHANNELS 	2       	      /* 2 serial ports  */
#define N_DUART_SIO_CHANNELS  	N_DUART_CHANNELS      /* 2 serial I/O channels */

#undef  NUM_DUART_TTY
#define NUM_DUART_TTY           N_DUART_SIO_CHANNELS  /* default two daurt channels */

#define DUART_BAUD              9600                  /* default baud rate */
#define DUART_REG_ADDR_INTERVAL 1                     /* duart vector register distance */

#define XTAL                    133333333 /* Base clk value */

#define DUART1_DATA_SPACE 	0x000d0000 /* for stock data from UART1 Rx */
#define DUART2_DATA_SPACE   	0x000d0100 /* for stock data from UART2 Rx */


/* UART1 8245 UM rev0 pg12-5 */

#define URBR1                   0x04500    /* DLAB=0 read only  */
#define UTHR1                   0x04500    /* DLAB=0 write only */
#define UDLB1                   0x04500    /* DLAB=1 */
#define UDMB1                   0x04501    /* DLAB=1 */
#define UIER1                   0x04501    /* DLAB=0 */
#define UIIR1                   0x04502    /* DLAB=0 read only  */
#define UFCR1                   0x04502    /* DLAB=0 write only */
#define UAFR1                   0x04502    /* DLAB=1 */
#define ULCR1                   0x04503
#define UMCR1                   0x04504
#define ULSR1                   0x04505
#define UMSR1                   0x04506
#define USCR1                   0x04507
#define UDSR1                   0x04510    /* read only */
#define UDCR1                   0x04511

/* UART2 8245 UM rev0 pg12-6 */

#define URBR2                   0x04600    /* DLAB=0 read only  */
#define UTHR2                   0x04600    /* DLAB=0 write only */
#define UDLB2                   0x04600    /* DLAB=1 */
#define UDMB2                   0x04601    /* DLAB=1 */
#define UIER2                   0x04601    /* DLAB=0 */
#define UIIR2                   0x04602    /* DLAB=0 read only  */
#define UFCR2                   0x04602    /* DLAB=0 write only */
#define UAFR2                   0x04602    /* DLAB=1 */
#define ULCR2                   0x04603
#define UMCR2                   0x04604
#define ULSR2                   0x04605
#define UMSR2                   0x04606
#define USCR2                   0x04607
#define UDSR2                   0x04610    /* read only */
#define UDCR2                   0x04611

#ifdef __cplusplus
}
#endif

#endif  /* __INCsysDuarth */





