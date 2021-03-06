# Makefile - Makefile for Wind River SBC8641D board
#
# Copyright (c) 2008 Wind River Systems, Inc.
# 
# The right to copy, distribute, modify or otherwise make use
# of this software may be licensed only pursuant to the terms
# of an applicable Wind River license agreement.
#
# modification history
# --------------------
# 01d,02oct08,kab  Remove VXBUILD directive
# 01c,04sep08,dtr  Remove need for -amp in proj facility.
# 01b,25aug08,dtr  Add VXBUILD=AMP default for release builds.
# 01a,21aug08,dtr  Modified from wrSbc8641/Makefile/01b.
#
# DESCRIPTION
# This file contains rules for building VxWorks for the template.
#
# INCLUDES
#     makeTarget
#*/

CPU              = PPC32
TOOL             = diab
CPU_VARIANT      = _ppc604_745x
TGT_DIR = $(WIND_BASE)/target

include $(TGT_DIR)/h/make/defs.bsp
#include $(TGT_DIR)/h/make/make.$(CPU)$(TOOL)
#include $(TGT_DIR)/h/make/defs.$(WIND_HOST_TYPE)

## Only redefine make definitions below this point, or your definitions will
## be overwritten by the makefile stubs above.  All the board specific
## defines are listed below, but it is preferable to use the BSP that
## matches the hardware.  Runtime checks for some board differences are not
## possible, so the kernel should be configured to the specific board.

TARGET_DIR      = wrSbc8641d_AMP
VENDOR          = Wind River
VXBUILD         = AMP

EXTRA_DEFINE   += -D_WRS_VX_AMP

##########################################################################
BOARD           = Wind River SBC8641D

##########################################################################
#
#
# The constants ROM_TEXT_ADRS, ROM_SIZE, and RAM_HIGH_ADRS are defined
# in config.h and Makefile.
# All definitions for these constants must be identical.
# Specify values in hexadecimal, without a leading 0x.
#

LOCAL_MEM_LOCAL_ADRS  =  0x0
ROM_TEXT_ADRS   = fff00100 # ROM cold entry address
ROM_WARM_ADRS   = fff0010C # ROM warm entry address
ROM_SIZE        = 00100000 # number of bytes of ROM space (512K)
RAM_LOW_ADRS    = 00100000 # RAM text/data address for vxWorks
RAM_HIGH_ADRS   = 00e00000 # RAM text/data address for bootrom
LOCAL_MEM_SIZE  = 10000000 # 256MB memory

# ROM_LINK_ADRS defaults to ROM_TEXT_ADRS, but needs to be different
# here due to complications related to the .space 0x100 at the start
# of romInit.s. 
ROM_LINK_ADRS   = fff00000

USR_ENTRY       = usrInit

DOC_FILES	=  sysCacheLib sysLib

ADDED_CFLAGS    += -g2

RELEASE_CMD		=  bootrom bootrom.hex 

## Only redefine make definitions above this point, or the expansion
## of the makefile target dependencies may be incorrect.

include $(TGT_DIR)/h/make/rules.bsp
#include $(TGT_DIR)/h/make/rules.$(WIND_HOST_TYPE)

