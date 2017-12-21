/* p1010rdb.h - Freescale P1010RDB board header */

/*
 * Copyright (c) 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,05mar12,y_y  add vxBus I2C support.
01a,19sep11,fao  derived from version 01b of fsl_p1020_rdb/p1020rdb.h
*/

/*
 * This file contains I/O addresses and related constants for the
 * Freescale P1010RDB board.
*/

#ifndef __INCp1010rdbh
#define __INCp1010rdbh

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

#ifdef  _ASMLANGUAGE
#   define CAST(x)
#else /* _ASMLANGUAGE */
typedef volatile UCHAR  VCHAR;      /* shorthand for volatile UCHAR */
typedef volatile INT32  VINT32;     /* volatile unsigned word */
typedef volatile INT16  VINT16;     /* volatile unsigned halfword */
typedef volatile INT8   VINT8;      /* volatile unsigned byte */
typedef volatile UINT32 VUINT32;    /* volatile unsigned word */
typedef volatile UINT16 VUINT16;    /* volatile unsigned halfword */
typedef volatile UINT8  VUINT8;     /* volatile unsigned byte */
#   define CAST(x) (x)
#endif  /* _ASMLANGUAGE */

/* Base Address of Memory Mapped Registers */

#define CCSBAR_RESET            0xff700000
#define CCSBAR                  0xffe00000
#define CCSR_SIZE               0x00100000

#define MP_MAGIC_RBV            0xfeedfeed

#define M85XX_ALTCBAR(base)     (CAST(VUINT32 *)((base) + 0x08))
#define M85XX_ALTCAR(base)      (CAST(VUINT32 *)((base) + 0x10))
#define M85XX_BPTR(base)        (CAST(VUINT32 *)((base) + 0x20))

#define BPTR_EN                 0x80000000

/*
 * Space for the SMP-reboot detection structure.  This should go in
 * memory with the same volatility as DRAM -- i.e. it will survive
 * a reset via the PIXIS but not a power-cycle.  It would be nice
 * for it to be accessible without setting up the DRAM controller,
 * but absent knowledge of any such space on the board we'll just
 * put it in DRAM (and therefore it can't be tested until after the
 * DRAM controller has been set up).
 */

#define RBV_ADRS                (RAM_LOW_ADRS - 16)

/*
 * Structure written at RBV_ADRS by SMP sysToMonitor when rebooting
 * with multiple processors running, examined by romInit to detect
 * an SMP warm boot.  The assembly version is defined for all builds,
 * because a non-SMP bootrom should work with an SMP vxWorks.
 */

#ifdef  _ASMLANGUAGE
#   define OFF_RBV_STARTTYPE    0
#   define OFF_RBV_MAGIC1       4
#   define OFF_RBV_MAGIC2       8
#   define OFF_RBV_MAGIC3       12
#endif  /* _ASMLANGUAGE */

/* SOC PVR and SVR */

#define PPC_PVR_85XX            0x80200000
#define PPC_PVR_MASK            0xFFF00000

#define PPC_SVR_P2020           0x80E00000
#define PPC_SVR_MASK            0xFFF00000

/* Define Clock Speed and source  */

#define FREQ_33_MHZ             33333300
#define FREQ_66_MHZ             66666600
#define FREQ_50_MHZ             50000000
#define FREQ_100_MHZ            100000000
#define FREQ_500_MHZ            500000000

#define DEFAULT_SYS_CLK_FREQ    FREQ_100_MHZ
#define DDR_CLK_FREQ            FREQ_66_MHZ

#define DEFAULT_SYSCLKFREQ      FREQ_500_MHZ

#define PLAT_RATIO_800_MHZ      20
#define PLAT_RATIO_533_MHZ      16
#define PLAT_RATIO_400_MHZ      12
#define PLAT_RATIO_333_MHZ      8

/* Clock rates */

#define SYS_CLK_RATE_MIN        1       /* minimum system clock rate */
#define SYS_CLK_RATE_MAX        8000    /* maximum system clock rate */

#define AUX_CLK_RATE_MIN        1
#define AUX_CLK_RATE_MAX        50000
#define AUX_CLK_RATE            20000

/* Frequency applied to the  "RTC" pin */

#define HPCN_RTC_FREQ           32768000

/* possibly this is not supported check your DDR undefined for safety */

#undef  INCLUDE_DDR_ECC

/* 60x bus adrs to PCI (non-prefetchable) memory address */

#define LOCAL2PCI_MEMIO(x)      ((int)(x) + PCI_MSTR_MEM_BUS)

#define ETHERNET_MAC_HANDLER

#define WR_ENET0                0x00  /* WR specific portion of MAC (MSB->LSB) */
#define WR_ENET1                0xA0
#define WR_ENET2                0x1E

#define CUST_ENET3_0            0xA0  /* Customer portion of MAC address */
#define CUST_ENET3_1            0xA1
#define CUST_ENET3_2            0xA2
#define CUST_ENET3_3            0xA3
#define CUST_ENET4              0xAA
#define CUST_ENET5              0xA0

#define MAX_MAC_ADRS            3
#define MAC_ADRS_LEN            6
#define NV_MAC_ADRS_OFFSET      0x200

/* OpenPic timer vector definition */

#define OPENPIC_TIMERA0_INT_VEC 0x4C
#define OPENPIC_TIMERA1_INT_VEC 0x4D
#define OPENPIC_TIMERA2_INT_VEC 0x4E
#define OPENPIC_TIMERA3_INT_VEC 0x4F
#define OPENPIC_TIMERB0_INT_VEC 0x50
#define OPENPIC_TIMERB1_INT_VEC 0x51
#define OPENPIC_TIMERB2_INT_VEC 0x52
#define OPENPIC_TIMERB3_INT_VEC 0x53

/*
 * Local Access Windows Regster Offsets from CCSBAR
 *
 * LAWBARx
 * 0-11 Reserved - read 0
 * 12-31 Base address - Most significant 20 bits
 *
 * LAWARx
 * 0   Enable window
 * 1-7 Reserved
 * 8-11 Target interface - 0000 PCI/PCI-X
 *                       - 0001 PCIEX2
 *                       - 0010 PCIEX1
 *                       - 0011 PCIEX3
 *                       - 0011 Reserved
 *                       - 0100 Local Bus memory controller eg SDRAM/L2SRAM
 *                       - 0101 -> 1011 Reserved
 *                       - 1100 Rapid IO
 *                       - 1101 -> 1110 Reserved
 *                       - 1111 DDR SDRAM
 * 12-25 Reserved - read 0
 * 26-31 Size of Window  - min 001011 -> 4KBytes
 *                         step power of 2
 *                       - max 011110 -> 2 Gbytes
 */

/* Used for Nor Flash */

#define  M85XX_LAWBAR0(base)    (CAST(VUINT32 *)((base) + 0xc08))
#define  M85XX_LAWAR0(base)     (CAST(VUINT32 *)((base) + 0xc10))

/* Used for DDR-III RAM */

#define  M85XX_LAWBAR1(base)    (CAST(VUINT32 *)((base) + 0xc28))
#define  M85XX_LAWAR1(base)     (CAST(VUINT32 *)((base) + 0xc30))

/* Used for PCIEX2_MEM, PCIEX2_MEM_IO, PCIEX2_IO  */

#define  M85XX_LAWBAR2(base)    (CAST(VUINT32 *)((base) + 0xc48))
#define  M85XX_LAWAR2(base)     (CAST(VUINT32 *)((base) + 0xc50))

/* Used for CPLD */

#define  M85XX_LAWBAR3(base)    (CAST(VUINT32 *)((base) + 0xc68))
#define  M85XX_LAWAR3(base)     (CAST(VUINT32 *)((base) + 0xc70))

/* Unused */

#define  M85XX_LAWBAR4(base)    (CAST(VUINT32 *)((base) + 0xc88))
#define  M85XX_LAWAR4(base)     (CAST(VUINT32 *)((base) + 0xc90))

/* Unused */

#define  M85XX_LAWBAR5(base)    (CAST(VUINT32 *)((base) + 0xca8))
#define  M85XX_LAWAR5(base)     (CAST(VUINT32 *)((base) + 0xcb0))

/* Unused */

#define  M85XX_LAWBAR6(base)    (CAST(VUINT32 *)((base) + 0xcc8))
#define  M85XX_LAWAR6(base)     (CAST(VUINT32 *)((base) + 0xcd0))

/* Unused */

#define  M85XX_LAWBAR7(base)    (CAST(VUINT32 *)((base) + 0xce8))
#define  M85XX_LAWAR7(base)     (CAST(VUINT32 *)((base) + 0xcf0))

/* Unused */

#define  M85XX_LAWBAR8(base)    (CAST(VUINT32 *)((base) + 0xd08))
#define  M85XX_LAWAR8(base)     (CAST(VUINT32 *)((base) + 0xd10))

/* Unused */

#define  M85XX_LAWBAR9(base)    (CAST(VUINT32 *)((base) + 0xd28))
#define  M85XX_LAWAR9(base)     (CAST(VUINT32 *)((base) + 0xd30))


/* Unused */

#define  M85XX_LAWBAR10(base)   (CAST(VUINT32 *)((base) + 0xd48))
#define  M85XX_LAWAR10(base)    (CAST(VUINT32 *)((base) + 0xd50))

/* Unused */

#define  M85XX_LAWBAR11(base)   (CAST(VUINT32 *)((base) + 0xd68))
#define  M85XX_LAWAR11(base)    (CAST(VUINT32 *)((base) + 0xd70))

#define  LAWBAR_ADRS_SHIFT      12
#define  LAWAR_ENABLE           0x80000000
#define  LAWAR_TGTIF_PCIEX3     0x00000000
#define  LAWAR_TGTIF_PCIEX2     0x00100000
#define  LAWAR_TGTIF_PCIEX1     0x00200000
#define  LAWAR_TGTIF_LBC        0x00400000
#define  LAWAR_TGTIF_RAPIDIO    0x00C00000
#define  LAWAR_TGTIF_RAPIDIO2   0x00D00000
#define  LAWAR_TGTIF_DDRSDRAM   0x00F00000

/* LAWAR SIZE Settings */

#define  LAWAR_SIZE_4KB         0x0000000B
#define  LAWAR_SIZE_8KB         0x0000000C
#define  LAWAR_SIZE_16KB        0x0000000D
#define  LAWAR_SIZE_32KB        0x0000000E
#define  LAWAR_SIZE_64KB        0x0000000F
#define  LAWAR_SIZE_128KB       0x00000010
#define  LAWAR_SIZE_256KB       0x00000011
#define  LAWAR_SIZE_512KB       0x00000012
#define  LAWAR_SIZE_1MB         0x00000013
#define  LAWAR_SIZE_2MB         0x00000014
#define  LAWAR_SIZE_4MB         0x00000015
#define  LAWAR_SIZE_8MB         0x00000016
#define  LAWAR_SIZE_16MB        0x00000017
#define  LAWAR_SIZE_32MB        0x00000018
#define  LAWAR_SIZE_64MB        0x00000019
#define  LAWAR_SIZE_128MB       0x0000001A
#define  LAWAR_SIZE_256MB       0x0000001B
#define  LAWAR_SIZE_512MB       0x0000001C
#define  LAWAR_SIZE_1GB         0x0000001D
#define  LAWAR_SIZE_2GB         0x0000001E

#define  M85XX_UART_THR0(base)   (CAST(VUINT32 *)((base) + 0x4500))

/* Incomplete LSDMR definitions */

#define  M85XX_LURT(base)       (CAST(VUINT32 *)((base) + 0x50A0))
#define  M85XX_LSRT(base)       (CAST(VUINT32 *)((base) + 0x50A4))
#define  M85XX_LTESR(base)      (CAST(VUINT32 *)((base) + 0x50B0))
#define  M85XX_LTEDR(base)      (CAST(VUINT32 *)((base) + 0x50B4))
#define  M85XX_LTEIR(base)      (CAST(VUINT32 *)((base) + 0x50B8))
#define  M85XX_LTEATR(base)     (CAST(VUINT32 *)((base) + 0x50BC))
#define  M85XX_LTEAR(base)      (CAST(VUINT32 *)((base) + 0x50C0))

#define  M85XX_DCR0(base)       (CAST(VUINT32 *)((base) + 0xe0f1c))
#define  M85XX_DCR1(base)       (CAST(VUINT32 *)((base) + 0xe0f20))

#define CPU1CHECK               (vxHid1Get() & 0x1)

/* ECM Registers */

#define ECM_OFFSET              0x1000
#define ECMBA                   (CCSBAR + ECM_OFFSET)

#define EEB_ABCR(base)          (CAST(VUINT32 *)((base) + ECM_OFFSET + 0x0))
#define EEB_DBCR(base)          (CAST(VUINT32 *)((base) + ECM_OFFSET + 0x8))
#define EEB_PCR(base)           (CAST(VUINT32 *)((base) + ECM_OFFSET + 0x10))
#define EEB_REV1(base)          (CAST(VUINT32 *)((base) + ECM_OFFSET + 0xBF8))
#define EEB_REV2(base)          (CAST(VUINT32 *)((base) + ECM_OFFSET + 0xBFC))
#define EEB_EDR(base)           (CAST(VUINT32 *)((base) + ECM_OFFSET + 0xE00))
#define EEB_EER(base)           (CAST(VUINT32 *)((base) + ECM_OFFSET + 0xE08))
#define EEB_EATR(base)          (CAST(VUINT32 *)((base) + ECM_OFFSET + 0xE0C))
#define EEB_ELADR(base)         (CAST(VUINT32 *)((base) + ECM_OFFSET + 0xE10))
#define EEB_EHADR(base)         (CAST(VUINT32 *)((base) + ECM_OFFSET + 0xE14))

#define EEB_PCR_CORE1_ENABLE    0x02000000
#define EEB_PCR_CORE0_ENABLE    0x01000000

/* Offsets for IFC registers */

#define IFC_OFFSET              0x1E000
#define IFC                     (CCSBAR + IFC_OFFSET)

#define IFC_CSPR0               0x010
#define IFC_CSPR1               0x01C
#define IFC_CSPR2               0x028
#define IFC_CSPR3               0x034
#define IFC_AMASK0              0x0A0
#define IFC_AMASK1              0x0AC
#define IFC_AMASK2              0x0B8
#define IFC_AMASK3              0x0C4
#define IFC_CSOR0               0x130 
#define IFC_CSOR1               0x13C 
#define IFC_CSOR2               0x148 
#define IFC_CSOR3               0x154 
#define IFC_FTIM0_CS0           0x1C0 
#define IFC_FTIM1_CS0           0x1C4 
#define IFC_FTIM2_CS0           0x1C8 
#define IFC_FTIM3_CS0           0x1CC 
#define IFC_FTIM0_CS1           0x1F0 
#define IFC_FTIM1_CS1           0x1F4 
#define IFC_FTIM2_CS1           0x1F8 
#define IFC_FTIM3_CS1           0x1FC 
#define IFC_FTIM0_CS2           0x220 
#define IFC_FTIM1_CS2           0x224 
#define IFC_FTIM2_CS2           0x228 
#define IFC_FTIM3_CS2           0x22C 
#define IFC_FTIM0_CS3           0x250 
#define IFC_FTIM1_CS3           0x254 
#define IFC_FTIM2_CS3           0x258 
#define IFC_FTIM3_CS3           0x25C 
#define IFC_GCR                 0x40C 
                                
/* Offsets for DDR registers */

#define DDR_OFFSET              0x2000
#define DDRBA                   (CCSBAR | DDR_OFFSET)

#define CS0_BNDS                0x000
#define CS1_BNDS                0x008
#define CS2_BNDS                0x010
#define CS3_BNDS                0x018
#define CS0_CONFIG              0x080
#define CS1_CONFIG              0x084
#define CS2_CONFIG              0x088
#define CS3_CONFIG              0x08C
#define CS0_CONFIG_2            0x0c0
#define CS1_CONFIG_2            0x0c4
#define CS2_CONFIG_2            0x0c8
#define CS3_CONFIG_2            0x0CC
#define TIMING_CFG_3            0x100
#define TIMING_CFG_0            0x104
#define TIMING_CFG_1            0x108
#define TIMING_CFG_2            0x10C
#define DDR_SDRAM_CFG           0x110
#define DDR_SDRAM_CFG_2         0x114
#define DDR_SDRAM_MODE_CFG      0x118
#define DDR_SDRAM_MODE_CFG_2    0x11c
#define DDR_SDRAM_MD_CNTL       0x120
#define DDR_SDRAM_INTERVAL      0x124
#define DDR_DATA_INIT           0x128
#define DDR_SDRAM_CLK_CTRL      0x130
#define DDR_INIT_ADDR           0x148
#define DDR_INIT_EXT_ADDRESS    0x14C
#define TIMING_CFG_4            0x160
#define TIMING_CFG_5            0x164
#define DDR_DDR_ZQ_CNTL         0x170
#define DDR_DDR_WRLVL_CNTL      0x174
#define DDR_DDRDSR_1            0xB20
#define DDR_DDRDSR_2            0xB24
#define DDR_DDRCDR_1            0xB28
#define DDR_DDRCDR_2            0xB2C
#define DDR_DDR_IP_REV1         0xBF8
#define DDR_DDR_IP_REV2         0xBFC
#define DATA_ERR_INJECT_HI      0xE00
#define DATA_ERR_INJECT_LO      0xE04
#define ECC_ERR_INJECT          0xE08
#define CAPTURE_DATA_HI         0xE20
#define CAPTURE_DATA_LO         0xE24
#define CAPTURE_ECC             0xE28
#define ERR_DETECT              0xE40
#define ERR_DISABLE             0xE44
#define ERR_INT_EN              0xE48
#define CAPTURE_ATTRIBUTES      0xE4c
#define CAPTURE_ADDRESS         0xE50
#define ERR_SBE                 0xE58

#define DDR_IO_OVCR             0x000E0F24

/* DUART */

#define UART0_BASE                  (CCSBAR + 0x4500)
#define UART1_BASE                  (CCSBAR + 0x4600)
#define DUART_REG_ADDR_INTERVAL     1

/* NAND Flash */

#define NAND_BUFFER_BASE            0xffa00000
#define NAND_BUFFER_SIZE            0x00100000
#define NAND_PAGE_SIZE              512
#define NAND_BLOCK_SIZE             (16 * 1024)
#define NAND_PAGE_PER_BLOCK         32
#define NAND_BANK                   1

/* PCIEX */

#define PCIEX1_REGBASE              (CCSBAR + 0xa000)   /* Mini PCI-EX slot */
#define PCIEX2_REGBASE              (CCSBAR + 0x9000)   /* PCI-EX slot */

/* PCIEX interrupt level */

#define PCIEX2_XINT1_LVL            4
#define PCIEX2_XINT2_LVL            5
#define PCIEX2_XINT3_LVL            6
#define PCIEX2_XINT4_LVL            7

/* PCIEX slots number */

#define NUM_PCIEX1_SLOTS            0x1
#define NUM_PCIEX2_SLOTS            0x1

#define PCI_LAT_TIMER               0x40  /* latency timer value, 64 PCI clocks */

/* PCIEX based addresses */

#define PCIEX1_LAW_BASE             0x80000000          /* PCI LAW window */
#define PCIEX1_LAW_SIZE             0x20000000          /* PCI LAW size   */
#define PCIEX1_MEM_SIZE             0x04000000          /* 64 MB */
#define PCIEX1_MEMIO_SIZE           0x04000000          /* 64 MB */
#define PCIEX1_IO_SIZE              0x04000000          /* 64 MB */
#define PCIEX1_MEM_ADRS             (PCIEX1_LAW_BASE)
#define PCIEX1_MEMIO_ADRS           (PCIEX1_MEM_ADRS   + PCIEX1_MEM_SIZE)
#define PCIEX1_IO_ADRS              (PCIEX1_MEMIO_ADRS + PCIEX1_MEMIO_SIZE)

#define PCIEX2_LAW_BASE             0xa0000000          /* PCI LAW window */
#define PCIEX2_LAW_SIZE             0x20000000          /* PCI LAW size   */
#define PCIEX2_MEM_SIZE             0x04000000          /* 64 MB */
#define PCIEX2_MEMIO_SIZE           0x04000000          /* 64 MB */
#define PCIEX2_IO_SIZE              0x04000000          /* 64 MB */
#define PCIEX2_MEM_ADRS             (PCIEX2_LAW_BASE)
#define PCIEX2_MEMIO_ADRS           (PCIEX2_MEM_ADRS   + PCIEX2_MEM_SIZE)
#define PCIEX2_IO_ADRS              (PCIEX2_MEMIO_ADRS + PCIEX2_MEMIO_SIZE)

#define PCI_MMU_TLB_SZ              _MMU_TLB_SZ_256M

/* CPU address */

#define PCI_MSTR_MEM_BUS            LOCAL_MEM_LOCAL_ADRS
#define PCI_BRIDGE_PIMMR_BASE_ADRS  0xC0000000

/* PCI Express Host Controller */

/* ATMU register defines */

#define PCI_WINDOW_ENABLE_BIT       0x80000000
#define PCI_SNOOP_ENABLE            0x40000000
#define PCI_PREFETCHABLE            0x20000000

/* outbound window attributes */

#define PCI_OUT_ATTR_RTT_MEM        0x00040000
#define PCI_OUT_ATTR_RTT_IO         0x00080000
#define PCI_OUT_ATTR_WTT_MEM        0x00004000
#define PCI_OUT_ATTR_WTT_IO         0x00008000

#define PCI_ATTR_WS_4K              0x0000000B
#define PCI_ATTR_WS_8K              0x0000000C
#define PCI_ATTR_WS_16K             0x0000000D
#define PCI_ATTR_WS_32K             0x0000000E
#define PCI_ATTR_WS_64K             0x0000000F
#define PCI_ATTR_WS_128K            0x00000010
#define PCI_ATTR_WS_256K            0x00000011
#define PCI_ATTR_WS_512K            0x00000012
#define PCI_ATTR_WS_1M              0x00000013
#define PCI_ATTR_WS_2M              0x00000014
#define PCI_ATTR_WS_4M              0x00000015
#define PCI_ATTR_WS_8M              0x00000016
#define PCI_ATTR_WS_16M             0x00000017
#define PCI_ATTR_WS_32M             0x00000018
#define PCI_ATTR_WS_64M             0x00000019
#define PCI_ATTR_WS_128M            0x0000001A
#define PCI_ATTR_WS_256M            0x0000001B
#define PCI_ATTR_WS_512M            0x0000001C
#define PCI_ATTR_WS_1G              0x0000001D
#define PCI_ATTR_WS_2G              0x0000001E
#define PCI_ATTR_WS_4G              0x0000001F
#define PCI_ATTR_WS_8G              0x00000020
#define PCI_ATTR_WS_16G             0x00000021
#define PCI_ATTR_WS_32G             0x00000022
#define PCI_ATTR_WS_64G             0x00000023

/* inbound window attributes */

#define PCI_IN_ATTR_TGI_LM                                  0x00f00000
#define PCI_IN_ATTR_RTT_LM_READ_NO_SNOOP                    0x00040000
#define PCI_IN_ATTR_RTT_LM_READ_SNOOP                       0x00050000
#define PCI_IN_ATTR_RTT_LM_READ_UNLOCK_L2_CACHE_LINE        0x00070000
#define PCI_IN_ATTR_RTT_LM_WRITE_NO_SNOOP                   0x00004000
#define PCI_IN_ATTR_RTT_LM_WRITE_SNOOP                      0x00005000
#define PCI_IN_ATTR_RTT_LM_WRITE_ALLOC_L2_CACHE_LINE        0x00006000
#define PCI_IN_ATTR_RTT_LM_WRITE_ALLOC_LOCK_L2_CACHE_LINE   0x00007000

/* SATA */

#define SATA1_BASE                  (CCSBAR + 0x18000)
#define SATA2_BASE                  (CCSBAR + 0x19000)

/* USB */

#define USB_BASE                    (CCSBAR + 0x22000)
#define USB_PHY_BASE                (CCSBAR + 0xE5000)

/* I2C */

#define I2C1_BASE                   (CCSBAR + 0x3000)
#define I2C2_BASE                   (CCSBAR + 0x3100)

/* EHCI registers */

#define EHCI_CAPLENGTH(base)        ((base) + 0x00100)

#define EHCI_BURSTSIZE(base)        ((base) + 0x00160)
#define EHCI_TXTTFILLTUNING_L(base) ((base) + 0x00164)
#define EHCI_TXTTFILLTUNING_H(base) ((base) + 0x00168)
#define EHCI_CONFIGFLAG(base)       ((base) + 0x00180)
#define EHCI_PORTSC(base)           ((base) + 0x00184)
#define EHCI_OTGSC(base)            ((base) + 0x001a4)
#define EHCI_USBMODE(base)          ((base) + 0x001a8)

#define EHCI_SNOOP1(base)           ((base) + 0x00400)
#define EHCI_SNOOP2(base)           ((base) + 0x00404)
#define EHCI_AGE_CNT_THRESH(base)   ((base) + 0x00408)
#define EHCI_PRI_CTRL(base)         ((base) + 0x0040c)
#define EHCI_SI_CTRL(base)          ((base) + 0x00410)
#define EHCI_CONTROL(base)          ((base) + 0x00500)

#define EHCI_USBMODE_IDLE           0x00000000
#define EHCI_USBMODE_DEVICE         0x00000002
#define EHCI_USBMODE_HOST           0x00000003

#define EHCI_PORTSC_ULPI            0x80000000
#define EHCI_PORTSC_UTMI            0x00000000

#define EHCI_SNOOP_SIZE_4K          0x0000000B
#define EHCI_SNOOP_SIZE_8K          0x0000000C
#define EHCI_SNOOP_SIZE_16K         0x0000000D
#define EHCI_SNOOP_SIZE_32K         0x0000000E
#define EHCI_SNOOP_SIZE_64K         0x0000000F
#define EHCI_SNOOP_SIZE_128K        0x00000010
#define EHCI_SNOOP_SIZE_256K        0x00000011
#define EHCI_SNOOP_SIZE_512K        0x00000012
#define EHCI_SNOOP_SIZE_1M          0x00000013
#define EHCI_SNOOP_SIZE_2M          0x00000014
#define EHCI_SNOOP_SIZE_4M          0x00000015
#define EHCI_SNOOP_SIZE_8M          0x00000016
#define EHCI_SNOOP_SIZE_16M         0x00000017
#define EHCI_SNOOP_SIZE_32M         0x00000018
#define EHCI_SNOOP_SIZE_64M         0x00000019
#define EHCI_SNOOP_SIZE_128M        0x0000001A
#define EHCI_SNOOP_SIZE_256M        0x0000001B
#define EHCI_SNOOP_SIZE_512M        0x0000001C
#define EHCI_SNOOP_SIZE_1G          0x0000001D
#define EHCI_SNOOP_SIZE_2G          0x0000001E

#define EHCI_SNOOP_SIZE             EHCI_SNOOP_SIZE_2G

#define EHCI_CONTROL_PHY_UTMI_EN    0x00000200
#define EHCI_CONTROL_PHY_CLK_UTMI   0x00000000
#define EHCI_CONTROL_PHY_CLK_ULPI   0x00000400
#define EHCI_CONTROL_USB_EN         0x00000004
#define EHCI_RD_PREFETCH_VAL        0x00000001

/* PIC Base Address */

#define PIC_OFFSET                  0x40000
#define PCIBA                       (CCSBAR | PIC_OFFSET)

/* DMA registers base address and offsets */

#define DMA1_REGBASE                (CCSBAR + 0x21100)
#define DMA2_REGBASE                (CCSBAR + 0x21180)
#define DMA3_REGBASE                (CCSBAR + 0x21200)
#define DMA4_REGBASE                (CCSBAR + 0x21280)

#define DMA_CHAN_OFFSET             0x80
#define DMA_CHAN_NUM                4

/* Global Function Registers */

/* PORPLL used to detect clocking ratio for CCB/CPM for serial devices */
/* Plat Ratio not working on board need to test!!!!*/


#define M85XX_PORPLLSR(base)    (CAST(VUINT32 *)((base) + 0xE0000))

#define M85XX_PORPLLSR_E500_1_RATIO_MASK    0x3f000000
#define M85XX_PORPLLSR_E500_RATIO_MASK      0x003f0000
#define M85XX_PORPLLSR_DDR_RATIO_MASK       0x00003e00
#define M85XX_PORPLLSR_PLAT_RATIO_MASK      0x0000003e
#define M85XX_PORPLLSR_E500_RATIO(base)     ((*M85XX_PORPLLSR(base) & M85XX_PORPLLSR_E500_RATIO_MASK) >> 16)
#define M85XX_PORPLLSR_E500_1_RATIO(base)   ((*M85XX_PORPLLSR(base) & M85XX_PORPLLSR_E500_1_RATIO_MASK) >> 24)
#define M85XX_PORPLLSR_DDR_RATIO(base)      ((*M85XX_PORPLLSR(base) & M85XX_PORPLLSR_DDR_RATIO_MASK) >> 9)
#define M85XX_PORPLLSR_PLAT_RATIO(base)     ((*M85XX_PORPLLSR(base) & M85XX_PORPLLSR_PLAT_RATIO_MASK) >> 1)

#define M85XX_DDRDLLCR(base)            (CAST(VUINT32 *)((base) + 0xE0E10))
#define M85XX_LBCDLLSR(base)            (CAST(VUINT32 *)((base) + 0xE0E20))

#define M85XX_DEVDISR(base)             (CAST(VUINT32 *)((base) + 0xE0070))
#define M85XX_DEVDISR_PCIE1             0x20000000
#define M85XX_DEVDISR_LBC               0x08000000
#define M85XX_DEVDISR_PCIE2             0x04000000
#define M85XX_DEVDISR_PCIE3             0x02000000
#define M85XX_DEVDISR_SEC               0x01000000
#define M85XX_DEVDISR_PME               0x00800000
#define M85XX_DEVDISR_TLU1              0x00400000
#define M85XX_DEVDISR_TLU2              0x00200000
#define M85XX_DEVDISR_SRIO              0x00080000
#define M85XX_DEVDISR_D2                0x00020000
#define M85XX_DEVDISR_D1                0x00010000
#define M85XX_DEVDISR_TB0               0x00004000
#define M85XX_DEVDISR_E500_CORE0        0x00008000
#define M85XX_DEVDISR_E500_CORE1        0x00002000
#define M85XX_DEVDISR_TB1               0x00001000
#define M85XX_DEVDISR_DMA1              0x00000400
#define M85XX_DEVDISR_DMA2              0x00000200
#define M85XX_DEVDISR_TSEC1             0x00000080
#define M85XX_DEVDISR_TSEC2             0x00000040
#define M85XX_DEVDISR_TSEC3             0x00000020
#define M85XX_DEVDISR_TSEC4             0x00000010
#define M85XX_DEVDISR_FEC               0x00000008
#define M85XX_DEVDISR_I2C               0x00000004
#define M85XX_DEVDISR_DUART             0x00000002

#define M85XX_POWMGTCSR(base)           (CAST(VUINT32 *)((base) + 0xE0080))
#define M85XX_POWMGTCSR_CORE0_IRQ_MSK   0x80000000
#define M85XX_POWMGTCSR_CORE0_CI_MSK    0x40000000
#define M85XX_POWMGTCSR_CORE1_IRQ_MSK   0x20000000
#define M85XX_POWMGTCSR_CORE1_CI_MSK    0x10000000
#define M85XX_POWMGTCSR_CORE0_DOZ       0x00080000
#define M85XX_POWMGTCSR_CORE1_DOZ       0x00040000
#define M85XX_POWMGTCSR_SLP             0x00020000
#define M85XX_POWMGTCSR_CORE1_DOZING    0x00000020
#define M85XX_POWMGTCSR_CORE1_NAPPING   0x00000010
#define M85XX_POWMGTCSR_CORE0_DOZING    0x00000008
#define M85XX_POWMGTCSR_CORE0_NAPPING   0x00000004
#define M85XX_POWMGTCSR_SLPING          0x00000002

/* Processor initialization register */

#define M85XX_EPICPIR(base)             (CAST(VUINT32 *)((base) + 0x41090))

/* Global Utilities Block Register */

#define M85XX_AUTORSTSR(base)           (CAST(VUINT32 *)((base) + 0xe009c))
#define READY_P1                        (0x01 << 14)

#define M85XX_EPICPIR_HRST_CORE0        0x00000001
#define M85XX_EPICPIR_HRST_CORE1        0x00000002

#define M85XX_PVR(base)                 (CAST(VUINT32 *)((base) + 0xE00A0))
#define M85XX_SVR(base)                 (CAST(VUINT32 *)((base) + 0xE00A4))

#define _PPC_BUCSR_FI                   0x200   /* Invalidate branch cache */
#define _PPC_BUCSR_E                    0x1     /* Enable branch prediction */

/* EPIC defines */

#define EPIC_EX_IRQ_NUM                 12
#define EPIC_IN_IRQ_NUM                 64
#define EPIC_GT_IRQ_NUM                 4
#define EPIC_MSG_IRQ_NUM                8
#define EPIC_SMSG_IRQ_NUM               8
#define EPIC_IPI_IRQ_NUM                4
#define EPIC_EX_REG_BASE                0x50000
#define EPIC_IN_REG_BASE                0x50200
#define EPIC_GT_A_REG_BASE              0x41120
#define EPIC_GT_B_REG_BASE              0x42120
#define EPIC_MSG_REG_BASE               0x51600
#define EPIC_SMSG_REG_BASE              0x51c00
#define EPIC_IPI_REG_BASE               0x410a0
#define EPIC_EX_REG_INTERVAL            0x20
#define EPIC_IN_REG_INTERVAL            0x20
#define EPIC_GT_REG_INTERVAL            0x40
#define EPIC_MSG_REG_INTERVAL           0x20
#define EPIC_SMSG_REG_INTERVAL          0x20
#define EPIC_IPI_REG_INTERVAL           0x10

/* interrupt vectors */

#define EPIC_DMA1_CHAN0_INT_NUM         4
#define EPIC_DMA1_CHAN0_INT_VEC         (EPIC_DMA1_CHAN0_INT_NUM +  \
                                         EPIC_VEC_IN_IRQ0)
#define EPIC_DMA1_CHAN1_INT_NUM         5
#define EPIC_DMA1_CHAN1_INT_VEC         (EPIC_DMA1_CHAN1_INT_NUM +  \
                                         EPIC_VEC_IN_IRQ0)
#define EPIC_DMA1_CHAN2_INT_NUM         6
#define EPIC_DMA1_CHAN2_INT_VEC         (EPIC_DMA1_CHAN2_INT_NUM +  \
                                         EPIC_VEC_IN_IRQ0)
#define EPIC_DMA1_CHAN3_INT_NUM         7
#define EPIC_DMA1_CHAN3_INT_VEC         (EPIC_DMA1_CHAN3_INT_NUM +  \
                                         EPIC_VEC_IN_IRQ0)
#define EPIC_USB_INT_NUM                12
#define EPIC_USB_INT_VEC                (EPIC_USB_INT_NUM + \
                                        EPIC_VEC_IN_IRQ0)
#define EPIC_SATA2_INT_NUM              25
#define EPIC_SATA2_INT_VEC              (EPIC_SATA2_INT_NUM + \
                                        EPIC_VEC_IN_IRQ0)
#define EPIC_I2C_INT_NUM                27
#define EPIC_I2C_INT_VEC                (EPIC_I2C_INT_NUM + \
                                         EPIC_VEC_IN_IRQ0)
#define EPIC_SPI_INT_NUM                43
#define EPIC_SPI_INT_VEC                (EPIC_SPI_INT_NUM + \
                                         EPIC_VEC_IN_IRQ0)
#define EPIC_SDHC_INT_NUM               56
#define EPIC_SDHC_INT_VEC               (EPIC_SDHC_INT_NUM + \
                                         EPIC_VEC_IN_IRQ0)
#define EPIC_SATA1_INT_NUM              58
#define EPIC_SATA1_INT_VEC              (EPIC_SATA1_INT_NUM + \
                                        EPIC_VEC_IN_IRQ0)
#define EPIC_DMA2_CHAN0_INT_NUM         60
#define EPIC_DMA2_CHAN0_INT_VEC         (EPIC_DMA2_CHAN0_INT_NUM +  \
                                         EPIC_VEC_IN_IRQ0)
#define EPIC_DMA2_CHAN1_INT_NUM         61
#define EPIC_DMA2_CHAN1_INT_VEC         (EPIC_DMA2_CHAN1_INT_NUM +  \
                                         EPIC_VEC_IN_IRQ0)
#define EPIC_DMA2_CHAN2_INT_NUM         62
#define EPIC_DMA2_CHAN2_INT_VEC         (EPIC_DMA2_CHAN2_INT_NUM +  \
                                         EPIC_VEC_IN_IRQ0)
#define EPIC_DMA2_CHAN3_INT_NUM         63
#define EPIC_DMA2_CHAN3_INT_VEC         (EPIC_DMA2_CHAN3_INT_NUM +  \
                                         EPIC_VEC_IN_IRQ0)

/* ETSEC */

#define ETSEC0_GROUP0_BASE              (CCSBAR + 0xB0000)
#define ETSEC1_GROUP0_BASE              (CCSBAR + 0xB1000)
#define ETSEC2_GROUP0_BASE              (CCSBAR + 0xB2000)

#define ETSEC0_MDIO_BASE                (CCSBAR + 0x24000)
#define ETSEC1_MDIO_BASE                (CCSBAR + 0x25000)
#define ETSEC2_MDIO_BASE                (CCSBAR + 0x26000)

/* eSDHC */

#define SDHC_BASE                       (CCSBAR + 0x2E000)

#define SDHC_CLK                        0x00010000
#define SDHC_DATA                       0x00540000
#define SDHC_WP                         0x00004000
#define SDHC_CD                         0x00001000

/* GPIO Registers */

#define GPIO_BASE                       (CCSBAR + 0xF000)

#define GPDIR                           (GPIO_BASE + 0xC00)
#define GPODR                           (GPIO_BASE + 0xC04)
#define GPDAT                           (GPIO_BASE + 0xC08)
#define GPIER                           (GPIO_BASE + 0xC0C)
#define GPIMR                           (GPIO_BASE + 0xC10)
#define GPICR                           (GPIO_BASE + 0xC14)

#define USB_PORT_EN                     0x01000000

/* SPI defines */

#define SPI_REG_BASE                    (CCSBAR + 0x7000)

/* Alternate Function Signal Multiplex Control Register */

#define M85XX_PMUXCR                    *((VUINT32 *)(CCSBAR + 0xE0060))

#define HID0_EMCP                       (0x80000000)
#define HID0_ENMAS7                     (0x80)

#define CPLD_BASE_ADRS                  (0xFFB00000)
#define CPLD_SIZE                       (0x00100000)

#define USB_DATA                        0x00AAA000
#define USB_CLK                         0x00000200
#define USB_STP                         0x00000800
#define USB_NXT                         0x00000080

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif /* __INCp1010rdbh */