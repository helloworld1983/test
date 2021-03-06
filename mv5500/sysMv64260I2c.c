/* sysMv64260I2c.c - Low Level MV64260 I2C Routines */

/* 
 * Copyright (c) 2002, 2004, 2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/* Copyright 2003 Motorola, Inc., All Rights Reserved */

/*
modification history
--------------------
01e,20may08,x_f  Remove i2cInitFlag and cpuBusSpd variable.
01e,01nov04,mdo  Documentation fixes for apigen
01d,27feb03,scb  Set I2C baud rate to "worst case" default instead
                 of trying to calculate optimal value based on bus speed.
01c,29jan03,cak  Replaced all references to a DFLT_BUS_CLK and
                 DEC_CLOCK_FREQ with a new definition that can be
                 either hard-coded or dynamically calculated. 
01b,03dec02,scb  Fixed warnings flagged by diab compiler.
01a,01oct02,scb  Copied from hxeb100 base (ver 01a).
*/

/* 
DESCRIPTION

This file contains the low-level routines which generate the following 
cycles on the I2C bus, via the MV64260's I2C interface:

\cs
  Start
  Stop
  Acknowledge-in
  Acknowledge-out
  Read
  Write
\ce

An initialization routine is also provided to initialize the I2C interface.

INCLUDE FILES
*/

/* includes */

#include "vxWorks.h"
#include "config.h"
#include "sysLib.h"
#include "mv64260.h"
#include "mv64260I2c.h"

/* defines */

/* externals */

IMPORT UINT32 sysTimeBaseLGet (void);
IMPORT UINT32 sysCpuBusSpd (void);

/* locals */

/* forward declarations */

LOCAL void sysMv64260I2cInit (UINT32);
LOCAL BOOL sysMv64260I2cIntFlagRead (UINT32);

/*******************************************************************************
*
* sysMv64260I2cInit - initialize the MV64260's I2C interface
*
* This function initializes the I2C interface of the MV64260.
*
* RETURNS: N/A 
*
* ERRNO
*/

LOCAL void sysMv64260I2cInit 
    (
    UINT32 base		/* base of MV64260 register set */
    ) 
    {
    UINT32 baudRate;

    /* Perform a soft reset */
    
    MV64260_WRITE32_PUSH(base, I2C_SFT_RST, 0);
    EIEIO_SYNC;
    sysMv64260UsDelay(1000);
    
    /*
     * We will set the baud rate to the "worst case" value.  This
     * value will work under all circumstances for any bus speed.
     * Using this value has the following effect:
     * 
     * 1.  The code is simplified.  
     *     The optimal baud rate calculation requires the use of a
     *     precalculated "normalized" bus speed.  By using a
     *     "worst case" value which works for all bus speeds, we
     *     eliminate the need for a "bus speed normalization"
     *     function.
     *
     * 2.  The rate at which of the VPD can be read will be slightly 
     *     slower than if an optimal baud rate value (calculated from
     *     "normalized" bus speed) were used.  The performance 
     *     degradation "worst case" would result if we were running 
     *     with a 100MHz bus and would be 0x23/0x2c = 0.8 as fast as 
     *     if the optimal baud rate were used.  For busses faster
     *     than 100MHz, the degradation is not as severe.  I2C accesses
     *     are only done at initialization and during some user commands
     *     such as "vpdShow".  Thus, this minor degradation in speed
     *     is not considered to be an important issue.
     */
    
    baudRate = 0x2C;        /* 86.805 KHz I2C bus clock */
    
    MV64260_WRITE32_PUSH(base, I2C_BAUDE_RATE, baudRate);
    EIEIO_SYNC;
    sysMv64260UsDelay(1000);
    
    /* Set ACK and I2CEN bits in I2C Control register */
    
    MV64260_WRITE32_PUSH(base, I2C_CTRL, 
                         (I2C_CTRL_ACK_MASK | I2C_CTRL_ENB_SHIFT));
    EIEIO_SYNC;
    sysMv64260UsDelay(4000);

    }

/*******************************************************************************
*
* sysMv64260I2cAckIn - perform an acknowledge-in cycle on the I2C bus
*
* This routine simply returns OK.  The MV64260 does not require this routine,
* it is included here as a hook to the generic I2C interface routines in
* sysMotI2c.c.
*
* RETURNS: OK always.
*
* ERRNO
*/

STATUS sysMv64260I2cAckIn 
    (
    UINT32 base ARG_UNUSED	/* base of MV64260 register set */
    )
    {
    return(OK);
    }

/*******************************************************************************
*
* sysMv64260I2cAckOut - perform an acknowledge-out cycle on the I2C bus
*
* This routine simply returns OK.  The MV64260 does not require this routine,
* it is included here as a hook to the generic I2C interface routines in
* sysMotI2c.c.
*
* RETURNS: OK always.
*
* ERRNO
*/

STATUS sysMv64260I2cAckOut 
    (
    UINT32 base ARG_UNUSED	/* base of MV64260 register set */
    )
    {
    return(OK);
    }

/*******************************************************************************
*
* sysMv64260I2cStop - perform an I2C stop cycle on the I2C bus
*
* This routine performs a stop cycle on the I2C bus.
*
* RETURNS: OK, or ERROR if operation unsuccessful.
*
* ERRNO
*/

STATUS sysMv64260I2cStop 
    (
    UINT32 base		/* base of MV64260 register set */
    )
    {
    UINT32 controlReg;		/* control register */

    /* Set STOP bit in Control Register */

    controlReg = MV64260_READ32(base, I2C_CTRL);
    MV64260_WRITE32_PUSH(base, I2C_CTRL, (controlReg | I2C_CTRL_STOP_MASK));
    EIEIO_SYNC;
    sysMv64260UsDelay(1000);

    /* Verify INTFLAG bit is set in Control Register */

    if (sysMv64260I2cIntFlagRead(base))
        {

        /* 
         * Clear the INTFLG, but do not clear the control register,
         * which would turn off the interface.  A STOP will be transmitted
         * on the bus after the INTFLG has been cleared.
         */

        controlReg = MV64260_READ32(base, I2C_CTRL);
        MV64260_WRITE32_PUSH(base, I2C_CTRL, 
                             (controlReg & ~I2C_CTRL_INTFLG_MASK));
        EIEIO_SYNC;
        sysMv64260UsDelay(1000);
        return(OK);
        }
    else
        {
        return(ERROR);
        }
    }

/*******************************************************************************
*
* sysMv64260I2cStart - perform an I2C start cycle on the I2C bus
*
* This routine performs a start cycle on the I2C bus.
*
* RETURNS: OK, or ERROR if operation unsuccessful.
*
* ERRNO
*/

STATUS sysMv64260I2cStart 
    (
    UINT32 base		/* base of MV64260 register set */
    )
    {
    UINT32 timeOut;		/* timeout counter */
    UINT32 statusReg;		/* status register */

    /* Initialize the I2C interface, if needed. */

    sysMv64260I2cInit(base);

    /* Set START bit in Control Register */

    MV64260_WRITE32_PUSH(base, I2C_CTRL, 
			 (I2C_CTRL_START_MASK | I2C_CTRL_ENB_MASK));
    EIEIO_SYNC;
    sysMv64260UsDelay(1000);

    /* Verify INTFLAG bit is set in Control Register */

    if (sysMv64260I2cIntFlagRead(base))
        {

        /* Check for completion of START sequence */

        for (timeOut = 10; timeOut > 0; timeOut--)
            {
            statusReg = MV64260_READ32(base, I2C_STATUS);
            EIEIO_SYNC;
            if ((statusReg == I2C_STATUS_STARTTX) ||
                (statusReg == I2C_STATUS_REPEATSTARTX))
                break;
            sysMv64260UsDelay(1000);
            }
        if (!timeOut)
            {
            sysMv64260I2cStop(base);
            return(ERROR);
            }
        return(OK);
        }
    else
        {
        sysMv64260I2cStop(base);
        return(ERROR);
        }
    }

/*******************************************************************************
*
* sysMv64260I2cRead - perform an I2C read cycle on the I2C bus
*
* This routine performs an I2C read cycle on the I2C bus.
*
* RETURNS: OK, or ERROR if operation unsuccessful.
*
* ERRNO
*/

STATUS sysMv64260I2cRead
    (
    UINT32 base,		    /* base of MV64260 register set */
    UCHAR * pDataBuffer,	/* buffer to hold read data */
    BOOL lastByte		    /* boolean indicating whether reading the */
    ) 			            /* last byte in sequence */
    {
    UINT32 readData;		/* read data */
    UINT32 timeOut;		    /* timeout counter */
    UINT32 statusReg;		/* status register */

    /* Clear INTFLG and set ACK and ENABLE bits */

    MV64260_WRITE32_PUSH(base, I2C_CTRL, 
 		         (I2C_CTRL_ACK_MASK | I2C_CTRL_ENB_MASK));
    EIEIO_SYNC;
    sysMv64260UsDelay(1000);

    /* Verify INTFLAG bit is set in Control Register */

    if (sysMv64260I2cIntFlagRead(base))
        {

        /* Check for READ status of ACK */

        for (timeOut = 10; timeOut > 0; timeOut--)
            {
            statusReg = MV64260_READ32(base, I2C_STATUS);
            EIEIO_SYNC;
            if (statusReg == I2C_STATUS_MSTDATARECVACK)
                {

                /* Get data requested by user */

                readData = MV64260_READ32(base, I2C_DATA); 
                EIEIO_SYNC;
                *pDataBuffer = (UCHAR)readData;
                sysMv64260UsDelay(1000);

                /* 
                 * If last byte to read from slave
                 * Then Clear INTFLAG and set Enable bit only 
                 */

                if (lastByte)
                    {
                    MV64260_WRITE32_PUSH(base, I2C_CTRL, I2C_CTRL_ENB_MASK);
                    }
                EIEIO_SYNC;
                sysMv64260UsDelay(1000);
                break;
                }
            sysMv64260UsDelay(1000);
            }
        if (!timeOut)
            {
            sysMv64260I2cStop(base);
            return(ERROR);
            }
        return(OK);
        }
    else
        {
        sysMv64260I2cStop(base);
        return(ERROR);
        }
    }

/*******************************************************************************
*
* sysMv64260I2cWrite - perform an I2C write cycle on the I2C bus
*
* This routine performs an I2C write cycle on the I2C bus.
*
* RETURNS: OK, or ERROR if operation unsuccessful.
*
* ERRNO
*/

STATUS sysMv64260I2cWrite
    (
    UINT32 base,	/* base of MV64260 register set */
    UCHAR * pDataBuffer	/* data to be written */
    ) 
    {
    UINT32 timeOut;		/* timeout counter */
    UINT32 statusReg;		/* status register */

    /* Write data into the I2C data register */

    MV64260_WRITE32_PUSH(base, I2C_DATA, ((UINT32)*pDataBuffer)); 
    EIEIO_SYNC;
    sysMv64260UsDelay(1000);

    /* Clear INTFLG in the control register to drive data onto I2C bus */

    MV64260_WRITE32_PUSH(base, I2C_CTRL, 0x0);
    EIEIO_SYNC;
    sysMv64260UsDelay(1000);

    /* Verify INTFLAG bit is set in Control Register */

    if (sysMv64260I2cIntFlagRead(base))
        {

        /* Check for WRITE status of ACK */

        for (timeOut = 10; timeOut > 0; timeOut--)
            {
            sysMv64260UsDelay(1000);
            statusReg = MV64260_READ32(base, I2C_STATUS);
            if (statusReg == I2C_STATUS_ADDRWRITENACK)
                {

                /* No device responding, generate STOP and return ERROR */

                sysMv64260I2cStop(base);
                return(ERROR);
                }
            if ((statusReg == I2C_STATUS_ADDRWRITEACK) ||
                (statusReg == I2C_STATUS_MSTDATAWRITEACK) ||
                (statusReg == I2C_STATUS_ADDRREADACK))
                break;

            /*
             * Since we have not received the correct status, keep 
             * trying until the loop count has expired.
             */

            sysMv64260UsDelay(1000);
            EIEIO_SYNC;
            }
        if (!timeOut)
            {
            sysMv64260I2cStop(base);
            return(ERROR);
            }
        sysMv64260UsDelay(1000);
        return(OK);
        }
    else
        {
        sysMv64260I2cStop(base);
        return(ERROR);
        }
    }

/*******************************************************************************
*
* sysMv64260I2cIntFlagRead - check control register for interrupt
*
* This routine reads the I2C control register to check if the INTFLG bit
* is set.
*
* RETURNS: FALSE if INTFLG not set, and TRUE if INTFLG set.
*
* ERRNO
*/

LOCAL BOOL sysMv64260I2cIntFlagRead 
    (
    UINT32 base		/* base of MV64260 register set */
    )
    {
    UINT32 timeOut;
    UINT32 controlReg;

    for (timeOut = 10; timeOut > 0; timeOut--)
        {
        controlReg = MV64260_READ32(base, I2C_CTRL);
        EIEIO_SYNC;
        if (controlReg & I2C_CTRL_INTFLG_MASK)
            return(1);
        sysMv64260UsDelay(1000);
        }

    /*
     * If we reach this point, then the INTFLG bit is not set.
     * Therefore, return with a value of 0 to indicate that the
     * bit is not set.
     */

    return(FALSE);
    }

/*******************************************************************************
*
* sysMv64260UsDelay - delay the specified number of microseconds
*
* This routine will delay for at least the specified number of microseconds,
* using the lower 32 bit "word" of the Time Base register as the timer.
*
* RETURNS: N/A
*
* ERRNO
*/

void sysMv64260UsDelay 
    (
    UINT32 delay	/* number of microseconds to delay */
    )
    {
    UINT32 baselineTickCount;
    UINT32 ticksToWait;

    /*
     * Get the Time Base Lower register tick count, this will be used
     * as the baseline.
     */

    baselineTickCount = sysTimeBaseLGet();

    /*
     * Convert delay time into ticks
     *
     * The Time Base register and the Decrementer count at the same rate:
     * once per 4 System Bus cycles.
     *
     * e.g., 66666666 cycles     1 tick      1 second             16 tick
     *       ---------------  *  ------   *  --------          =  ----------
     *       second              4 cycles    1000000 microsec    microsec
     */

    if ((ticksToWait = delay * ((sysCpuBusSpd() / 4) / 1000000)) == 0)
        return;

    while ((sysTimeBaseLGet() - baselineTickCount) < ticksToWait);
    }
