/* byteNvRam.c - byte-oriented generic NVRAM driver */

/* Copyright 1984-2002 Wind River Systems, Inc. */
#include "copyright_wrs.h"

/*
modification history
--------------------
01d,08jul04,mil  Fixed missing volatile keywords (SPR#96944).
01c,26apr02,gtf  Modified for wrSbc7410 bsp and CAT28LV64N parallel eeprom.
01b,29oct96,wlf  doc: cleanup.
01a,03jun96,dat	 written.
*/

/*
DESCRIPTION
This driver is for byte-oriented non-volatile RAM (NVRAM).  Typical uses
are EEPROMs, static RAM, and any other byte-oriented device.
There are other generic drivers for block-oriented devices like flash memory,
and for boards that have no non-volatile memory at all.

This is boilerplate driver code.  It is to be included in source form
into sysLib.c.  Macros are used to provide the actual working elements
while this code provides the generic logic.

The following numeric value macros are required:

  NV_RAM_ADRS	  - address of first non-volatile byte
  NV_RAM_INTRVL	  - address interval between bytes
  NV_RAM_SIZE	  - total number of bytes in device
  NV_BOOT_OFFSET  - Offset to first byte of boot line information

The following procedural macros are used.  If not defined by the
specific BSP, then default procedures assuming static RAM with no
special read/write requirements will be used.

  NV_RAM_READ(x)    - Read and return one byte at offset (x).
  NV_RAM_WRITE(x,y) - Write data (y) at offset (x).
  NV_RAM_WR_ENBL    - procedure to enable writing, if any
  NV_RAM_WR_DSBL    - procedure to disable writing, if any

*/

#include "vxWorks.h"
#include "config.h"

/* default procedures assume static ram with no special r/w routines */
#ifndef NV_RAM_WR_ENBL
#define NV_RAM_WR_ENBL	/* no write enable procedure */
#else
void sysNvRamWrEnbl(void);
#endif /*NV_RAM_WR_ENBL*/

#ifndef NV_RAM_WR_DSBL
#define NV_RAM_WR_DSBL	/* no write disable procedure */
#else
void sysNvRamWrDsbl(void);
#endif /*NV_RAM_WR_DSBL*/

#ifndef NV_RAM_READ
#define NV_RAM_READ(x) \
	(*(UCHAR *)((int)NV_RAM_ADRS + ((x) * NV_RAM_INTRVL)))
#else
UINT8 sysNvRamRead (int offset);
#endif /*NV_RAM_READ*/

#ifndef NV_RAM_WRITE
#define NV_RAM_WRITE(x,y) \
	(*(UCHAR *)((int)NV_RAM_ADRS + ((x) * NV_RAM_INTRVL)) = (y))
#else
void sysNvRamWrite (int offset, UINT8 data);
#endif /*NV_RAM_WRITE*/

/******************************************************************************
*
* sysNvRamGet - get the contents of non-volatile RAM
*
* This routine copies the contents of non-volatile memory into a specified
* string.  The string is terminated with an EOS.
*
* RETURNS: OK, or ERROR if access is outside the non-volatile RAM range.
*
* SEE ALSO: sysNvRamSet()
*/

STATUS sysNvRamGet
    (
    char *string,    /* where to copy non-volatile RAM    */
    int strLen,      /* maximum number of bytes to copy   */
    int offset       /* byte offset into non-volatile RAM */
    )
    {
    offset += NV_BOOT_OFFSET;   /* boot line begins at <offset> = 0 */

    if ( (offset < 0)
         || (strLen < 0)
         || ((offset + strLen) > NV_RAM_SIZE) )
        return(ERROR);

    while ( strLen-- )
        {
        *string = NV_RAM_READ (offset);
        string++, offset++;
        }
    *string = EOS;

    return(OK);
    }

/*******************************************************************************
*
* sysNvRamSet - write to non-volatile RAM
*
* This routine copies a specified string into non-volatile RAM.
*
* RETURNS: OK, or ERROR if access is outside the non-volatile RAM range.
*
* SEE ALSO: sysNvRamGet()
*/

STATUS sysNvRamSet
    (
    char *string,     /* string to be copied into non-volatile RAM */
    int strLen,       /* maximum number of bytes to copy           */
    int offset        /* byte offset into non-volatile RAM         */
    )
    {
    STATUS result = OK;
    char data=0;

    offset += NV_BOOT_OFFSET;   /* boot line begins at <offset> = 0 */

    if ( (offset < 0)
         || (strLen < 0)
         || ((offset + strLen) > NV_RAM_SIZE) )
        return ERROR;

    NV_RAM_WR_ENBL;

    while ( strLen-- )
        {
        data = *string; /* avoid any macro side effects */

        NV_RAM_WRITE (offset, data);

        /* verify data */
        if ( NV_RAM_READ (offset) != (UCHAR)data )
            {
            result = ERROR;
            goto exit;
            }
        string++, offset++;
        }

    exit:
    NV_RAM_WR_DSBL;

    return result;
    }



/*******************************************************************************
*
* sysNvRamWrEnabl - enable writes to eeprom.
*
* See the Catalyst Semiconductor CAT28LV64 64K-Bit (8Kx8) CMOS PARALLEL EEPROM
* datasheet for details.
*
* RETURNS: N/A.
*
* NOMANUAL
*/

void sysNvRamWrEnbl(void)
    {
    volatile UINT8 *ptr = (UINT8*)NV_RAM_ADRS ;
    *(ptr+0x1555) = 0xaa;
    *(ptr+0x0aaa) = 0x55;
    *(ptr+0x1555) = 0x80;
    *(ptr+0x1555) = 0xaa;
    *(ptr+0x0aaa) = 0x55;
    *(ptr+0x1555) = 0x20;
    EIEIO;
    /* 5ms delay */
    taskDelay(5);
    }

/*******************************************************************************
*
* sysNvRamWrDsbl - disable writes to eeprom.
*
* RETURNS: N/A.
*
* NOMANUAL
*/

void sysNvRamWrDsbl(void)
    {
    volatile UINT8 *ptr = (UINT8*)NV_RAM_ADRS ;
    *(ptr+0x1555) = 0xaa;
    *(ptr+0x0aaa) = 0x55;
    *(ptr+0x1555) = 0xa0;
    EIEIO;
    taskDelay(5);
    }

/*******************************************************************************
*
* sysNvRamWrite - write to eeprom.
*
* RETURNS: N/A.
*
* NOMANUAL
*/

void sysNvRamWrite
    (
    int offset, 
    UINT8 data
    )
    {
    volatile UINT8 *ptr = (UINT8*)(NV_RAM_ADRS+offset) ;
    *ptr = data ;
    EIEIO;
    while ( *ptr != data );
    }

/*******************************************************************************
*
* sysNvRamRead - read from eeprom.
*
* RETURNS: N/A.
*
* NOMANUAL
*/

UINT8 sysNvRamRead
    (
    int offset
    )
    {
    volatile UINT8 * ptr = ((UINT8*)(NV_RAM_ADRS+offset));
    return(*ptr);
    }



