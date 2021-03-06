/* usbPciStub.c - USB Configuration File */

/* Copyright 1999-2005, 2007, 2009 Wind River Systems, Inc. */

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
#include <vxWorks.h>
#include "config.h"

#if defined (INCLUDE_FSL_TCD)

#include "usb/usbPlatform.h"   /* Basic definitions */
#include "usb/usbPciLib.h"     /* Our API */
#include "usbMpc8349.h"

UINT32 usbPciMemioOffset
    (
    void
    )
    {
    return (0);
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
    pVOID param,                    /* parameter for int handler */
    UINT16 intNo                    /* interrupt vector number */
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
* fslUsbDrDeviceHwInit - initialize hardware configuration for device module
*
* This routine initializes the hardware configuration related to device module,
* such as clock ratio,etc.
*
* RETURNS: N/A
*/

VOID fslUsbDrDeviceHwInit 
    (
    VOID
    )
    {
    UINT32 ioBase = MPC8349_DR_CCSBAR;

    /* Reference Board Initialization */

    if (((*MPC8349_DR_BCSR5) & MPC8349_DR_BCSR5_INT_USB) == 0)
        {
        /* This is when PIB board is plugged in */
        
        *MPC8349_DR_BCSR5 |= MPC8349_DR_BCSR5_INT_USB;
        }

    /* 1:3 clk ratio */
    
    *MPC8349_DR_SCCR(ioBase) &= ~(MPC8349_DR_SCCR_USB_MPHCM_DRCM_MASK);
    
    /* TODO: Would 1:1 clk have better performance ? */

    *MPC8349_DR_SCCR(ioBase) |=   MPC8349_DR_SCCR_USB_MPHCM_DRCM_1_3;

    /* Make sure USBDR pins are available */

    /* Choose pin function 1 for DR pins */
    
    *MPC8349_DR_SICRL(ioBase) |=
        MPC8349_DR_SICRL_USB_PORT_0 | MPC8349_DR_SICRL_USB_PORT_1;
    
    /* Choose pin function 1 for DR pins DR_TERM_SEL, DR_OPMODE1, DR_OPMODE0 */
    
    *MPC8349_DR_SICRH(ioBase) |= MPC8349_DR_SICRH_TSEC2_F;

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
    UINT8 busNo,		/* Bus number of device */
    UINT8 deviceNo,		/* Device number of device */
    UINT8 funcNo,		/* Function number of device */
    UINT16 regOffset		/* Offset into PCI config space */
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
    UINT8 busNo,		/* Bus number of device */
    UINT8 deviceNo,		/* Device number of device */
    UINT8 funcNo,		/* Function number of device */
    pPCI_CFG_HEADER pCfgHdr	/* Buffer provided by caller */
    )
    {

    /* Do nothing if CfgHdr is NULL */
    
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
    return (retStat);
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
    return (retStat);
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
    return (void *)(pciAdrs);

    }
#endif /* INCLUDE_FSL_TCD */
