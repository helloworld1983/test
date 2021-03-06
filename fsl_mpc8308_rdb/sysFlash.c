/* sysFlash.c - Flash memory device driver */

/*
 * Copyright (c) 1993-1994, 1996-1998, 2000-2001, 2004-2007, 2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01y,15jul09,my_  fixed diab compiler warnings (WIND00173188)
01x,26jun07,l_g  add fsl_rdb8313 EN29LV640 support.
01w,01feb07,b_m  add Media5200 AMD29LV128M support.
01v,23jan06,j_b  add 28FxxxC3 support
01u,28nov05,j_b  add 28FxxxK3/K18 support
01t,27jul05,j_b  clean up warning
01s,24mar05,j_b  redefine FLASH29_REG_x_CYCLE
01r,10feb05,j_b  added 29LV320MB and 29LV065D support.
01q,24aug04,h_k  returned the second sysFlashDataPoll() arg type to FLASH_DEF
                 (SPR #101284) and added pValTmp to eliminate the GNU
                 dereferencing type-punned pointer warnings.
01p,05may04,h_k  cleaned GNU dereferencing type-punned pointer warnings and
                 constant condition in for loop statement.
01o,15feb01,frf  merged latest contribution, added support for
                 28F128J3A, 28F320J3A, 28F640J3A and 29LV040B.
01n,23mar00,zl   added support for 29LV160B/T. added sysSectorErase().
01m,01feb00,jpd  added support for 28F320. SPR 31293
01l,09sep98,jpd  added support for 28F016SV; minor doc fixes.
01k,20apr98,jpd  moved back into main source tree from local copy in BSPs.
01j,24mar98,jpd  added support for 29LV1024 and 29C040A.
01i,04jul97,jpd  added support for 28F008 device, made overlay buffer dynamic.
01h,25jun96,map  added documentation, and some clean up.
01g,02apr96,tam  cast FLASH_ADRS and FLASH_SIZE to UINT32 to get rid off
                 a compiler warning.
01f,12feb96,kkk  made 1st param of sysFlashDataPoll() volatile to confirm
                 to dzb's change.
01e,26jan96,dzb  added volatile to register pointers.
           +jpb  changed delay parameters to be globals if not defined.
01d,24feb94,dzb  added sysFlashWrite{En,Dis}able(), sysFlashBoardDelay().
01c,15feb94,dzb  added SYS_FLASH_DELAY_SHIFT macro.
01b,07jan94,dzb  added support for 29F0X0 flash devices.
                 cut ties to NVRAM macros.  added support for FLASH_WIDTH.
01a,05oct93,dzb  derived from version 1b of mem/iFlashMem.c.
*/

/*
DESCRIPTION
This library contains routines to manipulate flash memory.  Read and write
routines are included.

The macro values FLASH_ADRS, FLASH_SIZE, and FLASH_WIDTH must be defined to
indicate the address, size (in bytes), and the data-access width (in bytes) of
the flash memory.

If the flash memory needs to be overlaid, and the section of the memory that
needs to be overlaid is less than FLASH_SIZE, then, for efficiency, define
FLASH_SIZE_WRITABLE to the size (in bytes) of the overlay section.

The routine sysFlashDelay() creates a delay for a specified number of
microseconds.  The timing loop can be adjusted on a board-dependent basis by
defining the function sysFlashBoardDelay and values for the following macros,
.iP
SYS_FLASH_DELAY_SHIFT
.iP
SYS_FLASH_DELAY_ADJ
.iP
SYS_FLASH_DELAY_INCR
.LP
To use the routine sysFlashBoardDelay(), the macro SYS_FLASH_BOARD_DELAY
should be defined.

The macro FLASH_NO_OVERLAY should be defined when calls to sysFlashSet()
are expected to erase the flash and reprogram it with only the new data.

The macro FLASH_LOCKED should be defined when block lock/unlock commands
are required to erase the flash or reprogram it with new data.

The macro SYS_FLASH_TYPE should be defined for flash devices that cannot be
auto-selected. This macro should be set to a flash device code defined in the
header files, <drv/mem/flash28.h> and <drv/mem/flash29.h>

To support flash devices that that need to turn on/off write protect features
(special programming voltages or other write-enable features), the macro
SYS_FLASH_WRITE, and the routines, sysFlashWriteEnable() and
sysFlashFlashWriteDisable() should be defined.

INTERNAL:
The FLASH_SIZE_WRITABLE concept doesn't work very well.  It just limits the
amount of flash that is writable, so why bother.  What it was really
intended to address was flash that is only block writable, i.e. you
can only write a complete block at a time.  To properly handle block
memory, you must copy the old block of memory to a buffer, update the
part of the buffer that is to be changed, and then write back the
complete buffer in a single write operation.

The accesses to non-volatile memory, and flash control registers needs
to be abstracted.  Macros should be used for all actual i/o operations.
*/

#include <drv/mem/flashDev.h>
#include <drv/mem/flash28.h>
#include <drv/mem/flash29.h>

#ifndef FLASH_NO_OVERLAY
#  include <stdlib.h>
#endif /* FLASH_NO_OVERLAY */

/* defines */
#define FLASH_29LV128M			0x7e
#define FLASH_EN29LV640         0x7f


#define FLASH_SECTOR_MASK		0xffff0000      /* sector size = 0x20000 */
#define FLASH_SECTOR(adrs)		((adrs) & FLASH_SECTOR_MASK)

/* Not compatible with other parts, such as FLASH_29LV160T */
#undef  FLASH29_REG_FIRST_CYCLE
#define FLASH29_REG_FIRST_CYCLE       FLASH29_REG_ADRS (0x555)
#undef  FLASH29_REG_SECOND_CYCLE
#define FLASH29_REG_SECOND_CYCLE      FLASH29_REG_ADRS (0x2aa)

/* Establish default values for DELAY parameters */

#ifndef SYS_FLASH_DELAY_SHIFT
#   define  SYS_FLASH_DELAY_SHIFT 0
#endif /*SYS_FLASH_DELAY_SHIFT*/

#ifndef SYS_FLASH_DELAY_ADJ
#   define  SYS_FLASH_DELAY_ADJ 0
#endif  /* SYS_FLASH_DELAY_ADJ */

#ifndef SYS_FLASH_DELAY_INCR
#   define  SYS_FLASH_DELAY_INCR 1
#endif  /* SYS_FLASH_DELAY_INCR */

/* Names of routines, or null values */

#ifdef  SYS_FLASH_WRITE
#   define SYS_FLASH_WRITE_ENABLE_RTN() sysFlashWriteEnable ()
#   define SYS_FLASH_WRITE_DISABLE_RTN() sysFlashWriteDisable ()
#else
#   define SYS_FLASH_WRITE_ENABLE_RTN()
#   define SYS_FLASH_WRITE_DISABLE_RTN()
#endif  /* SYS_FLASH_WRITE */

#ifdef  SYS_FLASH_BOARD_DELAY
#   define SYS_FLASH_BOARD_DELAY_RTN()  sysFlashBoardDelay ()
#else
#   define SYS_FLASH_BOARD_DELAY_RTN()
#endif  /* SYS_FLASH_BOARD_DELAY */

#ifdef SYS_FLASH_TYPE
#   define FLASH_MEM_TYPE       SYS_FLASH_TYPE
#else
#   define FLASH_MEM_TYPE       0
#endif  /* SYS_FLASH_TYPE */

#ifdef FLASH_SIZE_WRITEABLE
#   define FLASH_MEM_SIZE       FLASH_SIZE_WRITEABLE
#else
#   define FLASH_MEM_SIZE       FLASH_SIZE
#endif  /* FLASH_SIZE_WRITEABLE */

/* Operation status bits for Flash 29Fxxx devices */

#define Q7(ix)      ((ix & 0x80) >> 7)  /* DQ7 bit */
#define Q5(ix)      ((ix & 0x20) >> 5)  /* DQ5 bit */

/* globals */

IMPORT  void sysFlashWriteEnable (void);
IMPORT  void sysFlashWriteDisable (void);
IMPORT  void sysFlashBoardDelay (void);

int flashDelayShift = SYS_FLASH_DELAY_SHIFT;
int flashDelayAdj   = SYS_FLASH_DELAY_ADJ;
int flashDelayIncr  = SYS_FLASH_DELAY_INCR;

/* forward declarations */

void    sysFlashDelay (int delayCount);
STATUS  sysFlashDataPoll (volatile FLASH_DEF * pFA, FLASH_DEF value);
STATUS  sysFlashErase (UINT8 flashType);
STATUS  sysFlashWrite (FLASH_DEF * pFB, int size, int offset,
                       UINT8 flashType, FLASH_DEF value);
UINT8   sysFlashTypeGet (void);



/******************************************************************************
*
* sysFlashGet - get the contents of flash memory
*
* This routine copies the contents of flash memory into a specified
* string.  The string is terminated with an EOS.
*
* RETURNS: OK, or ERROR if access is outside the flash memory range.
*
* SEE ALSO: sysFlashSet()
*
* INTERNAL
* If multiple tasks are calling sysFlashSet() and sysFlashGet(),
* they should use a semaphore to ensure mutually exclusive access.
*/

STATUS sysFlashGet
    (
    char *  string,     /* where to copy flash memory      */
    int     strLen,     /* maximum number of bytes to copy */
    int     offset      /* byte offset into flash memory   */
    )
    {
    if ((offset < 0) || (strLen < 0) || ((offset + strLen) > FLASH_SIZE))
        return (ERROR);

    bcopyBytes ((char *) (FLASH_ADRS + offset), string, strLen);
    string [strLen] = EOS;

    return (OK);
    }

/******************************************************************************
*
* sysFlashDelay - create a delay for a specified number of microseconds
*
* This routine implements a busy wait for a specified number of microseconds.
* The timing loop can be adjusted on a board-dependent basis by
* defining values for the following macros:
* .iP
* SYS_FLASH_DELAY_SHIFT
* .iP
* SYS_FLASH_DELAY_ADJ
* .iP
* SYS_FLASH_DELAY_INCR
* .LP
* The values SYS_FLASH_DELAY_SHIFT and SYS_FLASH_DELAY_ADJ
* convert microseconds into a board-dependent tick-count.
* This routine can call a user-defined hook, sysFlashBoardDelay(),
* which creates a delay for a number of board-dependent ticks as
* specified by SYS_FLASH_DELAY_INCR.  To use sysFlashBoardDelay(), define
* SYS_FLASH_BOARD_DELAY in config.h.
*
* RETURNS: N/A
*
* SEE ALSO: sysFlashErase(), sysFlashWrite()
*/

void sysFlashDelay
    (
    int delayCount  /* number of uSec to delay */
    )
    {
    int ix;

    delayCount <<= flashDelayShift; /* board-dependent shift */
    delayCount += flashDelayAdj;        /* board-dependent addition */

    for (ix = 0; ix < delayCount; ix += flashDelayIncr)
        SYS_FLASH_BOARD_DELAY_RTN ();
    }

/******************************************************************************
*
* sysFlashDataPoll - wait for a flash device operation to complete
*
* This routine polls a specified address on a 29F\f2xxx\f1 flash device
* until the device operation at that location completes or times out.
*
* While a flash operation is in progress, a read on the device
* returns on Q7 (data bit 7) the complement of the previous value of Q7.  Once
* the flash operation has completed, the Q7 bit returns the true data
* of the last write. Subsequent reads return the correct data in Q0-7.
*
* The Q5 bit implements a timeout functionality.  When a currently
* executing flash operation exceeds specified limits, the Q5 bit is set (to 1).
*
* RETURNS: OK, or ERROR if the timeout (!Q5) occurs before the device operation
* completes.
*
* SEE ALSO: sysFlashErase(), sysFlashWrite()
*/

STATUS sysFlashDataPoll
    (
    volatile FLASH_DEF * pFA,   /* programmed address to poll */
    FLASH_DEF value     /* data programmed to poll address */
    )
    {
    STATUS retVal = OK;
    volatile FLASH_POLL_DEF * pTest = (FLASH_POLL_DEF *) pFA;

    /* work around for GNU compiler warnings. */

    FLASH_DEF * pValTmp = (FLASH_DEF *) &value;
    volatile FLASH_POLL_DEF * pVal  = (FLASH_POLL_DEF *) pValTmp;
    int ix;         /* byte counter */
    int vBit;           /* programmed value of DQ7 */

    for (ix = (FLASH_WIDTH/FLASH_CHIP_WIDTH - 1); (ix >= 0 ) && (retVal == OK);
            ix--, pTest++, pVal++)
        {
        vBit = Q7(*pVal);

        while (Q7(*pTest) != vBit)
            if (Q5(*pTest) == 1)    /* timeout ? */
                break;

        if (Q7(*pTest) != vBit)     /* check Q7 & Q5 race */
            retVal = ERROR;
        }

    return (retVal);
    }

/******************************************************************************
*
* sysSectorErase - erase the contents of a sector
*
* This routine clears the contents of one sector in the flash memory.
*
* Flash 29F\f2xxx\f1 devices are erased by writing the six-byte erase code
* into specific address locations, which sets all byte locations to a high
* value (0xFF).
*
* RETURNS: OK, or ERROR if the contents of sector cannot be erased.
*/

STATUS sysSectorErase
    (
    volatile FLASH_DEF * pFA,      /* Sector start address */
    UINT8 flashType                /* type of flash memory on-board */
    )
    {
    STATUS retVal = OK;

    switch (flashType)
        {
    case (FLASH_28F640J3A):
    case (FLASH_28F320J3A):
    case (FLASH_28F128J3A):
    case (FLASH_28F640K3):
    case (FLASH_28F128K3):
    case (FLASH_28F256K3):
    case (FLASH_28F640K18):
    case (FLASH_28F128K18):
    case (FLASH_28F256K18):
    case (FLASH_28F640C3B):
    case (FLASH_28F320C3B):
    case (FLASH_28F160C3B):
    case (FLASH_28F800C3B):
    case (FLASH_28F640C3T):
    case (FLASH_28F160C3T):
    case (FLASH_28F800C3T):
        SYS_FLASH_WRITE_ENABLE_RTN ();      /* raise Vpp */

#ifdef FLASH_LOCKED
        /* block needs to be unlocked first */
        *pFA = FLASH28_CMD_LOCK_SETUP;
        *pFA = FLASH28_CMD_UNLOCK;
        *pFA = FLASH28_CMD_RESET;
#endif /* FLASH_LOCKED */

            *pFA = FLASH28_CMD_ERASE_SETUP;     /* setup */
            *pFA = FLASH28F008_CMD_ERASE;       /* erase */

        /* Check Write State Machine Status */
        do
          {
          } while ((*pFA & FLASH28F008_STAT_WSMS) != FLASH28F008_STAT_WSMS);


        /* Check Erase Error Status */

        if ((*pFA & FLASH28F008_STAT_EWS) != 0)
        {
        *pFA = FLASH28F008_CMD_CLEAR_STATUS;
        retVal = ERROR;
        }

            pFA = FLASH_CAST (FLASH_ADRS);
            *pFA = FLASH28_CMD_RESET;

#ifdef FLASH_LOCKED
        /* block needs to be locked afterward */
        *pFA = FLASH28_CMD_LOCK_SETUP;
        *pFA = FLASH28_CMD_LOCK;
        *pFA = FLASH28_CMD_RESET;
#endif /* FLASH_LOCKED */

        SYS_FLASH_WRITE_DISABLE_RTN ();     /* lower Vpp */
            break;

        case (FLASH_29LV160T):
        case (FLASH_29LV160B):
        case (FLASH_29LV040B):
        case (FLASH_29LV128M):
	    case (FLASH_EN29LV640):
			SYS_FLASH_WRITE_ENABLE_RTN ();      /* enable write */
			
            *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FIRST;
            *(FLASH_CAST FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_SECOND;
			*(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_CHIP_ERASE;
			*(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FOURTH;
            *(FLASH_CAST FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_FIFTH;
            *pFA                   = FLASH29_CMD_SECTOR;
			
            do
            {
            retVal = sysFlashDataPoll (pFA, (FLASH_DEF) 0xffffffff);
            } while ((*pFA != (FLASH_DEF) 0xffffffff) && (retVal == OK));


			SYS_FLASH_WRITE_DISABLE_RTN ();     /* disable write */
			break;
			
        default:
            retVal = ERROR;
        }

    return (retVal);
    }

/******************************************************************************
*
* sysFlashErase - erase the contents of flash memory
*
* This routine clears the contents of flash memory.
*
* Flash 28F\f2xxx\f1 devices are erased by writing a flash erase command to
* the device and verifying that each flash location is set to a high value
* (0xFF).
*
* Flash 29F\f2xxx\f1 devices are erased by writing the six-byte erase code
* into specific address locations, which sets all byte locations to a high
* value (0xFF).
*
* RETURNS: OK, or ERROR if the contents of flash memory cannot be erased.
*/

STATUS sysFlashErase
    (
    UINT8 flashType     /* type of flash memory on-board */
    )
    {
    volatile FLASH_DEF * pFA = FLASH_CAST (FLASH_ADRS);
    STATUS retVal = OK;
    int ix;

    switch (flashType)
        {
    case (FLASH_28F008):
    case (FLASH_28F016):
    case (FLASH_28F160):
    case (FLASH_28F320):
        SYS_FLASH_WRITE_ENABLE_RTN ();      /* raise Vpp */

            *pFA = FLASH28_CMD_ERASE_SETUP;     /* setup */
            *pFA = FLASH28F008_CMD_ERASE;       /* erase */

        /* Check Write State Machine Status */

        do
        {
        *pFA = FLASH28F008_CMD_READ_STATUS;
        } while ((*pFA & FLASH28F008_STAT_WSMS) != FLASH28F008_STAT_WSMS);


        /* Check Erase Error Status */

        if ((*pFA & FLASH28F008_STAT_EWS) != 0)
        {
        *pFA = FLASH28F008_CMD_CLEAR_STATUS;
        retVal = ERROR;
        }

            pFA = FLASH_CAST (FLASH_ADRS);
            *pFA = FLASH28_CMD_RESET;

        SYS_FLASH_WRITE_DISABLE_RTN ();     /* lower Vpp */
            break;

    case (FLASH_28F640J3A):
    case (FLASH_28F320J3A):
    case (FLASH_28F128J3A):
    case (FLASH_28F640K3):
    case (FLASH_28F128K3):
    case (FLASH_28F256K3):
    case (FLASH_28F640K18):
    case (FLASH_28F128K18):
    case (FLASH_28F256K18):
    case (FLASH_28F640C3B):
    case (FLASH_28F320C3B):
    case (FLASH_28F160C3B):
    case (FLASH_28F800C3B):
    case (FLASH_28F640C3T):
    case (FLASH_28F160C3T):
    case (FLASH_28F800C3T):
        SYS_FLASH_WRITE_ENABLE_RTN ();      /* raise Vpp */

#ifdef FLASH_LOCKED
        /* block needs to be unlocked first */
        *pFA = FLASH28_CMD_LOCK_SETUP;
        *pFA = FLASH28_CMD_UNLOCK;
        *pFA = FLASH28_CMD_RESET;
#endif /* FLASH_LOCKED */

        *pFA = FLASH28_CMD_ERASE_SETUP;     /* setup */
        *pFA = FLASH28F008_CMD_ERASE;       /* erase */

        /* Check Write State Machine Status */

        do
          {
          } while ((*pFA & FLASH28F008_STAT_WSMS) != FLASH28F008_STAT_WSMS);

        /* Check Erase Error Status */

        if ((*pFA & FLASH28F008_STAT_EWS) != 0)
        {
        *pFA = FLASH28F008_CMD_CLEAR_STATUS;
        retVal = ERROR;
        }

            pFA = FLASH_CAST (FLASH_ADRS);
            *pFA = FLASH28_CMD_RESET;

#ifdef FLASH_LOCKED
        /* block needs to be locked afterward */
        *pFA = FLASH28_CMD_LOCK_SETUP;
        *pFA = FLASH28_CMD_LOCK;
        *pFA = FLASH28_CMD_RESET;
#endif /* FLASH_LOCKED */

        SYS_FLASH_WRITE_DISABLE_RTN ();     /* lower Vpp */
            break;

        case (FLASH_28F256):
        case (FLASH_28F512):
        case (FLASH_28F010):
        case (FLASH_28F020):
            /* program the device to all zeros */

            if (sysFlashWrite (NULL, FLASH_SIZE, 0, flashType, 0) == ERROR)
        return (ERROR);

        SYS_FLASH_WRITE_ENABLE_RTN ();      /* raise Vpp */

            *pFA = FLASH28_CMD_ERASE_SETUP;     /* setup */
            *pFA = FLASH28_CMD_ERASE;           /* erase */
            sysFlashDelay (10000);

            for (; (pFA < FLASH_CAST ((UINT32)FLASH_ADRS + (UINT32)FLASH_SIZE))
           && (retVal == OK); pFA++)
                for (ix = 0;; ix++)
                   {
                    *pFA = FLASH28_CMD_ERASE_VERIFY;    /* verify */
                    sysFlashDelay (6);          /* wait for verify */

                    if (*pFA == (FLASH_DEF) 0xffffffff) /* done? */
                    break;

                    if (ix == 1000)
                        {
                        retVal = ERROR;
                        break;
                        }

                    *pFA = FLASH28_CMD_ERASE_SETUP; /* setup */
                    *pFA = FLASH28_CMD_ERASE;       /* erase */
                sysFlashDelay (10000);
                }

            pFA = FLASH_CAST (FLASH_ADRS);
            *pFA = FLASH28_CMD_RESET;
            *pFA = FLASH28_CMD_READ_MEM;
        sysFlashDelay (6);

        SYS_FLASH_WRITE_DISABLE_RTN ();     /* lower Vpp */
            break;

        case (FLASH_29F010):
        case (FLASH_29LV160T):
        case (FLASH_29LV160B):
        case (FLASH_29LV040B):
        case (FLASH_29LV128M):
	    case (FLASH_EN29LV640):
            SYS_FLASH_WRITE_ENABLE_RTN ();      /* enable write */

            *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FIRST;
            *(FLASH_CAST FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_SECOND;
            *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_CHIP_ERASE;
            *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FOURTH;
            *(FLASH_CAST FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_FIFTH;
            *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_SIXTH;

            do
            {
                retVal = sysFlashDataPoll (pFA, (FLASH_DEF) 0xffffffff);
                } while ((*pFA != (FLASH_DEF) 0xffffffff) && (retVal == OK));

            *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FIRST;
            *(FLASH_CAST FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_SECOND;
            *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_READ_RESET;

            SYS_FLASH_WRITE_DISABLE_RTN ();     /* disable enable */
            break;

    case (FLASH_29C040A):
        case (FLASH_29LV1024):
        /*
         * You can erase these entire chips, but there is really no
         * need, as a write automatically erases the sector being
         * written. In particular, we will not generally want all
         * of the chip erased from sysFlashSet().
         */

            *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FIRST;
            *(FLASH_CAST FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_SECOND;
            *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_CHIP_ERASE;
            *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FOURTH;
            *(FLASH_CAST FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_FIFTH;
            *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_SIXTH;

        /*
         * Atmel chip spec says it will take 20 ms max and does not
         * define a mechanism for polling for completion
         *
         * It seems that this driver cannot always safely use taskDelay()
         */

        sysFlashDelay (20000);
            break;

        default:
            retVal = ERROR;
        }

    return (retVal);
    }

/******************************************************************************
*
* sysFlashWrite - write data to flash memory
*
* This routine copies specified data of a specified length, <size>, into a
* specified offset, <offset>, in the flash memory.  Data is passed as a string,
* <pFB>, if not NULL.  If NULL, data is taken as a repeated sequence of
* <value>.
* The parameter <flashType> should be set to the flash device code.
* The parameter <offset> must be appropriately aligned for the width of
* the Flash devices in use.
*
* Flash 28F\f2xxx\f1 devices are programmed by a sequence of operations:
* .iP
* set up device to write
* .iP
* perform write
* .iP
* verify the write
* .LP
*
* Flash 29F\f2xxx\f1 devices are programmed by a sequence of operations:
* .iP
* set up device to write
* .iP
* perform write
* .iP
* wait for the write to complete
* .LP
*
* RETURNS: OK, or ERROR if the write operation fails.
*
* SEE ALSO: sysFlashSet()
*/

STATUS sysFlashWrite
    (
    FLASH_DEF * pFB,        /* string to be copied; use <value> if NULL */
    int     size,       /* size to program in bytes */
    int     offset,     /* byte offset into flash memory */
    UINT8   flashType,  /* type of flash memory on-board */
    FLASH_DEF   value       /* value to program */
    )
    {
    volatile FLASH_DEF * pFA;       /* flash address */
    STATUS retVal = OK;
    int ix;
    int sectorSize = 128;
    int twc = 2;    /* time for write completion */

    switch (flashType)
        {
    case (FLASH_28F008):
    case (FLASH_28F016):
    case (FLASH_28F160):
    case (FLASH_28F320):
        SYS_FLASH_WRITE_ENABLE_RTN ();      /* raise Vpp */

            for (pFA = FLASH_CAST (FLASH_ADRS + offset); (pFA < FLASH_CAST
                (FLASH_ADRS + size + offset)) && (retVal == OK); pFA++)
        {
        if (pFB != NULL)
            value = *pFB++;

        *pFA = FLASH28_CMD_PROG_SETUP;  /* write setup */
        *pFA = value;           /* data to write */

        /* Check Write State Machine Status */

        do
            {
            *pFA = FLASH28F008_CMD_READ_STATUS;
            }
        while ((*pFA & FLASH28F008_STAT_WSMS) != FLASH28F008_STAT_WSMS);


        /* Check Byte Write Error Status */

        if ((*pFA & FLASH28F008_STAT_BWS) != 0)
            {
            *pFA = FLASH28F008_CMD_CLEAR_STATUS;
            retVal = ERROR;
            }
        }

            pFA = FLASH_CAST (FLASH_ADRS);
            *pFA = FLASH28_CMD_RESET;

            SYS_FLASH_WRITE_DISABLE_RTN ();     /* lower Vpp */
            break;

    case (FLASH_28F320J3A):
    case (FLASH_28F640J3A):
    case (FLASH_28F128J3A):
    case (FLASH_28F640K3):
    case (FLASH_28F128K3):
    case (FLASH_28F256K3):
    case (FLASH_28F640K18):
    case (FLASH_28F128K18):
    case (FLASH_28F256K18):
    case (FLASH_28F640C3B):
    case (FLASH_28F320C3B):
    case (FLASH_28F160C3B):
    case (FLASH_28F800C3B):
    case (FLASH_28F640C3T):
    case (FLASH_28F160C3T):
    case (FLASH_28F800C3T):
         SYS_FLASH_WRITE_ENABLE_RTN ();     /* raise Vpp */

#ifdef FLASH_LOCKED
        /* block needs to be unlocked first */
        pFA = FLASH_CAST (FLASH_ADRS + offset);
        *pFA = FLASH28_CMD_LOCK_SETUP;
        *pFA = FLASH28_CMD_UNLOCK;
        *pFA = FLASH28_CMD_RESET;
#endif /* FLASH_LOCKED */

        for (pFA = FLASH_CAST (FLASH_ADRS + offset);
           (pFA <FLASH_CAST (FLASH_ADRS + size + offset)) &&
           (retVal == OK);
           pFA++)
           {
           if (pFB != NULL)
         value = *pFB++;

           *pFA = FLASH28_CMD_PROG_SETUP;   /* write setup */
           *pFA = value;                /* data to write */

           /* Check Write State Machine Status */

           do
           {
           } while ((*pFA & FLASH28F008_STAT_WSMS) != FLASH28F008_STAT_WSMS);

           /* Check Byte Write Error Status */

           if ((*pFA & FLASH28F008_STAT_BWS) != 0)
           {
           *pFA = FLASH28F008_CMD_CLEAR_STATUS;
           retVal = ERROR;
            }
           *pFA = FLASH28_CMD_RESET;
           }

#ifdef FLASH_LOCKED
        /* block needs to be locked afterward */
        pFA = FLASH_CAST (FLASH_ADRS + offset);
        *pFA = FLASH28_CMD_LOCK_SETUP;
        *pFA = FLASH28_CMD_LOCK;
        *pFA = FLASH28_CMD_RESET;
#endif /* FLASH_LOCKED */

         SYS_FLASH_WRITE_DISABLE_RTN ();        /* lower Vpp */
         break;

        case (FLASH_28F256):
        case (FLASH_28F512):
        case (FLASH_28F010):
        case (FLASH_28F020):
            SYS_FLASH_WRITE_ENABLE_RTN ();      /* raise Vpp */

            for (pFA = FLASH_CAST (FLASH_ADRS + offset); (pFA < FLASH_CAST
                (FLASH_ADRS + size + offset)) && (retVal == OK); pFA++)
                for (ix = 0;; ix++)
                    {
                    if (pFB != NULL)
                        value = *pFB++;

                    *pFA = FLASH28_CMD_PROG_SETUP;  /* write setup */
                    *pFA = value;           /* data to write */
                    sysFlashDelay (10);         /* wait for write */

                    *pFA = FLASH28_CMD_PROG_VERIFY; /* verify command */
                    sysFlashDelay (6);          /* wait for verify */

                    if (*pFA == value)          /* done? */
                        break;

                    if (ix == 25)           /* error? */
                        {
                        retVal = ERROR;
                        break;
                        }
                    }

            pFA = FLASH_CAST (FLASH_ADRS);
            *pFA = FLASH28_CMD_RESET;
            *pFA = FLASH28_CMD_READ_MEM;
            sysFlashDelay (6);

            SYS_FLASH_WRITE_DISABLE_RTN ();     /* lower Vpp */
            break;

        case (FLASH_29F010):
        case (FLASH_29LV160T):
        case (FLASH_29LV160B):
        case (FLASH_29LV040B):
    case (FLASH_29LV128M):
		case (FLASH_EN29LV640):
        SYS_FLASH_WRITE_ENABLE_RTN ();      /* enable write */

            for (pFA = FLASH_CAST (FLASH_ADRS + offset); pFA < FLASH_CAST
                (FLASH_ADRS + size + offset) && (retVal == OK); pFA++)
                {
                *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FIRST;
                *(FLASH_CAST FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_SECOND;
                *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_PROGRAM;
                if (pFB != NULL)
                    value = *pFB++;

                *pFA = value;                       /* data to write */
            do
            {
                    retVal = sysFlashDataPoll (pFA, (FLASH_DEF) value);
                    } while ((*pFA != value) && (retVal == OK));
                }

            *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FIRST;
            *(FLASH_CAST FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_SECOND;
            *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_READ_RESET;

        SYS_FLASH_WRITE_DISABLE_RTN ();     /* disable write */
            break;

    case (FLASH_29C040A):
        sectorSize = 256;
        twc = 1;

        /* FALL THROUGH */

        case (FLASH_29LV1024):
            for (pFA = FLASH_CAST (FLASH_ADRS + offset);
         pFA < FLASH_CAST (FLASH_ADRS + size + offset); )
                {
        /* Enable sector write */

        *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FIRST;
        *(FLASH_CAST FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_SECOND;
        *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_PROGRAM;

        /*
         * write the sector:
         *    29LV1024: 128 half-word accesses = 256 bytes
         *    29C040A 256 byte accesses
         */

        for (ix = 0; ix < sectorSize; ix++)
            {
            if (pFB != NULL)
            value = *pFB++;

            /* ensure entire sector written */

            if (pFA >= FLASH_CAST (FLASH_ADRS + size + offset))
            value = (FLASH_DEF) 0xFFFFFFFF;

            *pFA++ = value;                     /* data to write */
            }

        /*
         * Ensure write cycle completes. Atmel chip spec suggest
         * waiting for a specified time rather than polling for
         * completion.
         *
         * It seems that we cannot always safely use taskDelay()
         */

        sysFlashDelay (10000 * twc);
                }

            break;

        default:
            retVal = ERROR;
        }

    return (retVal);
    }

/******************************************************************************
*
* sysFlashTypeGet - determine the device type of on-board flash memory
*
* This routine uses the `autoselect' command to determine the device type of
* on-board flash memory for flash 29F\f2xxx\f1 devices.
*
* RETURNS: An integer indicating the device type of on-board flash memory.
*/

UINT8 sysFlashTypeGet (void)
    {
    volatile FLASH_DEF * pFA = FLASH_CAST (FLASH_ADRS); /* flash address */
    UINT8 retVal;

    SYS_FLASH_WRITE_ENABLE_RTN ();          /* enable writes */

    *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FIRST;
    *(FLASH_CAST FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_SECOND;
    *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_AUTOSELECT;

    /* 29LV1024 (at least) requires 20ms delay */

    /* It seems we cannot always safely use taskDelay() */

    sysFlashDelay (20000);

    retVal = (UINT8) *++pFA;

    *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FIRST;
    *(FLASH_CAST FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_SECOND;
    *(FLASH_CAST FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_READ_RESET;

    sysFlashDelay (20000);

    SYS_FLASH_WRITE_DISABLE_RTN ();         /* disable writes */

    return (retVal);
    }

/******************************************************************************
*
* sysFlashSet - write to flash memory
*
* This routine copies a specified string into flash memory after calling
* sysFlashErase() and clearing flash memory.
*
* If FLASH_NO_OVERLAY is defined, the parameter <offset> must be
* appropriately aligned for the Flash devices in use (device width,
* sector size etc.).
*
* If the specified string must be overlaid on the contents of flash memory,
* undefine FLASH_NO_OVERLAY.
*
* RETURNS: OK, or ERROR if the write fails or the input parameters are
* out of range.
*
* SEE ALSO: sysFlashErase(), sysFlashGet(), sysFlashTypeGet(), sysFlashWrite()
*
* INTERNAL
* If multiple tasks are calling sysFlashSet() and sysFlashGet(),
* they should use a semaphore to ensure mutually exclusive access to flash
* memory.
*/

STATUS sysFlashSet
    (
    char *  string,     /* string to be copied into flash memory */
    int     strLen,     /* maximum number of bytes to copy       */
    int     offset      /* byte offset into flash memory         */
    )
    {
    static UINT8 flashType = FLASH_MEM_TYPE;

#ifndef FLASH_NO_OVERLAY
    char *tempBuffer;
#endif  /* FLASH_NO_OVERLAY */

    /* limited to one sector */
    if ((offset < 0) || (strLen < 0) || ((offset + strLen) > FLASH_MEM_SIZE) ||
            ( (offset - FLASH_SECTOR(offset) + strLen) > FLASH_SECTOR_SIZE) )
        return (ERROR);

    /* see if contents are actually changing */

    if (bcmp ((char *) (FLASH_ADRS + offset), string, strLen) == 0)
        return (OK);


#ifndef FLASH_NO_OVERLAY
    /* first read existing data */

    if ( (tempBuffer = malloc(FLASH_SECTOR_SIZE)) == NULL)
        return (ERROR);

    bcopyBytes ((char *) FLASH_SECTOR(FLASH_ADRS + offset), tempBuffer,
                    FLASH_SECTOR_SIZE);
    bcopyBytes (string, (tempBuffer + offset - FLASH_SECTOR(offset)), strLen);
#endif  /* FLASH_NO_OVERLAY */

    if (flashType == 0)
        flashType = sysFlashTypeGet ();

    switch (flashType)
    {
    case (FLASH_28F640J3A):
    case (FLASH_28F320J3A):
    case (FLASH_28F128J3A):
        case (FLASH_28F640K3):
        case (FLASH_28F128K3):
        case (FLASH_28F256K3):
        case (FLASH_28F640K18):
        case (FLASH_28F128K18):
        case (FLASH_28F256K18):
        case (FLASH_28F640C3B):
        case (FLASH_28F320C3B):
        case (FLASH_28F160C3B):
        case (FLASH_28F800C3B):
        case (FLASH_28F640C3T):
        case (FLASH_28F160C3T):
        case (FLASH_28F800C3T):
        /* erase the sector */

        if (sysSectorErase (FLASH_CAST (FLASH_SECTOR (FLASH_ADRS + offset)), flashType) == ERROR)
            {
#ifndef FLASH_NO_OVERLAY
            free (tempBuffer);
#endif
            return (ERROR);
            }
        break;

    case FLASH_29C040A:
        case FLASH_29LV1024:
        /* do not erase these as not required */
            break;

    case (FLASH_29LV160T):
    case (FLASH_29LV160B):
    case (FLASH_29LV040B):
    case (FLASH_29LV128M):
	case (FLASH_EN29LV640):
        /* erase the sector */

        if (sysSectorErase (FLASH_CAST (FLASH_SECTOR (FLASH_ADRS + offset)), flashType) == ERROR)
            {
#ifndef FLASH_NO_OVERLAY
            free (tempBuffer);
#endif
            return (ERROR);
            }
        break;

    default:
        if (sysFlashErase (flashType) == ERROR) /* erase device */
            {
#ifndef FLASH_NO_OVERLAY
            free (tempBuffer);
#endif
            return (ERROR);
            }
        break;

    } /* endswitch */

#ifndef FLASH_NO_OVERLAY                /* program device */
    if (sysFlashWrite ((FLASH_DEF *) (tempBuffer), FLASH_SECTOR_SIZE,
            FLASH_SECTOR(offset), flashType, 0) == ERROR)
        {
            free (tempBuffer);
#else   /* FLASH_NO_OVERLAY */
    if (sysFlashWrite ((FLASH_DEF *) (string), strLen, offset, flashType, 0) ==
            ERROR)
        {
#endif  /* FLASH_NO_OVERLAY */
            return (ERROR);
        }

#ifndef FLASH_NO_OVERLAY
    free (tempBuffer);
#endif

    return (OK);
    }

