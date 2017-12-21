/* mv64360DumpRegs.c - MV64360 Register Dumping Utility */

/*
modification history
--------------------
01b,12apr05,rab  Fix compiler warnings.
01a,17dec03,cak  Ported from ver 01a, rtss source base.
*/

/*
DESCRIPTION

The purpose of this utility is to display all of the internal
registers - including those in PCI configuration space - of the
Discovery II (MV64360).
*/

/* includes */

#include "mv64360.h"
#include "vxWorks.h"
#include "config.h"
#include "mv6100A.h"

/* defines */

#define pReg(r) \
    { \
    printf("%-42s @",#r);\
    printf(" 0x%08x = 0x%08x\n\r",\
    r+MV64360_REG_BASE,(UINT32)MV64360_READ32(MV64360_REG_BASE,r));\
    }

#define pciRead(r,f) \
    { \
    UINT32 temp1; \
    UINT32 temp2; \
    printf("%-42s @",#r);\
    sysPciRead(0,0,f,r,&temp1);\
    sysPciRead(1,0,f,r,&temp2);\
    printf(" 0x%02x = 0x%08x  0x%08x\n\r",r,temp1,temp2);\
    }

/* typedefs */

/* globals */

/* locals */

/* forward declarations */

void sysPciRead (int, int, int, int, UINT32 *);
void mv64360DumpRegs (void);

/*******************************************************************************
*
* sysPciRead - read a register from the MV64360's PCI configuration space
*
* RETURNS: register value that is read
*/
    
void sysPciRead
    (
    int bus,
    int device,
    int func,
    int reg,
    UINT32 * pResult
    )
    {
    int configAddrReg = 0;
    int configDataReg = 0;
    int temp;

    if (bus == 0)
	{
	configAddrReg = (int) (MV64360_REG_BASE + PCIIF_CFG_ADDR_PCI0);
	configDataReg = (int) (MV64360_REG_BASE + PCIIF_CFG_DATA_PCI0);
	}
    else  /* bus == 1 */
	{
	configAddrReg = (int) (MV64360_REG_BASE + PCIIF_CFG_ADDR_PCI1);
	configDataReg = (int) (MV64360_REG_BASE + PCIIF_CFG_DATA_PCI1);
	}

    temp = (((0 << 16) & 0x00ff0000) |
           ((device << 11) & 0x0000f800) |
           ((func << 8)  & 0x00000700));

    sysOutLong(configAddrReg, temp | (reg & 0xFC) | 0x80000000);

    *pResult = sysInLong(configDataReg);
    }
 
/*******************************************************************************
*
* mv64360DumpRegs - dump registers in the MV64360
*
* RETURNS: N/A
*/

void mv64360DumpRegs ()
    {

    printf("CPU Interface Registers:\n\r");
    pReg(CPUIF_CS0_BASE_ADDR);
    pReg(CPUIF_CS0_SIZE);
    pReg(CPUIF_CS1_BASE_ADDR);
    pReg(CPUIF_CS1_SIZE);
    pReg(CPUIF_CS2_BASE_ADDR);
    pReg(CPUIF_CS2_SIZE);
    pReg(CPUIF_CS3_BASE_ADDR);
    pReg(CPUIF_CS3_SIZE);
    pReg(CPUIF_DEVCS0_BASE_ADDR);
    pReg(CPUIF_DEVCS0_SIZE);
    pReg(CPUIF_DEVCS1_BASE_ADDR);
    pReg(CPUIF_DEVCS1_SIZE);
    pReg(CPUIF_DEVCS2_BASE_ADDR);
    pReg(CPUIF_DEVCS2_SIZE);
    pReg(CPUIF_DEVCS3_BASE_ADDR);
    pReg(CPUIF_DEVCS3_SIZE);
    pReg(CPUIF_BOOTCS_BASE_ADDR);
    pReg(CPUIF_BOOTCS_SIZE);
    pReg(CPUIF_PCI0_IO_BASE_ADDR);
    pReg(CPUIF_PCI0_IO_SIZE);
    pReg(CPUIF_PCI0_MEM0_BASE_ADDR);
    pReg(CPUIF_PCI0_MEM0_SIZE);
    pReg(CPUIF_PCI0_MEM1_BASE_ADDR);
    pReg(CPUIF_PCI0_MEM1_SIZE);
    pReg(CPUIF_PCI0_MEM2_BASE_ADDR);
    pReg(CPUIF_PCI0_MEM2_SIZE);
    pReg(CPUIF_PCI0_MEM3_BASE_ADDR);
    pReg(CPUIF_PCI0_MEM3_SIZE);
    pReg(CPUIF_PCI1_IO_BASE_ADDR);
    pReg(CPUIF_PCI1_IO_SIZE);
    pReg(CPUIF_PCI1_MEM0_BASE_ADDR);
    pReg(CPUIF_PCI1_MEM0_SIZE);
    pReg(CPUIF_PCI1_MEM1_BASE_ADDR);
    pReg(CPUIF_PCI1_MEM1_SIZE);
    pReg(CPUIF_PCI1_MEM2_BASE_ADDR);
    pReg(CPUIF_PCI1_MEM2_SIZE);
    pReg(CPUIF_PCI1_MEM3_BASE_ADDR);
    pReg(CPUIF_PCI1_MEM3_SIZE);
    pReg(CPUIF_INTEGRATED_SRAM_BASE_ADDR);
    pReg(CPUIF_INTERNAL_SPACE_BASE_ADDR);
    pReg(CPUIF_BASE_ADDR_ENABLE);
    pReg(CPUIF_PCI0_IO_ADDR_REMAP);
    pReg(CPUIF_PCI0_MEM0_ADDR_REMAP_LOW);
    pReg(CPUIF_PCI0_MEM0_ADDR_REMAP_HI);
    pReg(CPUIF_PCI0_MEM1_ADDR_REMAP_LOW);
    pReg(CPUIF_PCI0_MEM1_ADDR_REMAP_HI);
    pReg(CPUIF_PCI0_MEM2_ADDR_REMAP_LOW);
    pReg(CPUIF_PCI0_MEM2_ADDR_REMAP_HI);
    pReg(CPUIF_PCI0_MEM3_ADDR_REMAP_LOW);
    pReg(CPUIF_PCI0_MEM3_ADDR_REMAP_HI);
    pReg(CPUIF_PCI1_IO_ADDR_REMAP);
    pReg(CPUIF_PCI1_MEM0_ADDR_REMAP_LOW);
    pReg(CPUIF_PCI1_MEM0_ADDR_REMAP_HI);
    pReg(CPUIF_PCI1_MEM1_ADDR_REMAP_LOW);
    pReg(CPUIF_PCI1_MEM1_ADDR_REMAP_HI);
    pReg(CPUIF_PCI1_MEM2_ADDR_REMAP_LOW);
    pReg(CPUIF_PCI1_MEM2_ADDR_REMAP_HI);
    pReg(CPUIF_PCI1_MEM3_ADDR_REMAP_LOW);
    pReg(CPUIF_PCI1_MEM3_ADDR_REMAP_HI);
    pReg(CPUIF_PCI0_HDRS_RETARG_CTRL);
    pReg(CPUIF_PCI0_HDRS_RETARG_BASE);
    pReg(CPUIF_PCI1_HDRS_RETARG_CTRL);
    pReg(CPUIF_PCI1_HDRS_RETARG_BASE);
    pReg(CPUIF_CPU_CFG);
    pReg(CPUIF_CPU_GE_HDRS_RETARG_CTRL);
    pReg(CPUIF_CPU_GE_HDRS_RETARG_BASE);
    pReg(CPUIF_CPU_IDMA_HDRS_RETARG_CTRL);
    pReg(CPUIF_CPU_IDMA_HDRS_RETARG_BASE);
    pReg(CPUIF_CPU_MODE);
    pReg(CPUIF_CPU_PADS_CALIBRATION);
    pReg(CPUIF_RST_SAMPLE_LO);
    pReg(CPUIF_RST_SAMPLE_HI);
    pReg(CPUIF_CPU_MSTR_CTRL);
    pReg(CPUIF_CPU_INTERFACE_CROSSBAR_CTRL_LOW);
    pReg(CPUIF_CPU_INTERFACE_CROSSBAR_CTRL_HI);
    pReg(CPUIF_WHO_AM_I);
    pReg(CPUIF_CPU0_DOORBELL);
    pReg(CPUIF_CPU0_DOORBELL_CLEAR);
    pReg(CPUIF_CPU_INTERFACE_CROSSBAR_TIME_OUT);
    pReg(CPUIF_CPU1_DOORBELL);
    pReg(CPUIF_CPU1_DOORBELL_CLEAR);
    pReg(CPUIF_CPU0_DOORBELL_MASK);
    pReg(CPUIF_CPU1_DOORBELL_MASK);
    pReg(CPUIF_SEMAPHORE0);
    pReg(CPUIF_SEMAPHORE1);
    pReg(CPUIF_SEMAPHOER2);
    pReg(CPUIF_SEMAPHORE3);
    pReg(CPUIF_SEMAPHORE4);
    pReg(CPUIF_CPU0_SYNC_BARRIER_TRIGGER);
    pReg(CPUIF_CPU0_SYNC_BARRIER_VIRTUAL);
    pReg(CPUIF_SEMAPHORE5);
    pReg(CPUIF_SEMAPHORE6);
    pReg(CPUIF_SEMAPHORE7);
    pReg(CPUIF_CPU_PROTECT_WINDOW0_BASE_ADDR);
    pReg(CPUIF_CPU_PROTECT_WINDOW0_SIZE);
    pReg(CPUIF_CPU1_SYNC_BARRIER_TRIGGER);
    pReg(CPUIF_CPU1_SYNC_BARRIER_VIRTUAL);
    pReg(CPUIF_CPU_PROTECT_WINDOW1_BASE_ADDR);
    pReg(CPUIF_CPU_PROTECT_WINDOW1_SIZE);
    pReg(CPUIF_CPU_PROTECT_WINDOW2_BASE_ADDR);
    pReg(CPUIF_CPU_PROTECT_WINDOW2_SIZE);
    pReg(CPUIF_CPU_PROTECT_WINDOW3_BASE_ADDR);
    pReg(CPUIF_CPU_PROTECT_WINDOW3_SIZE);
    pReg(CPUIF_CPU_ERR_ADDR_LOW);
    pReg(CPUIF_CPU_ERR_ADDR_HI);
    pReg(CPUIF_CPU_ERR_DATA_LOW);
    pReg(CPUIF_CPU_ERR_DATA_HI);
    pReg(CPUIF_CPU_ERR_PARITY);
    pReg(CPUIF_CPU_ERR_CAUSE);
    pReg(CPUIF_CPU0_ERR_MASK);
    printf("\n\r");

    printf("SRAM Registers:\n\r");
    pReg(ITG_SRAM_CFG);
    pReg(ITG_SRAM_ERR_CAUSE);
    pReg(ITG_SRAM_TEST_MODE);
    pReg(ITG_SRAM_ERR_ADDR);
    pReg(ITG_SRAM_ERR_ADDR_HI);
    pReg(ITG_SRAM_ERR_DATA_LOW);
    pReg(ITG_SRAM_ERR_DATA_HI);
    pReg(ITG_SRAM_ERR_PARITY);
    printf("\n\r");

    printf("DDR SDRAM Registers:\n\r");
    pReg(DDR_SDRAM_CFG);
    pReg(DDR_DUNIT_CTRL_LO);
    pReg(DDR_DUNIT_CTRL_HI);
    pReg(DDR_SDRAM_TMNG_LO);
    pReg(DDR_SDRAM_TMNG_HI);
    pReg(DDR_SDRAM_ADDR_CTRL);
    pReg(DDR_SDRAM_OPEN_PAGES_CTRL);
    pReg(DDR_SDRAM_OPER);
    pReg(DDR_SDRAM_MODE);
    pReg(DDR_SDRAM_EXT_DRAM_MODE);
    pReg(DDR_SDRAM_IF_XBAR_CTRL_LO);
    pReg(DDR_SDRAM_IF_XBAR_CTRL_HI);
    pReg(DDR_SDRAM_IF_XBAR_TMOUT);
    pReg(DDR_SDRAM_ADDR_CTRL_PAD_CALIB);
    pReg(DDR_SDRAM_DATA_PAD_CALIB);
    pReg(DDR_SDRAM_ERR_ADDR);
    pReg(DDR_SDRAM_ERR_DATA_LO);
    pReg(DDR_SDRAM_ERR_DATA_HI);
    pReg(DDR_SDRAM_RCVD_ECC);
    pReg(DDR_SDRAM_CALC_ECC);
    pReg(DDR_SDRAM_ECC_CTRL);
    pReg(DDR_SDRAM_ECC_CNTR);
    pReg(DDR_DFCDL_CFG0);
    pReg(DDR_DFCDL_CFG1);
    pReg(DDR_SRAM_ADDR);
    pReg(DDR_SRAM_DATA0);
    pReg(DDR_DFCDL_PROBE);
    printf("\n\r");

    printf("Device Controller Registers:\n\r");
    pReg(DVCTL_DEVICE_BANK0_PARAMS);
    pReg(DVCTL_DEVICE_BANK1_PARAMS);
    pReg(DVCTL_DEVICE_BANK2_PARAMS);
    pReg(DVCTL_DEVICE_BANK3_PARAMS);
    pReg(DVCTL_DEVICE_BOOT_BANK_PARAMS);
    pReg(DVCTL_DEVICE_INTERFACE_CTRL);
    pReg(DVCTL_DEVICE_INTERFACE_CROSSBAR_CTRL_LOW);
    pReg(DVCTL_DEVICE_INTERFACE_CROSSBAR_CTRL_HI);
    pReg(DVCTL_DEVICE_INTERFACE_CROSSBAR_TIMEOUT);
    pReg(DVCTL_DEVICE_INTERRUPT_CAUSE);
    pReg(DVCTL_DEVICE_INTERRUPT_MASK);
    pReg(DVCTL_DEVICE_ERR_ADDR);
    pReg(DVCTL_DEVICE_ERR_DATA);
    pReg(DVCTL_DEVICE_ERR_PARITY);
    printf("\n\r");

    printf("PCI Registers:\n\r");
    pReg(PCIIF_CS0_BAR_SIZE_PCI0);
    pReg(PCIIF_CS0_BAR_SIZE_PCI1);
    pReg(PCIIF_CS1_BAR_SIZE_PCI0);
    pReg(PCIIF_CS1_BAR_SIZE_PCI1);
    pReg(PCIIF_CS2_BAR_SIZE_PCI0);
    pReg(PCIIF_CS2_BAR_SIZE_PCI1);
    pReg(PCIIF_CS3_BAR_SIZE_PCI0);
    pReg(PCIIF_CS3_BAR_SIZE_PCI1);
    pReg(PCIIF_DEVCS0_BAR_SIZE_PCI0);
    pReg(PCIIF_DEVCS0_BAR_SIZE_PCI1);
    pReg(PCIIF_DEVCS1_BAR_SIZE_PCI0);
    pReg(PCIIF_DEVCS1_BAR_SIZE_PCI1);
    pReg(PCIIF_DEVCS2_BAR_SIZE_PCI0);
    pReg(PCIIF_DEVCS2_BAR_SIZE_PCI1);
    pReg(PCIIF_DEVCS3_BAR_SIZE_PCI0);
    pReg(PCIIF_DEVCS3_BAR_SIZE_PCI1);
    pReg(PCIIF_BOOTCS_BAR_SIZE_PCI0);
    pReg(PCIIF_BOOTCS_BAR_SIZE_PCI1);
    pReg(PCIIF_P2P_MEM0_BAR_SIZE_PCI0);
    pReg(PCIIF_P2P_MEM0_BAR_SIZE_PCI1);
    pReg(PCIIF_P2P_MEM1_BAR_SIZE_PCI0);
    pReg(PCIIF_P2P_MEM1_BAR_SIZE_PCI1);
    pReg(PCIIF_P2P_IO_BAR_SIZE_PCI0);
    pReg(PCIIF_P2P_IO_BAR_SIZE_PCI1);
    pReg(PCIIF_CPU_BAR_SIZE_PCI0);
    pReg(PCIIF_CPU_BAR_SIZE_PCI1);
    pReg(PCIIF_INTEGRATED_SRAM_BAR_SIZE_PCI0);
    pReg(PCIIF_INTEGRATED_SRAM_BAR_SIZE_PCI1);
    pReg(PCIIF_EXPANSION_ROM_BAR_SIZE_PCI0);
    pReg(PCIIF_EXPANSION_ROM_BAR_SIZE_PCI1);
    pReg(PCIIF_BASE_ADDR_ENABLE_PCI0);
    pReg(PCIIF_BASE_ADDR_ENABLE_PCI1);
    pReg(PCIIF_CS0_BASE_ADDR_REMAP_PCI0);
    pReg(PCIIF_CS0_BASE_ADDR_REMAP_PCI1);
    pReg(PCIIF_CS1_BASE_ADDR_REMAP_PCI0);
    pReg(PCIIF_CS1_BASE_ADDR_REMAP_PCI1);
    pReg(PCIIF_CS2_BASE_ADDR_REMAP_PCI0);
    pReg(PCIIF_CS2_BASE_ADDR_REMAP_PCI1);
    pReg(PCIIF_CS3_BASE_ADDR_REMAP_PCI0);
    pReg(PCIIF_CS3_BASE_ADDR_REMAP_PCI1);
    pReg(PCIIF_DEVCS0_BASE_ADDR_REMAP_PCI0);
    pReg(PCIIF_DEVCS0_BASE_ADDR_REMAP_PCI1);
    pReg(PCIIF_DEVCS1_BASE_ADDR_REMAP_PCI0);
    pReg(PCIIF_DEVCS1_BASE_ADDR_REMAP_PCI1);
    pReg(PCIIF_DEVCS2_BASE_ADDR_REMAP_PCI0);
    pReg(PCIIF_DEVCS2_BASE_ADDR_REMAP_PCI1);
    pReg(PCIIF_DEVCS3_BASE_ADDR_REMAP_PCI0);
    pReg(PCIIF_DEVCS3_BASE_ADDR_REMAP_PCI1);
    pReg(PCIIF_BOOTCS_BASE_ADDR_REMAP_PCI0);
    pReg(PCIIF_BOOTCS_BASE_ADDR_REMAP_PCI1);
    pReg(PCIIF_P2P_MEM0_BASE_ADDR_REMAP_LOW_PCI0);
    pReg(PCIIF_P2P_MEM0_BASE_ADDR_REMAP_LOW_PCI1);
    pReg(PCIIF_P2P_MEM0_BASE_ADDR_REMAP_HI_PCI0);
    pReg(PCIIF_P2P_MEM0_BASE_ADDR_REMAP_HI_PCI1);
    pReg(PCIIF_P2P_MEM1_BASE_ADDR_REMAP_LOW_PCI0);
    pReg(PCIIF_P2P_MEM1_BASE_ADDR_REMAP_LOW_PCI1);
    pReg(PCIIF_P2P_MEM1_BASE_ADDR_REMAP_HI_PCI0);
    pReg(PCIIF_P2P_MEM1_BASE_ADDR_REMAP_HI_PCI1);
    pReg(PCIIF_P2P_IO_BASE_ADDR_REMAP_PCI0);
    pReg(PCIIF_P2P_IO_BASE_ADDR_REMAP_PCI1);
    pReg(PCIIF_CPU_BASE_ADDR_REMAP_LOW_PCI0);
    pReg(PCIIF_CPU_BASE_ADDR_REMAP_LOW_PCI1);
    pReg(PCIIF_CPU_BASE_ADDR_REMAP_HI_PCI0);
    pReg(PCIIF_CPU_BASE_ADDR_REMAP_HI_PCI1);
    pReg(PCIIF_HDRS_RETARG_CTRL_PCI0);
    pReg(PCIIF_HDRS_RETARG_CTRL_PCI1);
    pReg(PCIIF_INTEGRATED_SRAM_BASE_ADDR_REMAP_PCI0);
    pReg(PCIIF_INTEGRATED_SRAM_BASE_ADDR_REMAP_PCI1);
    pReg(PCIIF_EXPANSION_ROM_BASE_ADDR_REMAP_PCI0);
    pReg(PCIIF_EXPANSION_ROM_BASE_ADDR_REMAP_PCI1);
    pReg(PCIIF_ADDR_DECODE_CTRL_PCI0);
    pReg(PCIIF_ADDR_DECODE_CTRL_PCI1);
    pReg(PCIIF_HDRS_RETARG_BASE_PCI0);
    pReg(PCIIF_HDRS_RETARG_BASE_PCI1);
    pReg(PCIIF_HDRS_RETARG_BASE_HI_PCI0);
    pReg(PCIIF_HDRS_RETARG_BASE_HI_PCI1);
    pReg(PCIIF_DLL_STATUS_AND_CTRL_PCI0);
    pReg(PCIIF_DLL_STATUS_AND_CTRL_PCI1);
    pReg(PCIIF_MPP_PADS_CALIBRATION_PCI0);
    pReg(PCIIF_MPP_PADS_CALIBRATION_PCI1);
    pReg(PCIIF_PCI_CMD_PCI0);
    pReg(PCIIF_PCI_CMD_PCI1);
    pReg(PCIIF_MODE_PCI0);
    pReg(PCIIF_MODE_PCI1);
    pReg(PCIIF_RETRY_PCI0);
    pReg(PCIIF_RETRY_PCI1);
    pReg(PCIIF_DISCARD_TIMER_PCI0);
    pReg(PCIIF_DISCARD_TIMER_PCI1);
    pReg(PCIIF_MSI_TRIGGER_TIMER_PCI0);
    pReg(PCIIF_MSI_TRIGGER_TIMER_PCI1);
    pReg(PCIIF_ARB_CTRL_PCI0);
    pReg(PCIIF_ARB_CTRL_PCI1);
    pReg(PCIIF_INTERFACE_CROSSBAR_CTRL_LOW_PCI0);
    pReg(PCIIF_INTERFACE_CROSSBAR_CTRL_LOW_PCI1);
    pReg(PCIIF_INTERFACE_CROSSBAR_CTRL_HI_PCI0);
    pReg(PCIIF_INTERFACE_CROSSBAR_CTRL_HI_PCI1);
    pReg(PCIIF_INTERFACE_CROSSBAR_TIMEOUT_PCI0);
    pReg(PCIIF_INTERFACE_CROSSBAR_TIMEOUT_PCI1);
    pReg(PCIIF_SYNC_BARRIER_TRIGGER_PCI0);
    pReg(PCIIF_SYNC_BARRIER_TRIGGER_PCI1);
    pReg(PCIIF_SYNC_BARRIER_VIRTUAL_PCI0);
    pReg(PCIIF_SYNC_BARRIER_VIRTUAL_PCI1);
    pReg(PCIIF_P2P_CFG_PCI0);
    pReg(PCIIF_P2P_CFG_PCI1);
    pReg(PCIIF_ACCESS_CTRL_BASE0_LOW_PCI0);
    pReg(PCIIF_ACCESS_CTRL_BASE0_LOW_PCI1);
    pReg(PCIIF_ACCESS_CTRL_BASE0_HI_PCI0);
    pReg(PCIIF_ACCESS_CTRL_BASE0_HI_PCI1);
    pReg(PCIIF_ACCESS_CTRL_SIZE0_PCI0);
    pReg(PCIIF_ACCESS_CTRL_SIZE0_PCI1);
    pReg(PCIIF_ACCESS_CTRL_BASE1_LOW_PCI0);
    pReg(PCIIF_ACCESS_CTRL_BASE1_LOW_PCI1);
    pReg(PCIIF_ACCESS_CTRL_BASE1_HI_PCI0);
    pReg(PCIIF_ACCESS_CTRL_BASE1_HI_PCI1);
    pReg(PCIIF_ACCESS_CTRL_SIZE1_PCI0);
    pReg(PCIIF_ACCESS_CTRL_SIZE1_PCI1);
    pReg(PCIIF_ACCESS_CTRL_BASE2_LOW_PCI0);
    pReg(PCIIF_ACCESS_CTRL_BASE2_LOW_PCI1);
    pReg(PCIIF_ACCESS_CTRL_BASE2_HI_PCI0);
    pReg(PCIIF_ACCESS_CTRL_BASE2_HI_PCI1);
    pReg(PCIIF_ACCESS_CTRL_SIZE2_PCI0);
    pReg(PCIIF_ACCESS_CTRL_SIZE2_PCI1);
    pReg(PCIIF_ACCESS_CTRL_BASE3_LOW_PCI0);
    pReg(PCIIF_ACCESS_CTRL_BASE3_LOW_PCI1);
    pReg(PCIIF_ACCESS_CTRL_BASE3_HI_PCI0);
    pReg(PCIIF_ACCESS_CTRL_BASE3_HI_PCI1);
    pReg(PCIIF_ACCESS_CTRL_SIZE3_PCI0);
    pReg(PCIIF_ACCESS_CTRL_SIZE3_PCI1);
    pReg(PCIIF_ACCESS_CTRL_BASE4_LOW_PCI0);
    pReg(PCIIF_ACCESS_CTRL_BASE4_LOW_PCI1);
    pReg(PCIIF_ACCESS_CTRL_BASE4_HI_PCI0);
    pReg(PCIIF_ACCESS_CTRL_BASE4_HI_PCI1);
    pReg(PCIIF_ACCESS_CTRL_SIZE4_PCI0);
    pReg(PCIIF_ACCESS_CTRL_SIZE4_PCI1);
    pReg(PCIIF_ACCESS_CTRL_BASE5_LOW_PCI0);
    pReg(PCIIF_ACCESS_CTRL_BASE5_LOW_PCI1);
    pReg(PCIIF_ACCESS_CTRL_BASE5_HI_PCI0);
    pReg(PCIIF_ACCESS_CTRL_BASE5_HI_PCI1);
    pReg(PCIIF_ACCESS_CTRL_SIZE5_PCI0);
    pReg(PCIIF_ACCESS_CTRL_SIZE5_PCI1);
    pReg(PCIIF_SERR_MASK_PCI0);
    pReg(PCIIF_SERR_MASK_PCI1);
    pReg(PCIIF_CFG_ADDR_PCI0);
    pReg(PCIIF_CFG_ADDR_PCI1);
    pReg(PCIIF_CFG_DATA_PCI0);
    pReg(PCIIF_CFG_DATA_PCI1);
    pReg(PCIIF_INTERRUPT_ACK_PCI0);
    pReg(PCIIF_INTERRUPT_ACK_PCI1);
    pReg(PCIIF_INTERRUPT_CAUSE_PCI0);
    pReg(PCIIF_INTERRUPT_CAUSE_PCI1);
    pReg(PCIIF_INTERRUPT_MASK_PCI0);
    pReg(PCIIF_INTERRUPT_MASK_PCI1);
    pReg(PCIIF_ERR_ADDR_LOW_PCI0);
    pReg(PCIIF_ERR_ADDR_LOW_PCI1);
    pReg(PCIIF_ERR_ADDR_HI_PCI0);
    pReg(PCIIF_ERR_ADDR_HI_PCI1);
    pReg(PCIIF_ERR_ATTR_PCI0);
    pReg(PCIIF_ERR_ATTR_PCI1);
    pReg(PCIIF_ERR_CMD_PCI0);
    pReg(PCIIF_ERR_CMD_PCI1);
    printf("\n\r");

    printf("Message Unit Registers:\n\r");
    pReg(MUIF_INBND_MSG0_PCI0);
    pReg(MUIF_INBND_MSG0_PCI1);
    pReg(MUIF_INBND_MSG1_PCI0);
    pReg(MUIF_INBND_MSG1_PCI1);
    pReg(MUIF_OUTBND_MSG0_PCI0);
    pReg(MUIF_OUTBND_MSG0_PCI1);
    pReg(MUIF_OUTBND_MSG1_PCI0);
    pReg(MUIF_OUTBND_MSG1_PCI1);
    pReg(MUIF_INBND_DOORBELL_PCI0);
    pReg(MUIF_INBND_DOORBELL_PCI1);
    pReg(MUIF_INBND_INTERRUPT_CAUSE_PCI0);
    pReg(MUIF_INBND_INTERRUPT_CAUSE_PCI1);
    pReg(MUIF_INBND_INTERRUPT_MASK_PCI0);
    pReg(MUIF_INBND_INTERRUPT_MASK_PCI1);
    pReg(MUIF_OUTBND_DOORBELL_PCI0);
    pReg(MUIF_OUTBND_DOORBELL_PCI1);
    pReg(MUIF_OUTBND_INTERRUPT_CAUSE_PCI0);
    pReg(MUIF_OUTBND_INTERRUPT_CAUSE_PCI1);
    pReg(MUIF_OUTBND_INTERRUPT_MASK_PCI0);
    pReg(MUIF_OUTBND_INTERRUPT_MASK_PCI1);
    pReg(MUIF_INBND_Q_PORT_VIRTUAL_PCI0);
    pReg(MUIF_INBND_Q_PORT_VIRTUAL_PCI1);
    pReg(MUIF_OUTBND_Q_PORT_VIRTUAL_PCI0);
    pReg(MUIF_OUTBND_Q_PORT_VIRTUAL_PCI1);
    pReg(MUIF_Q_CTRL_PCI0);
    pReg(MUIF_Q_CTRL_PCI1);
    pReg(MUIF_INBND_POST_HEAD_PTR_PCI0);
    pReg(MUIF_INBND_POST_HEAD_PTR_PCI1);
    pReg(MUIF_Q_BASE_ADDR_PCI0);
    pReg(MUIF_Q_BASE_ADDR_PCI1);
    pReg(MUIF_INBND_FREE_HEAD_PTR_PCI0);
    pReg(MUIF_INBND_FREE_HEAD_PTR_PCI1);
    pReg(MUIF_INBND_FREE_TAIL_PTR_PCI0);
    pReg(MUIF_INBND_FREE_TAIL_PTR_PCI1);
    pReg(MUIF_INBND_POST_TAIL_PTR_PCI0);
    pReg(MUIF_INBND_POST_TAIL_PTR_PCI1);
    pReg(MUIF_OUTBND_FREE_HEAD_PTR_PCI0);
    pReg(MUIF_OUTBND_FREE_HEAD_PTR_PCI1);
    pReg(MUIF_OUTBND_FREE_TAIL_PTR_PCI0);
    pReg(MUIF_OUTBND_FREE_TAIL_PTR_PCI1);
    pReg(MUIF_OUTBND_POST_HEAD_PTR_PCI0);
    pReg(MUIF_OUTBND_POST_HEAD_PTR_PCI1);
    pReg(MUIF_OUTBND_POST_TAIL_PTR_PCI0);
    pReg(MUIF_OUTBND_POST_TAIL_PTR_PCI1);
    printf("\n\r");

    printf("Gigabit Ethernet Registers:\n\r");
    pReg(GE_PHY_ADDR_REG);
    pReg(GE_SMI_REG);
    pReg(GE_ENET_UNIT_DEFAULT_ADDR_REG);
    pReg(GE_ENET_UNIT_DEFAULT_ID_REG);
    pReg(GE_ENET_UNIT_INTERRUPT_CAUSE_REG);
    pReg(GE_ENET_UNIT_INTERRUPT_MASK_REG);
    pReg(GE_ENET_UNIT_ERR_ADDR_REG);
    pReg(GE_ENET_UNIT_INTERNAL_ADDR_ERR_REG);
    pReg(GE_BASE_ADDR_BA0);
    pReg(GE_BASE_ADDR_BA1);
    pReg(GE_BASE_ADDR_BA2);
    pReg(GE_BASE_ADDR_BA3);
    pReg(GE_BASE_ADDR_BA4);
    pReg(GE_BASE_ADDR_BA5);
    pReg(GE_SIZE_SR0);
    pReg(GE_SIZE_SR1);
    pReg(GE_SIZE_SR2);
    pReg(GE_SIZE_SR3);
    pReg(GE_SIZE_SR4);
    pReg(GE_SIZE_SR5);
    pReg(GE_HDR_RETARG_BASE_REG);
    pReg(GE_HDR_RETARG_CTRL_REG);
    pReg(GE_HI_ADDR_REMAP_HARR0);
    pReg(GE_HI_ADDR_REMAP_HARR1);
    pReg(GE_HI_ADDR_REMAP_HARR2);
    pReg(GE_HI_ADDR_REMAP_HARR3);
    pReg(GE_BASE_ADDR_ENABLE_REG);
    pReg(GE_ENET_PORT_ACCESS_PROTECT_PORT0);
    pReg(GE_ENET_PORT_ACCESS_PROTECT_PORT1);
    pReg(GE_ENET_PORT_ACCESS_PROTECT_PORT2);
    pReg(GE_CFG_PORT0);
    pReg(GE_CFG_PORT1);
    pReg(GE_CFG_PORT2);
    pReg(GE_CFG_EXTEND_PORT0);
    pReg(GE_CFG_EXTEND_PORT1);
    pReg(GE_CFG_EXTEND_PORT2);
    pReg(GE_MII_SERIAL_PARAMS_PORT0);
    pReg(GE_MII_SERIAL_PARAMS_PORT1);
    pReg(GE_MII_SERIAL_PARAMS_PORT2);
    pReg(GE_GMII_SERIAL_PARAMS_PORT0);
    pReg(GE_GMII_SERIAL_PARAMS_PORT1);
    pReg(GE_GMII_SERIAL_PARAMS_PORT2);
    pReg(GE_VLAN_ETHERTYPE_PORT0);
    pReg(GE_VLAN_ETHERTYPE_PORT1);
    pReg(GE_VLAN_ETHERTYPE_PORT2);
    pReg(GE_MAC_ADDR_LOW_PORT0);
    pReg(GE_MAC_ADDR_LOW_PORT1);
    pReg(GE_MAC_ADDR_LOW_PORT2);
    pReg(GE_MAC_ADDR_HI_PORT0);
    pReg(GE_MAC_ADDR_HI_PORT1);
    pReg(GE_MAC_ADDR_HI_PORT2);
    pReg(GE_SDMA_CFG_PORT0);
    pReg(GE_SDMA_CFG_PORT1);
    pReg(GE_SDMA_CFG_PORT2);
    pReg(GE_IP_DIFF_SVCS_CODEPT_0_TO_PRIORITY_PORT0);
    pReg(GE_IP_DIFF_SVCS_CODEPT_0_TO_PRIORITY_PORT1);
    pReg(GE_IP_DIFF_SVCS_CODEPT_0_TO_PRIORITY_PORT2);
    pReg(GE_IP_DIFF_SVCS_CODEPT_1_TO_PRIORITY_PORT0);
    pReg(GE_IP_DIFF_SVCS_CODEPT_1_TO_PRIORITY_PORT1);
    pReg(GE_IP_DIFF_SVCS_CODEPT_1_TO_PRIORITY_PORT2);
    pReg(GE_IP_DIFF_SVCS_CODEPT_2_TO_PRIORITY_PORT0);
    pReg(GE_IP_DIFF_SVCS_CODEPT_3_TO_PRIORITY_PORT0);
    pReg(GE_IP_DIFF_SVCS_CODEPT_4_TO_PRIORITY_PORT0);
    pReg(GE_IP_DIFF_SVCS_CODEPT_5_TO_PRIORITY_PORT0);
    pReg(GE_IP_DIFF_SVCS_CODEPT_3_TO_PRIORITY_PORT1);
    pReg(GE_IP_DIFF_SVCS_CODEPT_4_TO_PRIORITY_PORT1);
    pReg(GE_IP_DIFF_SVCS_CODEPT_5_TO_PRIORITY_PORT1);
    pReg(GE_IP_DIFF_SVCS_CODEPT_3_TO_PRIORITY_PORT2);
    pReg(GE_IP_DIFF_SVCS_CODEPT_4_TO_PRIORITY_PORT2);
    pReg(GE_IP_DIFF_SVCS_CODEPT_5_TO_PRIORITY_PORT2);
    pReg(GE_IP_DIFF_SVCS_CODEPT_6_TO_PRIORITY_PORT0);
    pReg(GE_IP_DIFF_SVCS_CODEPT_6_TO_PRIORITY_PORT1);
    pReg(GE_IP_DIFF_SVCS_CODEPT_6_TO_PRIORITY_PORT2);
    pReg(GE_SERIAL_CTRL_PSCR_PORT0);
    pReg(GE_SERIAL_CTRL_PSCR_PORT1);
    pReg(GE_SERIAL_CTRL_PSCR_PORT2);
    pReg(GE_VLAN_PRIORITY_TAG_TO_PRIORITY_VPT2P_PORT0);
    pReg(GE_VLAN_PRIORITY_TAG_TO_PRIORITY_VPT2P_PORT1);
    pReg(GE_VLAN_PRIORITY_TAG_TO_PRIORITY_VPT2P_PORT2);
    pReg(GE_ENET_PORT_STATUS_PSR_PORT0);
    pReg(GE_ENET_PORT_STATUS_PSR_PORT1);
    pReg(GE_ENET_PORT_STATUS_PSR_PORT2);
    pReg(GE_XMIT_Q_CMD_PORT0);
    pReg(GE_XMIT_Q_CMD_PORT1);
    pReg(GE_XMIT_Q_CMD_PORT2);
    pReg(GE_XMIT_Q_FIXED_PRIORITY_CFG_PORT0);
    pReg(GE_XMIT_Q_FIXED_PRIORITY_CFG_PORT1);
    pReg(GE_XMIT_Q_FIXED_PRIORITY_CFG_PORT2);
    pReg(GE_XMIT_TKN_BKT_RATE_CFG_PORT0);
    pReg(GE_XMIT_TKN_BKT_RATE_CFG_PORT1);
    pReg(GE_XMIT_TKN_BKT_RATE_CFG_PORT2);
    pReg(GE_MAXIMUM_XMIT_UNIT_PORT0);
    pReg(GE_MAXIMUM_XMIT_UNIT_PORT1);
    pReg(GE_MAXIMUM_XMIT_UNIT_PORT2);
    pReg(GE_MAXIMUM_TKN_BKT_SIZE_PORT0);
    pReg(GE_MAXIMUM_TKN_BKT_SIZE_PORT1);
    pReg(GE_MAXIMUM_TKN_BKT_SIZE_PORT2);
    pReg(GE_INTERRUPT_CAUSE_PORT0);
    pReg(GE_INTERRUPT_CAUSE_PORT1);
    pReg(GE_INTERRUPT_CAUSE_PORT2);
    pReg(GE_INTERRUPT_CAUSE_EXTEND_PORT0);
    pReg(GE_INTERRUPT_CAUSE_EXTEND_PORT1);
    pReg(GE_INTERRUPT_CAUSE_EXTEND_PORT2);
    pReg(GE_INTERRUPT_MASK_PIMR_PORT0);
    pReg(GE_INTERRUPT_MASK_PIMR_PORT1);
    pReg(GE_INTERRUPT_MASK_PIMR_PORT2);
    pReg(GE_EXTEND_INTERRUPT_MASK_PORT0);
    pReg(GE_EXTEND_INTERRUPT_MASK_PORT1);
    pReg(GE_EXTEND_INTERRUPT_MASK_PORT2);
    pReg(GE_RX_FIFO_URGENT_THRESHOLD_PORT0);
    pReg(GE_RX_FIFO_URGENT_THRESHOLD_PORT1);
    pReg(GE_RX_FIFO_URGENT_THRESHOLD_PORT2);
    pReg(GE_TX_FIFO_URGENT_THRESHOLD_PORT0);
    pReg(GE_TX_FIFO_URGENT_THRESHOLD_PORT1);
    pReg(GE_TX_FIFO_URGENT_THRESHOLD_PORT2);
    pReg(GE_RX_MINIMAL_FRAME_SIZE_PXMFSR_PORT1);
    pReg(GE_RX_MINIMAL_FRAME_SIZE_PXMFSR_PORT2);
    pReg(GE_RX_DISCARD_FRAME_CTR_PORT0);
    pReg(GE_RX_DISCARD_FRAME_CTR_PORT1);
    pReg(GE_RX_DISCARD_FRAME_CTR_PORT2);
    pReg(GE_OVERRUN_FRAME_CTR_PORT0);
    pReg(GE_OVERRUN_FRAME_CTR_PORT1);
    pReg(GE_OVERRUN_FRAME_CTR_PORT2);
    pReg(GE_INTERNAL_ADDR_ERR_PORT0);
    pReg(GE_INTERNAL_ADDR_ERR_PORT1);
    pReg(GE_INTERNAL_ADDR_ERR_PORT2);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q0_PORT0);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q1_PORT0);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q2_PORT0);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q3_PORT0);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q4_PORT0);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q5_PORT0);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q6_PORT0);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q7_PORT0);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q0_PORT1);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q1_PORT1);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q2_PORT1);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q3_PORT1);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q4_PORT1);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q5_PORT1);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q6_PORT1);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q7_PORT1);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q0_PORT2);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q1_PORT2);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q2_PORT2);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q3_PORT2);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q4_PORT2);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q5_PORT2);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q6_PORT2);
    pReg(GE_ENET_CURR_RCV_DESC_PTR_Q7_PORT2);
    pReg(GE_RCV_Q_CMD_PORT0);
    pReg(GE_RCV_Q_CMD_PORT1);
    pReg(GE_RCV_Q_CMD_PORT2);
    pReg(GE_XMIT_CURR_SERVED_DESC_PTR_PORT0);
    pReg(GE_XMIT_CURR_SERVED_DESC_PTR_PORT1);
    pReg(GE_XMIT_CURR_SERVED_DESC_PTR_PORT2);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q0_PORT0);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q1_PORT0);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q2_PORT0);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q3_PORT0);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q4_PORT0);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q5_PORT0);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q6_PORT0);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q7_PORT0);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q0_PORT1);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q1_PORT1);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q2_PORT1);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q3_PORT1);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q4_PORT1);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q5_PORT1);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q6_PORT1);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q7_PORT1);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q0_PORT2);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q1_PORT2);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q2_PORT2);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q3_PORT2);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q4_PORT2);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q5_PORT2);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q6_PORT2);
    pReg(GE_XMIT_CURR_Q_DESC_PTR_Q7_PORT2);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q0_PORT0);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q1_PORT0);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q2_PORT0);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q3_PORT0);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q4_PORT0);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q5_PORT0);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q6_PORT0);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q7_PORT0);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q0_PORT1);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q1_PORT1);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q2_PORT1);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q3_PORT1);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q4_PORT1);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q5_PORT1);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q6_PORT1);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q7_PORT1);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q0_PORT2);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q1_PORT2);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q2_PORT2);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q3_PORT2);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q4_PORT2);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q5_PORT2);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q6_PORT2);
    pReg(GE_XMIT_Q_TKN_BKT_CTR_Q7_PORT2);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q0_PORT0);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q1_PORT0);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q2_PORT0);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q3_PORT0);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q4_PORT0);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q5_PORT0);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q6_PORT0);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q7_PORT0);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q0_PORT1);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q1_PORT1);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q2_PORT1);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q3_PORT1);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q4_PORT1);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q5_PORT1);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q6_PORT1);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q7_PORT1);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q0_PORT2);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q1_PORT2);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q2_PORT2);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q3_PORT2);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q4_PORT2);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q5_PORT2);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q6_PORT2);
    pReg(GE_XMIT_Q_TKN_BKT_CFG_Q7_PORT2);
    pReg(GE_DEST_ADDR_FILTER_SPCL_MCAST_TBL_PORT0);
    pReg(GE_DEST_ADDR_FILTER_SPCL_MCAST_TBL_PORT1);
    pReg(GE_DEST_ADDR_FILTER_SPCL_MCAST_TBL_PORT2);
    pReg(GE_XMIT_Q_ARB_CFG_Q0_PORT0);
    pReg(GE_XMIT_Q_ARB_CFG_Q1_PORT0);
    pReg(GE_XMIT_Q_ARB_CFG_Q2_PORT0);
    pReg(GE_XMIT_Q_ARB_CFG_Q3_PORT0);
    pReg(GE_XMIT_Q_ARB_CFG_Q4_PORT0);
    pReg(GE_XMIT_Q_ARB_CFG_Q5_PORT0);
    pReg(GE_XMIT_Q_ARB_CFG_Q6_PORT0);
    pReg(GE_XMIT_Q_ARB_CFG_Q7_PORT0);
    pReg(GE_XMIT_Q_ARB_CFG_Q0_PORT1);
    pReg(GE_XMIT_Q_ARB_CFG_Q1_PORT1);
    pReg(GE_XMIT_Q_ARB_CFG_Q2_PORT1);
    pReg(GE_XMIT_Q_ARB_CFG_Q3_PORT1);
    pReg(GE_XMIT_Q_ARB_CFG_Q4_PORT1);
    pReg(GE_XMIT_Q_ARB_CFG_Q5_PORT1);
    pReg(GE_XMIT_Q_ARB_CFG_Q6_PORT1);
    pReg(GE_XMIT_Q_ARB_CFG_Q7_PORT1);
    pReg(GE_XMIT_Q_ARB_CFG_Q0_PORT2);
    pReg(GE_XMIT_Q_ARB_CFG_Q1_PORT2);
    pReg(GE_XMIT_Q_ARB_CFG_Q2_PORT2);
    pReg(GE_XMIT_Q_ARB_CFG_Q3_PORT2);
    pReg(GE_XMIT_Q_ARB_CFG_Q4_PORT2);
    pReg(GE_XMIT_Q_ARB_CFG_Q5_PORT2);
    pReg(GE_XMIT_Q_ARB_CFG_Q6_PORT2);
    pReg(GE_XMIT_Q_ARB_CFG_Q7_PORT2);
    pReg(GE_XMIT_TKN_BKT_CTR_PORT0);
    pReg(GE_XMIT_TKN_BKT_CTR_PORT1);
    pReg(GE_XMIT_TKN_BKT_CTR_PORT2);
    pReg(GE_DEST_ADDR_FILTER_OTHER_MCAST_TBL_PORT0);
    pReg(GE_DEST_ADDR_FILTER_OTHER_MCAST_TBL_PORT1);
    pReg(GE_DEST_ADDR_FILTER_OTHER_MCAST_TBL_PORT2);
    pReg(GE_DEST_ADDR_FILTER_UNICAST_TBL_PORT0);
    pReg(GE_DEST_ADDR_FILTER_UNICAST_TBL_PORT1);
    pReg(GE_DEST_ADDR_FILTER_UNICAST_TBL_PORT2);
    pReg(GE_MAC_MIB_CTRS_PORT0);
    pReg(GE_MAC_MIB_CTRS_PORT1);
    pReg(GE_MAC_MIB_CTRS_PORT2);
    printf("\n\r");

    printf("Communication Unit Registers:\n\r");
    pReg(CUI_BASE_ADDR0);
    pReg(CUI_BASE_ADDR1);
    pReg(CUI_BASE_ADDR2);
    pReg(CUI_BASE_ADDR3);
    pReg(CUI_SZ_REG0);
    pReg(CUI_SZ_REG1);
    pReg(CUI_SZ_REG2);
    pReg(CUI_SZ_REG3);
    pReg(CUI_HI_ADDR_RMAP0);
    pReg(CUI_HI_ADDR_RMAP1);
    pReg(CUI_BASE_ADDR_ENB);
    pReg(CUI_ARB_CTRL);
    pReg(CUI_MPSC0);
    pReg(CUI_MPSC1);
    pReg(CUI_INTRNL_SPACE_BASE_ADDR);
    pReg(CUI_INT_CAUSE);
    pReg(CUI_CFG);
    pReg(CUI_XBAR_TMOUT);
    pReg(CUI_INT_MASK);
    pReg(CUI_MPSC_ROUTG);
    pReg(CUI_RX_CLK_ROUTG);
    pReg(CUI_ERR_ADDR);
    pReg(CUI_MPSC_CAUSE0);
    pReg(CUI_MPSC_CAUSE1);
    pReg(CUI_TX_CLK_ROUTG);
    pReg(CUI_MPSC_MASK0);
    pReg(CUI_MPSC_MASK1);
    pReg(CUI_MPSCX_MAIN_CFG0_LO);
    pReg(CUI_MPSCX_MAIN_CFG1_LO);
    pReg(CUI_MPSCX_MAIN_CFG0_HI);
    pReg(CUI_MPSCX_MAIN_CFG1_HI);
    pReg(CUI_SDMA_CFG_CHAN0);
    pReg(CUI_SDMA_CFG_CHAN1);
    pReg(CUI_SDMA_CMD_CHAN0);
    pReg(CUI_SDMA_CMD_CHAN1);
    pReg(CUI_SDMA_CAUSE);
    pReg(CUI_SDMA_MASK);
    printf("\n\r");

    printf("Baude Rate Generator Registers:\n\r");
    pReg(BRG_0_CFG_REG);
    pReg(BRG_1_CFG_REG);
    pReg(BRG_0_BAUD_TUNING_REG);
    pReg(BRG_1_BAUD_TUNING_REG);
    pReg(BRG_CAUSE_REG);
    pReg(BRG_MASK_REG);
    printf("\n\r");

    printf("DMA Registers:\n\r");
    pReg(IDMA_BYTE_COUNT_CHAN0);
    pReg(IDMA_BYTE_COUNT_CHAN1);
    pReg(IDMA_BYTE_COUNT_CHAN2);
    pReg(IDMA_BYTE_COUNT_CHAN3);
    pReg(IDMA_SRC_ADDR_CHAN0);
    pReg(IDMA_SRC_ADDR_CHAN1);
    pReg(IDMA_SRC_ADDR_CHAN2);
    pReg(IDMA_SRC_ADDR_CHAN3);
    pReg(IDMA_DEST_ADDR_CHAN0);
    pReg(IDMA_DEST_ADDR_CHAN1);
    pReg(IDMA_DEST_ADDR_CHAN2);
    pReg(IDMA_DEST_ADDR_CHAN3);
    pReg(IDMA_NEXT_DESC_PTR_CHAN0);
    pReg(IDMA_NEXT_DESC_PTR_CHAN1);
    pReg(IDMA_NEXT_DESC_PTR_CHAN2);
    pReg(IDMA_NEXT_DESC_PTR_CHAN3);
    pReg(IDMA_CURR_DESC_PTR_CHAN0);
    pReg(IDMA_CURR_DESC_PTR_CHAN1);
    pReg(IDMA_CURR_DESC_PTR_CHAN2);
    pReg(IDMA_CURR_DESC_PTR_CHAN3);
    pReg(IDMA_BASE_ADDR_REG0);
    pReg(IDMA_BASE_ADDR_REG1);
    pReg(IDMA_BASE_ADDR_REG2);
    pReg(IDMA_BASE_ADDR_REG3);
    pReg(IDMA_BASE_ADDR_REG4);
    pReg(IDMA_BASE_ADDR_REG5);
    pReg(IDMA_BASE_ADDR_REG6);
    pReg(IDMA_BASE_ADDR_REG7);
    pReg(IDMA_SIZE_REG0);
    pReg(IDMA_SIZE_REG1);
    pReg(IDMA_SIZE_REG2);
    pReg(IDMA_SIZE_REG3);
    pReg(IDMA_SIZE_REG4);
    pReg(IDMA_SIZE_REG5);
    pReg(IDMA_SIZE_REG6);
    pReg(IDMA_SIZE_REG7);
    pReg(IDMA_HI_ADDR_REMAP0);
    pReg(IDMA_HI_ADDR_REMAP1);
    pReg(IDMA_HI_ADDR_REMAP2);
    pReg(IDMA_HI_ADDR_REMAP3);
    pReg(IDMA_BASE_ADDR_ENABLE);
    pReg(IDMA_CHAN0_ACCESS_PROTECT);
    pReg(IDMA_CHAN1_ACCESS_PROTECT);
    pReg(IDMA_CHAN2_ACCESS_PROTECT);
    pReg(IDMA_CHAN3_ACCESS_PROTECT);
    pReg(IDMA_HDRS_RETARG_CTRL);
    pReg(IDMA_CHAN0_CTRL_LOW);
    pReg(IDMA_CHAN1_CTRL_LOW);
    pReg(IDMA_CHAN2_CTRL_LOW);
    pReg(IDMA_CHAN3_CTRL_LOW);
    pReg(IDMA_HDR_RETARG_BASE);
    pReg(IDMA_CHAN0_CTRL_HI);
    pReg(IDMA_CHAN1_CTRL_HI);
    pReg(IDMA_CHAN2_CTRL_HI);
    pReg(IDMA_CHAN3_CTRL_HI);
    pReg(IDMA_ARB_CTRL);
    pReg(IDMA_INTERRUPT_CAUSE);
    pReg(IDMA_INTERRUPT_MASK);
    pReg(IDMA_CROSSBAR_TIMEOUT);
    pReg(IDMA_ERR_ADDR);
    pReg(IDMA_ERR_SELECT);
    printf("\n\r");

    printf("Timer Registers:\n\r");
    pReg(TMR_CNTR0);
    pReg(TMR_CNTR1);
    pReg(TMR_CNTR2);
    pReg(TMR_CNTR3);
    pReg(TMR_CNTR_CTRL);
    pReg(TMR_CNTR_INT_CAUSE);
    pReg(TMR_CNTR_INT_MASK);
    printf("\n\r");

    printf("Watchdog Registers:\n\r");
    pReg(WDOG_CFG_REG);
    pReg(WDOG_VAL_REG);
    printf("\n\r");

    printf("I2C Registers:\n\r");
    pReg(I2C_SLV_ADDR);
    pReg(I2C_EXTENDED_SLV_ADDR);
    pReg(I2C_DATA);
    pReg(I2C_CTRL);
    pReg(I2C_STATUS);
    pReg(I2C_BAUDE_RATE);
    pReg(I2C_SOFT_RESET);
    printf("\n\r");

    printf("GPP Registers:\n\r");
    pReg(GPP_IO_CTRL);
    pReg(GPP_LEVEL_CTRL);
    pReg(GPP_VAL);
    pReg(GPP_INTERRUPT_CAUSE);
    pReg(GPP_INTERRUPT_MASK0);
    pReg(GPP_INTERRUPT_MASK1);
    pReg(GPP_VAL_SET);
    pReg(GPP_VAL_CLEAR);
    printf("\n\r");

    printf("Interrupt Controller Registers:\n\r");
    pReg(ICI_MAIN_INTERRUPT_CAUSE_LOW);
    pReg(ICI_MAIN_INTERRUPT_CAUSE_HI);
    pReg(ICI_CPU_INT0_MASK_LOW);
    pReg(ICI_CPU_INT0_MASK_HI);
    pReg(ICI_CPU_INT0_SELECT_CAUSE);
    pReg(ICI_CPU_INT1_MASK_LOW);
    pReg(ICI_CPU_INT1_MASK_HI);
    pReg(ICI_CPU_INT1_SELECT_CAUSE);
    pReg(ICI_INT0_MASK_LOW);
    pReg(ICI_INT0_MASK_HI);
    pReg(ICI_INT0_SELECT_CAUSE);
    pReg(ICI_INT1_MASK_LOW);
    pReg(ICI_INT1_MASK_HI);
    pReg(ICI_INT1_SELECT_CAUSE);
    printf("\n\r");

    printf("MPP Registers:\n\r");
    pReg(MPP_CTRL0);
    pReg(MPP_CTRL1);
    pReg(MPP_CTRL2);
    pReg(MPP_CTRL3);
    printf("\n\r");

    printf("Serial Initialization Registers:\n\r");
    pReg(SII_SERIAL_INIT_LAST_DATA);
    pReg(SII_SERIAL_INIT_CTRL);
    pReg(SII_SERIAL_INIT_STATUS);
    printf("\n\r");

    printf("Function 0:                                         Bus 0       Bus 1\n\r");
    pciRead(PCIIF_DEVICE_AND_VENDOR_ID_PCICFG,0);
    pciRead(PCIIF_STATUS_AND_CMD_PCICFG,0);
    pciRead(PCIIF_CLASS_CODE_AND_REVISION_ID_PCICFG,0);
    pciRead(PCIIF_BIST_LATENCY_CACHE_PCICFG,0);
    pciRead(PCIIF_CS0_BASE_ADDR_LOW_PCICFG,0);
    pciRead(PCIIF_CS0_BASE_ADDR_HI_PCICFG,0);
    pciRead(PCIIF_CS1_BASE_ADDR_LOW_PCICFG,0);
    pciRead(PCIIF_CS1_BASE_ADDR_HI_PCICFG,0);
    pciRead(PCIIF_INTERNAL_MEM_MAPPED_BASE_ADDR_LOW_PCICFG,0);
    pciRead(PCIIF_INTERNAL_MEM_MAPPED_BASE_ADDR_HI_PCICFG,0);
    pciRead(PCIIF_SUBSYSTEM_DEVICE_AND_VENDOR_ID_PCICFG,0);
    pciRead(PCIIF_EXPANSION_ROM_BASE_ADDR_PCICFG,0);
    pciRead(PCIIF_CAPABILITY_LIST_PTR_PCICFG,0);
    pciRead(PCIIF_INTERRUPT_PIN_AND_LINE_PCICFG,0);
    pciRead(PCIIF_POWER_MGMT_PCICFG,0);
    pciRead(PCIIF_POWER_MGMT_CTRL_AND_STATUS_PCICFG,0);
    pciRead(PCIIF_VPD_ADDR_PCICFG,0);
    pciRead(PCIIF_VPD_DATA_PCICFG,0);
    pciRead(PCIIF_MSI_MSG_CTRL_PCICFG,0);
    pciRead(PCIIF_MSI_MSG_ADDR_PCICFG,0);
    pciRead(PCIIF_MSI_MSG_UPPER_ADDR_PCICFG,0);
    pciRead(PCIIF_MSG_DATA_PCICFG,0);
    pciRead(PCIIF_PCI_X_CMD_PCICFG,0);
    pciRead(PCIIF_PCI_X_STATUS_PCICFG,0);
    pciRead(PCIIF_COMPACTPCI_HOTSWAP_PCICFG,0);
    printf("\n\r");

    printf("Function 1:                                         Bus 0       Bus 1\n\r");
    pciRead(PCIIF_CS2_BASE_ADDR_LOW_PCICFG,1);
    pciRead(PCIIF_CS2_BASE_ADDR_HI_PCICFG,1);
    pciRead(PCIIF_CS3_BASE_ADDR_LOW_PCICFG,1);
    pciRead(PCIIF_CS3_BASE_ADDR_HI_PCICFG,1);
    pciRead(PCIIF_INTEGRATED_SRAM_BASE_ADDR_LOW_PCICFG,1);
    pciRead(PCIIF_INTEGRATED_SRAM_BASE_ADDR_HI_PCICFG,1);
    printf("\n\r");

    printf("Function 2:                                         Bus 0       Bus 1\n\r");
    pciRead(PCIIF_DEVCS0_BASE_ADDR_LOW_PCICFG,2); 
    pciRead(PCIIF_DEVCS0_BASE_ADDR_HI_PCICFG,2);
    pciRead(PCIIF_DEVCS1_BASE_ADDR_LOW_PCICFG,2);
    pciRead(PCIIF_DEVCS1_BASE_ADDR_HI_PCICFG,2);
    pciRead(PCIIF_DEVCS2_BASE_ADDR_LOW_PCICFG,2);
    pciRead(PCIIF_DEVCS2_BASE_ADDR_HI_PCICFG,2);
    printf("\n\r");

    printf("Function 3:                                         Bus 0       Bus 1\n\r");
    pciRead(PCIIF_DEVCS3_BASE_ADDR_LOW_PCICFG,3); 
    pciRead(PCIIF_DEVCS3_BASE_ADDR_HI_PCICFG,3);
    pciRead(PCIIF_BOOTCS_BASE_ADDR_LOW_PCICFG,3);
    pciRead(PCIIF_BOOTCS_BASE_ADDR_HI_PCICFG,3);
    pciRead(PCIIF_CPU_BASE_ADDR_LOW_PCICFG,3);
    printf("\n\r");
 
    printf("Function 4:                                         Bus 0       Bus 1\n\r");
    pciRead(PCIIF_P2P_IO_BASE_ADDR_PCICFG,4);
    pciRead(PCIIF_P2P_MEM0_BASE_ADDR_LOW_PCICFG,4);
    pciRead(PCIIF_P2P_MEM0_BASE_ADDR_HI_PCICFG,4);
    pciRead(PCIIF_P2P_MEM1_BASE_ADDR_LOW_PCICFG,4);
    pciRead(PCIIF_P2P_MEM1_BASE_ADDR_HI_PCICFG,4);
    pciRead(PCIIF_CPU_BASE_ADDR_HI_PCICFG,4);
    pciRead(PCIIF_INTERNAL_IO_MAPPED_BASE_ADDR_PCICFG,4);
    printf("\n\r"); 
    }
