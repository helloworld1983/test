/* config.h - Freescale P2020 BSP configuration file */

/*
 * Copyright (c) 2009-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,19jul12,clx  Update BSP_REV
01f,02feb12,x_s  Remove the component INCLUDE_AIM_MMU_SHOW. (WIND00334904)
01e,19dec11,agf  Moved L1 parity handling to arch lib. (WIND00309426)
                 Update BSP_REV for vxWorks 6.9.2.1
01d,15apr10,clx  Update BSP version for vxWorks 6.9
01c,15sep09,l_z  Remove unused INCLUDE_PPC_FPU. (WIND00153695)
01b,19aug09,syt  BSP_REV bump up.
01a,17apr09,syt  derived from version 01q of ads8572/config.h
*/

#ifndef __INCconfigh
#define __INCconfigh

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

#define BSP_VERSION        "6.9"       /* vxWorks 6.9 */
#define BSP_REV            "/2"        /* 0 for first revision */

#include <vsbConfig.h>
#include <configAll.h>

#ifndef _ASMLANGUAGE
#   include <hwif/intCtlr/vxbEpicIntCtlr.h>
#endif  /* _ASMLANGUAGE */

#include "p2020.h"

/*
 * Must be the same as RAM_LOW_ADRS for core0
 * This used for reboot on core1
 */

#define RAM_LOW_ADRS_CPU0       0x00100000

/*
 * Here we need a region of memory that is safe to use
 * We assume that 0x10000 is enough space for intial vxworks stack
 * before is runns the first task.F
 * Assumes also that RAM_LOW_ADRS is at least 0x20000.
 */

#define CPU1_FUNC_START_ADR     (RAM_LOW_ADRS_CPU0 - 0x10000)
#define CPU1_STACK_START_ADR    (CPU1_FUNC_START_ADR + 4)
#define CPU1_INIT_START_ADR     (CPU1_STACK_START_ADR + 4)

#ifdef _WRS_CONFIG_SMP

/* # of CPUs configured to vxWorks SMP systems */

#   undef  VX_SMP_NUM_CPUS
#   define VX_SMP_NUM_CPUS      2
#   define INCLUDE_SMP_DEMO
#endif /* _WRS_CONFIG_SMP */

/* Common Includes for VXBUS PCI and ETSEC */

#define INCLUDE_VXBUS
#define INCLUDE_VXB_CMDLINE
#define INCLUDE_HWMEM_ALLOC
#define INCLUDE_PARAM_SYS
#define INCLUDE_PLB_BUS

#define HWMEM_POOL_SIZE         100000

#define INCLUDE_INTCTLR_LIB
#define DRV_INTCTLR_PPC
#define DRV_INTCTLR_EPIC

#undef  DRV_TIMER_OPENPIC
#undef  INCLUDE_INTCTLR_DYNAMIC_LIB

#define DRV_TIMER_M85XX
#define INCLUDE_TIMER_SYS

#define DRV_SIO_NS16550
#define INCLUDE_SIO_UTILS

#ifdef INCLUDE_PCI_BUS
#   define INCLUDE_PCI_BUS_AUTOCONF
#   define DRV_PCIBUS_M85XX
#   define DRV_RESOURCE_M85XXCCSR
#   define INCLUDE_GEI825XX_VXB_END
#endif  /* INCLUDE_PCI_BUS */

#define INCLUDE_END
#define INCLUDE_ETSEC_VXB_END
#define INCLUDE_DMA_SYS
#define INCLUDE_MII_BUS
#define INCLUDE_GENERICPHY

#define MAX_MAC_DEVS            3

/* default mac address */

#define ENET_DEFAULT0           WR_ENET0
#define ENET_DEFAULT1           WR_ENET1
#define ENET_DEFAULT2           WR_ENET2

#undef  DRV_DMA_FSL
#undef  INCLUDE_FSL_SPI

#undef  CONSOLE_BAUD_RATE
#define CONSOLE_BAUD_RATE       115200

#define WDT_RATE_MIN            (sysTimerClkFreq / (1 << 29))
#define WDT_RATE_MAX            (sysTimerClkFreq / (1 << 21))

#define DEFAULT_BOOT_LINE \
    "motetsec(0,0)host:vxWorks h=192.168.0.1 e=192.168.0.3 u=vxworks pw=vxworks f=0x0"

/* MMU and CACHE */

#define INCLUDE_MMU_BASIC
#define USER_I_MMU_ENABLE
#define USER_D_MMU_ENABLE

#define CACHE_LIBRARY_MODE     (CACHE_COPYBACK | CACHE_SNOOP_ENABLE)
#define CAM_DRAM_CACHE_MODE    _MMU_TLB_ATTR_M
#define TLB_CACHE_MODE         VM_STATE_CACHEABLE | VM_STATE_MEM_COHERENCY

#define INCLUDE_CACHE_SUPPORT

#define USER_D_CACHE_ENABLE
#undef  USER_D_CACHE_MODE
#define USER_D_CACHE_MODE       (CACHE_LIBRARY_MODE)
#define USER_I_CACHE_ENABLE
#undef  USER_I_CACHE_MODE
#define USER_I_CACHE_MODE       (CACHE_LIBRARY_MODE)

#define INCLUDE_L2_CACHE
#undef  INCLUDE_L2_SRAM

#define INCLUDE_BRANCH_PREDICTION

/* L2 SRAM Mode */

#define L2SRAM_ADDR             0xEFF80000
#define L2SRAM_WINDOW_SIZE      0x80000

#if defined(INCLUDE_L2_CACHE) && defined(INCLUDE_L2_SRAM)
#   define L2_CACHE_SIZE        L2SIZ_256KB
#   define L2_SRAM_SIZE         L2SIZ_256KB
#elif defined(INCLUDE_L2_CACHE) && !defined(INCLUDE_L2_SRAM)
#   define L2_CACHE_SIZE        L2SIZ_512KB
#   define L2_SRAM_SIZE         0
#else
#   define L2_CACHE_SIZE        0
#   define L2_SRAM_SIZE         L2SIZ_512KB
#endif  /* INCLUDE_L2_CACHE && INCLUDE_L2_SRAM */

/* Disable Support for SPE 64bit registers */

#define INCLUDE_SPE

/* add on-chip drivers */

#undef  INCLUDE_SECURITY_ENGINE     /* only supported if chip has E ie p2020E */

/* Use openPicTimer as the auxClk */

#ifdef INCLUDE_AUX_CLK
#   define DRV_TIMER_OPENPIC
#endif /* INCLUDE_AUX_CLK */

/* I2C support */

#undef  INCLUDE_I2C

/* LBC CS0 - flash 0 - default for bootrom */

#define FLASH_BASE_ADRS         0xf8000000
#define FLASH_SIZE              0x08000000
#define FLASH_WINDOW_SIZE       0x00800000

#define INCLUDE_FLASH

#ifdef INCLUDE_FLASH

/* NVRam */

#   define FLASH_ADRS           FLASH_BASE_ADRS
#   define FLASH_WIDTH          2
#   define FLASH_CHIP_WIDTH     2
#   define FLASH_SECTOR_SIZE    0x00020000
#   define FLASH_SECTOR_MASK    0xfffe0000
#   define NV_RAM_ADRS          (ROM_BASE_ADRS - FLASH_SECTOR_SIZE)
#   define NV_RAM_SIZE          FLASH_SECTOR_SIZE
#   define NV_MAC_ADRS_OFFSET   0x200

/* board specific flash configuration needed by MTD driver */

#   define S29GL_FLASH_BIT      1           /* 16-bit */
#   define S29GL_FLASH_NUM      1           /* only one chip */
#   define S29GL_FLASH_WIDTH    2           /* 16-bit */
#   define S29GL_SECTOR_SIZE    0x00020000  /* 128K per sector */
#   define S29GL_FLASH_SIZE     0x04000000  /* only 64MB used for TureFFS */
#   define S29GL_FLASH_OP_DELAY

#else  /* INCLUDE_FLASH */

#   define NV_RAM_SIZE          0

#endif  /* INCLUDE_FLASH */

/* TrueFFS flash support */

#undef INCLUDE_TFFS

#ifdef INCLUDE_TFFS
#   define INCLUDE_DOSFS
#   define INCLUDE_TL_FTL
#   define INCLUDE_TFFS_MOUNT
#endif  /* INCLUDE_TFFS */

/* USB EHCI */

#undef INCLUDE_USB

#ifdef INCLUDE_USB
#   define INCLUDE_USB_INIT
#   define INCLUDE_EHCI
#   define INCLUDE_EHCI_INIT
#   define INCLUDE_USB_MS_BULKONLY
#   define INCLUDE_USB_MS_BULKONLY_INIT
#   define INCLUDE_USB_MS_CBI
#   define INCLUDE_USB_MS_CBI_INIT
#   define INCLUDE_DOSFS
#endif  /* INCLUDE_USB */

/*  Define for FS */

#ifdef INCLUDE_DOSFS

#   define INCLUDE_ERF
#   define INCLUDE_DEVICE_MANAGER
#   define INCLUDE_FS_EVENT_UTIL
#   define INCLUDE_FS_MONITOR
#   define INCLUDE_XBD
#   define INCLUDE_XBD_BLK_DEV
#   define INCLUDE_XBD_TRANS
#   define INCLUDE_DOSFS_DIR_FIXED
#   define INCLUDE_DOSFS_DIR_VFAT
#   define INCLUDE_DOSFS_FAT
#   define INCLUDE_DOSFS_FMT
#   define INCLUDE_DOSFS_CHKDSK
#   define INCLUDE_DOSFS_MAIN

#endif  /* INCLUDE_DOSFS */

#ifdef INCLUDE_MMU_BASIC

#   define INCLUDE_AIM_MMU_CONFIG
#   define INCLUDE_AIM_MMU_MEM_POOL_CONFIG

/*
 * The following parameters are to configure initial memory usage for
 * page table and region tables and in event of running out the increment
 * of memory allocation and is specified as a number of MMU pages (4KByte
 * blocks).
 */

#   define AIM_MMU_INIT_PT_NUM  0x40
#   define AIM_MMU_INIT_PT_INCR 0x20
#   define AIM_MMU_INIT_RT_NUM  0x10
#   define AIM_MMU_INIT_RT_INCR 0x10

/* This write protects the page tables */

#   define INCLUDE_AIM_MMU_PT_PROTECTION

/*
 * INCLUDE_LOCK_TEXT_SECTION Requires use of CAM entries which can
 * possibly be already used in sysStaticTlbDesc. Also the larger the
 * page size that can be used the less CAM entries required so aligning
 * RAM_LOW_ADRS on a large page size boundary is usually necessary.
 * Locking the text section should increase performance because no
 * Instruction TLB misses are taken within the text section.
 */

#   define INCLUDE_LOCK_TEXT_SECTION
#   undef INCLUDE_PAGE_SIZE_OPTIMIZATION /* Not available for 85XX */

#endif /* INCLUDE_MMU_BASIC */

#define INCLUDE_CTORS_DTORS

#if ((TOOL==e500v2diab) || (TOOL==e500v2gnu))

/* These are 60X specific for now */

#   undef INCLUDE_HW_FP

/* ev2diab is hard float so undefine soft float */

#   undef INCLUDE_SW_FP

#else  /* (TOOL==e500v2diab) || (TOOL==e500v2gnu) */

/*
 * Using software FP support. Athough task based 32 bit HW_FP is allowed
 * no optimised libraries are available. The kernel doesn't execute any hw
 * fp instructions
 */

#   undef  INCLUDE_HW_FP
#   define INCLUDE_SW_FP

#endif  /* (TOOL==e500v2diab) || (TOOL==e500v2gnu) */

#define ROM_TEXT_ADRS           0xFFF00100
#define ROM_BASE_ADRS           0xFFF00000
#define ROM_SIZE                0x00100000

#define INCLUDE_DDR_SDRAM
#define LOCAL_MEM_LOCAL_ADRS    0x00000000
#define LOCAL_MEM_SIZE          PHY_MEM_SIZE
#define USER_RESERVED_MEM       0x00000000

#undef  VEC_BASE_ADRS
#define VEC_BASE_ADRS           LOCAL_MEM_LOCAL_ADRS

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif  /* __INCconfigh */

#if defined(PRJ_BUILD)
    #include "prjParams.h"
#endif /* PRJ_BUILD */

