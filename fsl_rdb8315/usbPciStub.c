/* usbPciStub.c - USB Configuration File */

/*
 * Copyright (c) 2003, 2005-2007, 2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01e,09sep09,s_z  Integrate the USB TCD support by INCLUDE_FSL_TCD(WIND00180575)
01d,17oct07,ami  USB vxBusSupport added (Defect WIND00108412)
01c,26Oct06,jrp  CQ69944. Added dummy function for compatability
01b,16aug05,dtr  Update comments.
01a,11aug03,cfc  Support for USB2 Host Stack
*/

/*
DESCRIPTION

This configlette initializes a USB Host Controller Interface (EHCI)

INCLUDE FILES: usb/pciConstants.h, usb/usbPciLib.h
*/

/* includes */
#include "vxWorks.h"
#include "config.h"

#include "usb/usbPlatform.h"	    /* Basic definitions */
#include "usb/usbPciLib.h"	    /* Our API */

#if defined (INCLUDE_FSL_TCD)

#include "usbMpc8313.h"

/***************************************************************************
*
* fslUsbDrDeviceHwInit - initialize hardware configuration for device module
*
* This routine initializes the hardware configuration related to device module.
*
* RETURNS: N/A
*/


VOID fslUsbDrDeviceHwInit 
    (
    VOID
    )
    {
    UINT32 ioBase = MPC8313_DR_CCSBAR;

    
    *MPC8313_DR_SCCR(ioBase) |=   0x00300000;

    *MPC8313_DR_CONTROL(ioBase) = 0x00000280;
	
    while((*MPC8313_DR_CONTROL(ioBase) & 0x00020000) ==0)
	;

    /* Make sure USBDR pins are available */

    /* Choose pin function 1 for DR pins */

    *MPC8313_DR_SICRL(ioBase) = 0x00000800;

    /* Choose pin function 1 for DR pins DR_TERM_SEL, DR_OPMODE1, DR_OPMODE0 */

    *MPC8313_DR_SICRH(ioBase) &= 0xffffff1f;

    *MPC8313_DR_SICRH(ioBase) |= 0x000000a0;
    
    return;
    }


UINT16 usbPciWordIn
    (
    UINT32 pMem                  /* memory address to convert */
    ) 
    {
    return *(UINT32*)pMem;
    }

UINT32 usbPciDwordIn
    (
    UINT32 pMem                  /* memory address to convert */
    ) 
    {
    return *(UINT32*)pMem;
    }

UINT8 usbPciByteIn
    (
    UINT32 pMem                  /* memory address to convert */
    ) 
    {
    return *(UINT32*)pMem;
    }

void usbPciWordOut
    (
    UINT32 pMem,                  /* memory address to convert */
    UINT16 data
    ) 
    {
    *(UINT32*)pMem = data;
    }

void usbPciDwordOut
    (
    UINT32 pMem,
    UINT32 data                  /* memory address to convert */
    ) 
    {
    *(UINT32*)pMem = data;
    }

void usbPciByteOut
    (
    UINT32 pMem,                  /* memory address to convert */
    UINT8 data
    ) 
    {
    *(UINT32*)pMem = data;
    }


/***************************************************************************
*
* usbPciWordGet - Returns a UINT16 configuration value
*
* This function returns the UINT16 value at offset <regOffset> from 
* the PCI configuration space of the device identified by <busNo>, 
* <deviceNo>, and <funcNo>.
*
* NOTE: This function adjusts for big vs. little endian environments.
*
* RETURNS: UINT16 value read from device configuration space
*/

UINT32 usbPciWordGet
    (
    UINT8 busNo,     /* Bus number of device */
    UINT8 deviceNo,  /* Device number of device */
    UINT8 funcNo,    /* Function number of device */
    UINT16 regOffset /* Offset into PCI config space */
    )
    {
    return 0;
    }

/***************************************************************************
*
* usbPciDwordGet - Returns a UINT32 configuration value
*
* This function returns the UINT32 value at offset <regOffset> from
* the PCI configuration space of the device identified by <busNo>,
* <deviceNo>, and <funcNo>.
*
* NOTE: This functions returns 0.  There is no configuration space on this
* board..
*
* RETURNS: UINT32 value read from device configuration space
*/

UINT32 usbPciDwordGet
    (
    UINT8 busNo,                /* Bus number of device */
    UINT8 deviceNo,             /* Device number of device */
    UINT8 funcNo,               /* Function number of device */
    UINT16 regOffset            /* Offset into PCI config space */
    )
    {
    return 0;
    }

/***************************************************************************
*
* usbPciConfigHeaderGet - Reads a device's PCI configuration header
*
* This function reads the PCI configuration header for the device
* identified by <busNo>, <deviceNo>, and <funcNo>.  The configuration
* header is stored in the <pCfgHdr> buffer provided by the caller.
*
* This function initializes the <pCfgHdr> structure to zeros.  Any 
* fields which cannot be read from the device's configuration header 
* will remain zero upon return.  This function does not attempt to read
* fields defined as "reserved" in the PCI configuration header.
*
* RETURNS: N/A
*/

VOID usbPciConfigHeaderGet
    (
    UINT8 busNo,     /* Bus number of device */
    UINT8 deviceNo,  /* Device number of device */
    UINT8 funcNo,    /* Function number of device */
    pPCI_CFG_HEADER pCfgHdr    /* Buffer provided by caller */
    )
    {
    return;
    }

/*************************************************************************
*
* usbPciIntDisable - Disables system interrupts
*
* This routine is used to disable the interrupts for IRQ specifed in 
* <nIRQNumber>.
*
* RETURNS: status of the function called to disable the interrupt
*
* ERRNO: None
*/

/* XXX this name needs to be changed */

int usbPciIntDisable
    (
    UINT16 nIRQNumber
    )
    {
    int retStat = 0;
    retStat = (int)intDisable(nIRQNumber);
    return(retStat);
    }

/*************************************************************************
*
* usbPciIntEnable - Enable system interrupts
*
* This routine is used to enable the interrupts for IRQ specifed in 
* <nIRQNumber>.
*
* RETURNS: status of the function called to enable the interrupt
*
* ERRNO: none
*/

/* XXX this name needs to be changed */

int usbPciIntEnable
    (
    UINT16 nIRQNumber
    )
    {
    int retStat = 0;
    retStat = (int)intEnable(nIRQNumber);
    return(retStat);
    }

/***************************************************************************
*
* usbPciIntConnect - Connect to a interrupt vector
*
* Connects the <func> to the interrupt number <intNo>.  <param> is an
* application-specific value which will be passed to <func> each time
* the interrupt handler is invoked.
*
* RETURNS: OK, or ERROR if unable to connect/enable interrupt
*/

STATUS usbPciIntConnect
    (
    VOIDFUNCPTR func,     /* new interrupt handler */
    pVOID param,          /* parameter for int handler */
    UINT16 intNo          /* interrupt vector number */
    )

    {
    UINT32 vec = (UINT32)intNo ;

    if (intConnect((VOIDFUNCPTR *)vec, func, (int)param) != OK)
        return ERROR;

    if (intEnable(vec) != OK)
        {
        return ERROR;
        }

    return OK;
    }

/***************************************************************************
*
* usbMemToPci - Convert a memory address to a PCI-reachable memory address
*
* Converts <pMem> to an equivalent 32-bit memory address visible from the
* PCI bus.  This conversion is necessary to allow PCI bus masters to address
* the same memory viewed by the processor.
*
* RETURNS: converted memory address
*/

UINT32 usbMemToPci
    (
    pVOID pMem                  /* memory address to convert */
    )

    {

    /* The conversion is a two-step process.  First, we need to convert the
     * logical processor address (virtual) to a physical address.  Then, we
     * convert the physical address to one which can be seen from the PCI
     * bus.
     */

    /* 1:1 */
    return (UINT32)pMem ;

    }

/***************************************************************************
*
* usbPciToMem - Convert a PCI-reachable address to a CPU-reachable pointer
*
* Converts <pciAdrs> to an equivalent CPU memory address.
*
* RETURNS: pointer to PCI memory
*/

pVOID usbPciToMem
    (
    UINT32 pciAdrs              /* 32-bit PCI address to be converted */
    )

    {

    /* 1:1 */
    return(void *)(pciAdrs);

    }

UINT32 usbPciMemioOffset
    (
    void
    )
    {
    return(0);
    }

/***************************************************************************
*
* usbPciIntDisconnect - Removes an interrupt handler
*
* Removes an interrupt handler installed by usbPciIntConnect().  <func>,
* <param>, and <intNo> must match the corresponding parameters from an earlier
* call to usbPciIntConnect().
*
* RETURNS: N/A
*/

VOID usbPciIntRestore
    (
    VOIDFUNCPTR func,     /* int handler to be removed */
    pVOID param,                    /* parameter for int handler */
    UINT16 intNo                    /* interrupt vector number */
    )

    {
    UINT32 vec = (UINT32)intNo ;
    intDisable(vec);
    }

/***************************************************************************
*
* usbPciMemInvalidate - Invalidate cache for a region of memory
*
* When another bus master, such as a PCI bus master, writes to memory, the
* cache may need to be invalidated for that region of memory.
*
* NOTE: Returns immediately if size == 0.
*
* RETURNS: N/A
*/

VOID usbPciMemInvalidate
    (
    pVOID pMem,    /* base of memory region to invalidate */
    UINT32 size    /* size of region to invalidate */
    )

    {
    if (size != 0)
        CACHE_USER_INVALIDATE (pMem, size);
    }


/***************************************************************************
*
* usbPciMemFlush - Flush a region of memory through the cache
*
* In systems which implement a non-write-thru cache, the processor may have
* written data to memory which has not yet been flushed to the actual system
* memory.  Before other bus masters may interrogate this memory, it may be
* necessary to flush the cache.
*
* NOTE: Returns immediately if size == 0.
*
* RETURNS: N/A
*/

VOID usbPciMemFlush
    (
    pVOID pMem,    /* base of memory region to invalidate */
    UINT32 size    /* size of region to invalidate */
    )

    {
    if (size != 0)
        CACHE_USER_FLUSH (pMem, size);
    }

#endif /* INCLUDE_FSL_TCD */

