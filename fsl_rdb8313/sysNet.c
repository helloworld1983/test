/* sysNet.c - system-dependent Network Library */

/*
 * Copyright (c) 2005-2008, 2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,24nov10,swu changed glbEnetAddr array size.(WIND00226757)
01e,03mar08,z_l changed device name.
01d,09jul07,l_g modified for fsl_rdb8313
01c,04mar07,d_z Correct vendor code for the MAC address.(CQ:86932)
01b,18aug06,dtr WIND61530 - replace magic numbers.
01a,05jul05,dtr adopted from sbc8260/sysNet.c/01a
*/

/*
DESCRIPTION

This module provides BSP functionality to support the
bootrom 'M' command to modify MAC addresses of on-board
network interfaces.

MAC adddress routines provided by the BSP in this file are:
    sysNetMacNVRamAddrGet()
    sysNetMacAddrGet()
    sysNetMacAddrSet()

This board provides storage in flash for the MAC addresses
of the motfcc and motscc interfaces.  This library also
implements a RAM buffer to represent the contents of the
flash.  The RAM buffer contains eight entries, which is
more than currently needed by this board, but can be
considered as room for expansion in future boards using
a derivative of this BSP.  This RAM buffer is contained
in the array glbEnetAddr[][].
*/

#ifdef ETHERNET_MAC_HANDLER

#include <vxWorks.h>
#include "config.h"

#ifndef MAX_MAC_DEVS
#   define MAX_MAC_DEVS     1 
#endif /* MAX_MAC_DEVS */

#define MAC_OFFSET_MOTTSEC  0
#define MAX_MAC_ADRS        2

const char *sysNetDevName[MAX_MAC_DEVS] = {"motetsec"};

IMPORT int dynamicMacAddrGen
    (
    UINT8 * ifName,         /* interface name */
    int     ifUnit,         /* interface unit */
    UINT8 * ifMacAddr,      /* address buffer */
    int     ifMacAddrLen    /* length of buffer */
    );

/* locals */

LOCAL UINT8 glbEnetAddr[MAX_MAC_ADRS][MAC_ADRS_LEN + 1] = 
    {
    { WR_ENET0, WR_ENET1, WR_ENET2, CUST_ENET3_0, CUST_ENET4, CUST_ENET5, 0 },
    { WR_ENET0, WR_ENET1, WR_ENET2, CUST_ENET3_1, CUST_ENET4, CUST_ENET5, 0 }
    };

LOCAL UINT8 sysInvalidAddr[2][MAC_ADRS_LEN] = 
    {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }
    };

/*******************************************************************************
*
* sysMacOffsetGet - Calculate table offset
*
*  This routine calculates which table entry corresponds to
*  the specified interface.
*
*  Two values are calculated and returned in the parameters
*  pointed to by ppEnet and pOffset.
*
* RETURNS: ERROR if the interface is not known; OK otherwise
*/

STATUS sysMacOffsetGet
    (
    char *    ifName,        /* interface name */
    int       ifUnit,        /* interface unit */
    char **   ppEnet,        /* pointer to glbEnetAddr[][] entry */
    int *     pOffset        /* offset in NVRAM */
    )
    {

    /*
     * The address offsets into NVRAM and glbEnetAddr[] are:
     *
     *    motetsec0 - offset 0
     *
     */

    if (strcmp(ifName, "motetsec") == 0)
        {
        if (ifUnit > 1)
            return (ERROR);
        *pOffset = ifUnit * MAC_ADRS_LEN;
        *ppEnet  = (char *)glbEnetAddr[ifUnit + MAC_OFFSET_MOTTSEC];
        }
    else
        return (ERROR);

    return (OK);
    }

/*******************************************************************************
*
* sysNetMacNVRamAddrGet - Get interface MAC address
*
*  This routine gets the current MAC address from the
*  Non Volatile RAM, and store it in the ifMacAddr
*  buffer provided by the caller.
*
*  It is not required for the BSP to provide NVRAM to store
*  the MAC address.  Also, some interfaces do not allow
*  the MAC address to be set by software.  In either of
*  these cases, this routine simply returns ERROR.
*
*  Given a MAC address m0:m1:m2:m3:m4:m5, the byte order
*  of ifMacAddr is:
*    m0 @ ifMacAddr
*    m1 @ ifMacAddr + 1
*    m2 @ ifMacAddr + 2
*    m3 @ ifMacAddr + 3
*    m4 @ ifMacAddr + 4
*    m5 @ ifMacAddr + 5
*
* RETURNS: OK, if MAC address available, ERROR otherwise
*/

STATUS sysNetMacNVRamAddrGet
    (
    char *    ifName,
    int       ifUnit,
    UINT8 *   ifMacAddr,
    int       ifMacAddrLen
    )
    {
    int     offset;
    char *  pEnet;

    /* fetch address line & offset from glbEnetAddr[] table */
    
    if (sysMacOffsetGet(ifName, ifUnit, &pEnet, &offset) != OK)
        return(ERROR);

#if (NV_RAM_SIZE != NONE)

    /* get MAC address from NvRAM. */

    sysNvRamGet (pEnet, ifMacAddrLen, NV_MAC_ADRS_OFFSET + offset);

#endif /* (NV_RAM_SIZE != NONE) */

    if ( memcmp(pEnet, sysInvalidAddr[0], MAC_ADRS_LEN) == 0 )
        return(ERROR);
    if ( memcmp(pEnet, sysInvalidAddr[1], MAC_ADRS_LEN) == 0 )
        return(ERROR);

    /* mac address in memory only */
    
    memcpy (ifMacAddr, pEnet, ifMacAddrLen);

    return (OK);
    }

/*******************************************************************************
*
* sysNetMacAddrGet - Get interface MAC address
*
*  This routine gets the current MAC address from the
*  network interface, and stores it in the ifMacAddr
*  buffer provided by the caller.
*
*  If the network interface cannot be queried about the
*  MAC address, this routine returns ERROR.
*
* RETURNS: OK, if MAC address available, ERROR otherwise
*/

STATUS sysNetMacAddrGet
    (
    char *    ifName,
    int       ifUnit,
    UINT8 *   ifMacAddr,
    int       ifMacAddrLen
    )
    {
    /*
     * None of our interfaces can be queried directly.
     * Return ERROR to indicate that we need to use
     * RAM/NVRAM instead.
     */
    return(ERROR);
    }

/*******************************************************************************
*
* sysNetMacAddrSet - Save interface MAC address
*
*  This routine saves the MAC address specified in
*  ifMacAddr to the appropriate location in NVRam (if
*  possible) and update the specified interface to use
*  the specified MAC address.
*
*  If the network interface MAC address cannot be set,
*  this routine returns ERROR.
*
* RETURNS: OK, if MAC address available, ERROR otherwise
*/

STATUS sysNetMacAddrSet
    (
    char *    ifName,
    int       ifUnit,
    UINT8 *   ifMacAddr,
    int       ifMacAddrLen
    )
    {
    int     offset;
    char *  pEnet;

    /* fetch address line & offset from glbEnetAddr[] table */

    if (sysMacOffsetGet(ifName, ifUnit, &pEnet, &offset) != OK)
        return(ERROR);

#if (NV_RAM_SIZE != NONE)

    /* check MAC address in NvRAM. */

    sysNvRamGet (pEnet, ifMacAddrLen, NV_MAC_ADRS_OFFSET + offset);
    if (0 == memcmp (ifMacAddr, pEnet, ifMacAddrLen))
        { 
            
        /* same address so don't erase and rewrite flash */
    
        printf("Address unchanged\n");
        return (OK);
        }

    sysNvRamSet ((char *)ifMacAddr, ifMacAddrLen, NV_MAC_ADRS_OFFSET + offset);
#endif /* (NV_RAM_SIZE != NONE) */

    /* mac address in memory only */

    memcpy (ifMacAddr, pEnet, ifMacAddrLen);

    return (OK);
    }

/*******************************************************************************
*
* sysMacIndex2Unit - convert index range to unit number
*
* This routine converts an index range 0..MAX_MAC_ADRS-1
* to a unit number.
*
* RETURNS: unit number of indexed device
*
* ERRNO
*/

int sysMacIndex2Unit
    (
    int index
    )
    {
    return (index);   /* remaining three are motfcc (0,1,2) */
    }

/*******************************************************************************
*
* sysMacIndex2Dev - convert index range to device string
*
* This routine converts an index range 0..MAX_MAC_ADRS-1
* to a device string index e.g. motfcc.
*
* RETURNS: index access device name in sysNetDevName
*
* ERRNO
*/

int sysMacIndex2Dev
    (
    int index
    )
    {
    return (0);      /* remaining are motfcc */
    }
    
#ifdef ENET_MAC_DEBUG

/*******************************************************************************
*
* sysNetMacAddrClear - clear MAC address in FLASH/NVRAM
*
*  This routine clears the storage locations in NVRAM
*  reserved for the MAC address of the specified interface.
*
*  This is useful for debugging the 'M' command.  To use
*  this, boot vxWorks and run sysNetMacAddrClear() from
*  the shell.  After running this command, you can test
*  the bootrom 'M' command under conditions similar to a
*  new, unprogrammed board.
*
* RETURNS: OK, if MAC address available, ERROR otherwise
*/

int sysNetMacAddrClear
    (
    char *    ifName,
    int       ifUnit
    )
    {
    UINT8  ifMacAddr [MAC_ADRS_LEN] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
    int    offset;
    char * pEnet;

    if (sysMacOffsetGet(ifName, ifUnit, &pEnet, &offset) != OK)
        return(ERROR);

    sysNvRamSet (ifMacAddr, MAC_ADRS_LEN, NV_MAC_ADRS_OFFSET + offset);
    memcpy (ifMacAddr, pEnet, MAC_ADRS_LEN);
    
    return(0);
    }
#endif /* ENET_MAC_DEBUG */

#endif /* ETHERNET_MAC_HANDLER */
