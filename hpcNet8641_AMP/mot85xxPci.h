/* mot85xxPci.h - Freescale hpcNet8641 PCI Bridge setup header file */

/* Copyright (c) 2005-2006 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,04jan07,dtr  File created.
*/

#ifndef _INCmot85xxPcih
#define _INCmot85xxPcih

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */


#define COMMAND_REGISTER_OFFSET         0x4
#define COMMAND_REGISTER_WIDTH          0x2        
#define BRIDGE_BAR0_OFFSET              0x10
#define BRIDGE_BAR0_WIDTH               0x4


#define PCIEX_REGBASE            (CCSBAR + 0x8000)
#define PCIEX2_REGBASE           (CCSBAR + 0x9000)
/* PCI 1 configuration space reg and int ack */


#define PCIEX_CFG_ADR_REG        (CCSBAR + 0x8000)    
#define PCIEX_CFG_DATA_REG       (CCSBAR + 0x8004)
#define PCIEX_INT_ACK            (CCSBAR + 0x8008)

/* PCI 2 configuration space reg and int ack */

#define PCIEX2_CFG_ADR_REG        (CCSBAR + 0x9000)    
#define PCIEX2_CFG_DATA_REG       (CCSBAR + 0x9004)
#define PCIEX2_INT_ACK            (CCSBAR + 0x9008)


/* PCI 1 Outbound translation registers */
#undef CVPUINT32
#define CVPUINT32(base,addr)  (CAST(VUINT32 *)((base) + (addr)))

/* PCI Express Outbound translation registers */

#define PCIEX_OUTBOUND_TRANS_ADRS_REG0(base)     CVPUINT32(base, 0x8c00)
#define PCIEX_OUTBOUND_TRANS_ADRS_REG1(base)     CVPUINT32(base, 0x8c20)
#define PCIEX_OUTBOUND_TRANS_ADRS_REG2(base)     CVPUINT32(base, 0x8c40)
#define PCIEX_OUTBOUND_TRANS_ADRS_REG3(base)     CVPUINT32(base, 0x8c60)
#define PCIEX_OUTBOUND_TRANS_ADRS_REG4(base)     CVPUINT32(base, 0x8c80)
#define PCIEX_OUTBOUND_TRANS_EXT_ADRS_REG0(base)     CVPUINT32(base, 0x8c04)
#define PCIEX_OUTBOUND_TRANS_EXT_ADRS_REG1(base)     CVPUINT32(base, 0x8c24)
#define PCIEX_OUTBOUND_TRANS_EXT_ADRS_REG2(base)     CVPUINT32(base, 0x8c44)
#define PCIEX_OUTBOUND_TRANS_EXT_ADRS_REG3(base)     CVPUINT32(base, 0x8c64)
#define PCIEX_OUTBOUND_TRANS_EXT_ADRS_REG4(base)     CVPUINT32(base, 0x8c84)
#define PCIEX_OUTBOUND_BASE_ADRS_REG0(base)     CVPUINT32(base, 0x8c08)
#define PCIEX_OUTBOUND_BASE_ADRS_REG1(base)     CVPUINT32(base, 0x8c28)
#define PCIEX_OUTBOUND_BASE_ADRS_REG2(base)     CVPUINT32(base, 0x8c48)
#define PCIEX_OUTBOUND_BASE_ADRS_REG3(base)     CVPUINT32(base, 0x8c68)
#define PCIEX_OUTBOUND_BASE_ADRS_REG4(base)     CVPUINT32(base, 0x8c88)

/* Outbound attributes register definitions */ 

#define PCIEX_OUTBOUND_ATTR_REG0(base)     CVPUINT32(base, 0x8c10)
#define PCIEX_OUTBOUND_ATTR_REG1(base)     CVPUINT32(base, 0x8c30)
#define PCIEX_OUTBOUND_ATTR_REG2(base)     CVPUINT32(base, 0x8c50)
#define PCIEX_OUTBOUND_ATTR_REG3(base)     CVPUINT32(base, 0x8c70)
#define PCIEX_OUTBOUND_ATTR_REG4(base)     CVPUINT32(base, 0x8c90)


/* PCI Express Outbound translation registers */

#define PCIEX2_OUTBOUND_TRANS_ADRS_REG0(base)     CVPUINT32(base, 0x9c00)
#define PCIEX2_OUTBOUND_TRANS_ADRS_REG1(base)     CVPUINT32(base, 0x9c20)
#define PCIEX2_OUTBOUND_TRANS_ADRS_REG2(base)     CVPUINT32(base, 0x9c40)
#define PCIEX2_OUTBOUND_TRANS_ADRS_REG3(base)     CVPUINT32(base, 0x9c60)
#define PCIEX2_OUTBOUND_TRANS_ADRS_REG4(base)     CVPUINT32(base, 0x9c80)
#define PCIEX2_OUTBOUND_TRANS_EXT_ADRS_REG0(base)     CVPUINT32(base, 0x9c04)
#define PCIEX2_OUTBOUND_TRANS_EXT_ADRS_REG1(base)     CVPUINT32(base, 0x9c24)
#define PCIEX2_OUTBOUND_TRANS_EXT_ADRS_REG2(base)     CVPUINT32(base, 0x9c44)
#define PCIEX2_OUTBOUND_TRANS_EXT_ADRS_REG3(base)     CVPUINT32(base, 0x9c64)
#define PCIEX2_OUTBOUND_TRANS_EXT_ADRS_REG4(base)     CVPUINT32(base, 0x9c84)
#define PCIEX2_OUTBOUND_BASE_ADRS_REG0(base)     CVPUINT32(base, 0x9c08)
#define PCIEX2_OUTBOUND_BASE_ADRS_REG1(base)     CVPUINT32(base, 0x9c28)
#define PCIEX2_OUTBOUND_BASE_ADRS_REG2(base)     CVPUINT32(base, 0x9c48)
#define PCIEX2_OUTBOUND_BASE_ADRS_REG3(base)     CVPUINT32(base, 0x9c68)
#define PCIEX2_OUTBOUND_BASE_ADRS_REG4(base)     CVPUINT32(base, 0x9c88)

/* Outbound attributes register definitions */ 

#define PCIEX2_OUTBOUND_ATTR_REG0(base)     CVPUINT32(base, 0x9c10)
#define PCIEX2_OUTBOUND_ATTR_REG1(base)     CVPUINT32(base, 0x9c30)
#define PCIEX2_OUTBOUND_ATTR_REG2(base)     CVPUINT32(base, 0x9c50)
#define PCIEX2_OUTBOUND_ATTR_REG3(base)     CVPUINT32(base, 0x9c70)
#define PCIEX2_OUTBOUND_ATTR_REG4(base)     CVPUINT32(base, 0x9c90)

/* Outbound/Inbound Comparison mask register defines */

#define PCI_WINDOW_ENABLE_BIT 0x80000000
#define PCI_ATTR_BS_BIT       0x40000000
#define PCI_OUT_ATTR_RTT_MEM      0x00040000
#define PCI_OUT_ATTR_RTT_IO       0x00080000
#define PCI_OUT_ATTR_WTT_MEM      0x00004000
#define PCI_OUT_ATTR_WTT_IO       0x00008000 
#define PCI_ATTR_WS_4K       0x0000000B
#define PCI_ATTR_WS_8K       0x0000000c
#define PCI_ATTR_WS_16K      0x0000000D
#define PCI_ATTR_WS_32K      0x0000000E
#define PCI_ATTR_WS_64K      0x0000000F
#define PCI_ATTR_WS_128K     0x00000010
#define PCI_ATTR_WS_256K     0x00000011
#define PCI_ATTR_WS_512K     0x00000012
#define PCI_ATTR_WS_1M       0x00000013
#define PCI_ATTR_WS_2M       0x00000014
#define PCI_ATTR_WS_4M       0x00000015
#define PCI_ATTR_WS_8M       0x00000016
#define PCI_ATTR_WS_16M      0x00000017
#define PCI_ATTR_WS_32M      0x00000018
#define PCI_ATTR_WS_64M      0x00000019
#define PCI_ATTR_WS_128M     0x0000001a
#define PCI_ATTR_WS_256M     0x0000001b
#define PCI_ATTR_WS_512M     0x0000001c
#define PCI_ATTR_WS_1G       0x0000001d
#define PCI_ATTR_WS_2G       0x0000001e
#define PCI_ATTR_WS_4G       0x0000001f
#define PCI_IN_ATTR_TGI_LM   0x00f00000
#define PCI_IN_ATTR_TGI_RIO  0x00c00000
#define PCI_IN_ATTR_RTT_RIO_READ 0x00040000
#define PCI_IN_ATTR_RTT_LM_READ_NO_SNOOP 0x00040000
#define PCI_IN_ATTR_RTT_LM_READ_SNOOP 0x00050000
#define PCI_IN_ATTR_RTT_LM_READ_UNLOCK_L2_CACHE_LINE 0x00070000
#define PCI_IN_ATTR_RTT_LM_WRITE_NO_SNOOP 0x00004000
#define PCI_IN_ATTR_RTT_LM_WRITE_SNOOP 0x00005000
#define PCI_IN_ATTR_RTT_LM_WRITE_ALLOC_L2_CACHE_LINE 0x00006000
#define PCI_IN_ATTR_RTT_LM_WRITE_ALLOC_LOCK_L2_CACHE_LINE 0x00007000

#define PCI_SNOOP_ENABLE        0x40000000
#define PCI_PREFETCHABLE        0x20000000


/* PCI Express Inbound translation registers */

#define PCIEX_INBOUND_TRANS_ADRS_REG3(base)     CVPUINT32(base, 0x8DA0)
#define PCIEX_INBOUND_TRANS_EXT_ADRS_REG3(base) CVPUINT32(base, 0x8DA4)
#define PCIEX_INBOUND_BASE_ADRS_REG3(base)      CVPUINT32(base, 0x8DA8)
#define PCIEX_INBOUND_ATTR_REG3(base)           CVPUINT32(base, 0x8DB0)
#define PCIEX_INBOUND_TRANS_ADRS_REG2(base)     CVPUINT32(base, 0x8DC0)
#define PCIEX_INBOUND_BASE_ADRS_REG2(base)      CVPUINT32(base, 0x8DC8)
#define PCIEX_INBOUND_ATTR_REG2(base)           CVPUINT32(base, 0x8DD0)
#define PCIEX_INBOUND_TRANS_ADRS_REG1(base)     CVPUINT32(base, 0x8DE0)
#define PCIEX_INBOUND_BASE_ADRS_REG1(base)      CVPUINT32(base, 0x8DE8)
#define PCIEX_INBOUND_ATTR_REG1(base)           CVPUINT32(base, 0x8DF0)

/* PCI Express Inbound translation registers */

#define PCIEX2_INBOUND_TRANS_ADRS_REG3(base)     CVPUINT32(base, 0x9DA0)
#define PCIEX2_INBOUND_TRANS_EXT_ADRS_REG3(base) CVPUINT32(base, 0x9DA4)
#define PCIEX2_INBOUND_BASE_ADRS_REG3(base)      CVPUINT32(base, 0x9DA8)
#define PCIEX2_INBOUND_ATTR_REG3(base)           CVPUINT32(base, 0x9DB0)
#define PCIEX2_INBOUND_TRANS_ADRS_REG2(base)     CVPUINT32(base, 0x9DC0)
#define PCIEX2_INBOUND_BASE_ADRS_REG2(base)      CVPUINT32(base, 0x9DC8)
#define PCIEX2_INBOUND_ATTR_REG2(base)           CVPUINT32(base, 0x9DD0)
#define PCIEX2_INBOUND_TRANS_ADRS_REG1(base)     CVPUINT32(base, 0x9DE0)
#define PCIEX2_INBOUND_BASE_ADRS_REG1(base)      CVPUINT32(base, 0x9DE8)
#define PCIEX2_INBOUND_ATTR_REG1(base)           CVPUINT32(base, 0x9DF0)


#define PCI_ERROR_DETECT_REG             0x8e00
#define PCI_ERROR_CAPTURE_DISABLE_REG    0x8e04
#define PCI_ERROR_ENABLE_REG             0x8e08
#define PCI_ERROR_ATTR_CAPTURE_REG       0x8e0c
#define PCI_ERROR_ADRS_CAPTURE_REG       0x8e10
#define PCI_ERROR_EXT_ADRS_CAPTURE_REG   0x8e14
#define PCI_ERROR_DATA_LOW_CAPTURE_REG   0x8e18
#define PCI_ERROR_DATA_HIGH_CAPTURE_REG  0x8e1c
#define PCI_ERROR_GASKET_TIMER_REG       0x8e20

/* Command status register defines */
#define BUS_MASTER_ENABLE_BIT   0x4
#define MEMORY_SPACE_ACCESS_ENABLE_BIT 0x2

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif /* _INCmot85xxPcih */

