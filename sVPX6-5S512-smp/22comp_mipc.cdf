/* 22comp_mipc.cdf - configuration for MCB/MSD/MIPC */

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
01a,24feb08,syt  adapted from fsl_p4080_ds version 01q
*/

Folder FOLDER_MIPC {
    _CHILDREN   FOLDER_MULTIOS
}

Component INCLUDE_MIPC_UNSUPPORTED {
    _CHILDREN   FOLDER_NOT_VISIBLE
}

Parameter MIPC_SM_SYSTEM_POOL_BASE {
    NAME        Base address of shared memory pool used by MCB (virtual)
    SYNOPSIS    This is the virtual address for MIPC SM.  Configure the \
                physical address (MIPC_SM_SYSTEM_POOL_BASE_PHYS) instead.
    DEFAULT     (INCLUDE_VIRTUAL_SM)::((VIRTUAL_SM_BASE - VIRTUAL_SM_BASE_PHYS + MIPC_SM_SYSTEM_POOL_BASE_PHYS)) \
                (MIPC_SM_SYSTEM_POOL_BASE_PHYS)
}

Parameter MIPC_SM_SYSTEM_POOL_BASE_PHYS {
    NAME        Base address of shared memory pool used by MCB
    SYNOPSIS    The base address on the fsl_p5020_ds is at 0x40010000. The \
                shared memory extends up to 0x40100000. MCB, SM and DSHM must share that \
                space if included. Care must be taken so that it is not overflown, since this \
                will corrupt kernel data and/or text.
    _CFG_PARAMS INCLUDE_MIPC_SM
    DEFAULT     0x40010000
}

Parameter MIPC_SM_SYSTEM_POOL_SIZE {
    DEFAULT     0x80000
}

Parameter MIPC_SM_NODE_IRQ {
    NAME        Interrupt request line
    SYNOPSIS    Interrupt request line.
    TYPE        INT
    DEFAULT     3
}

Parameter MIPC_SM_NODES {
    NAME        Maximum nodes per bus
    SYNOPSIS    Specifies the maximum number of nodes a bus can support, unless overridden by the bus configuration string.
    TYPE        UINT
    DEFAULT     2
}

Parameter MSD_NUM_DEVS {
    DEFAULT     (INCLUDE_AMP_CPU_00)::(3) \
                (1)
}

Parameter MSD_CFG_STR {
    DEFAULT     (INCLUDE_AMP_CPU_00)::("#auto=y bus=main") \
                (INCLUDE_AMP_CPU_01)::("#dev=/ttyMsd0 node=0 instance=0 console=y bus=main") \
                "#dev=/ttyMsd0 node=0 instance=0 console=n bus=main"
}

