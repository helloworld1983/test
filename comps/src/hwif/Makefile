# Makefile - makefile target rules for target/config/comps/src/hwif
#
# Copyright (c) 2007, 2008, 2010 Wind River Systems, Inc.
#
# The right to copy, distribute, modify or otherwise make use
# of this software may be licensed only pursuant to the terms
# of an applicable Wind River license agreement. 
#
# modification history
# --------------------
# 01l,13aug10,wqi  Removed NULL_DEVICE for Windows32 and Linux, 
#                  but keep if for SunOS. (WIND00117507)
# 01l,07may10,h_k  updated copyright year for vxbUsrCmdLine.c.
# 01k,22oct08,pgh  Add NULL_DEVICE
# 01j,14oct08,pgh  Convert backslash to forward slash.
# 01i,15aug08,h_k  removed vxBus.vxb.
# 01h,10jul08,l_z  fix compiler warning
# 01g,30jun08,tor  fix WIND_BASE on windows
# 01f,27sep07,pmr  fix Solaris build
# 01e,22sep07,tor  remove dup vxbUsrCmdLine.c
# 01d,04sep07,tor  WIND0090647
# 01c,21aug07,tor  add 3rd party driver support, fix solaris shell problems
# 01b,01aug07,tor  dependency improvements
# 01a,24jul07,jrp  Added vxbDevInit and vxbDevConnect capability
#
# DESCRIPTION
#
# This is the makefile to create the vxbUsrCmdLine.c file. 
#

RM            = rm -f

TGT_DIR=$(WIND_BASE)/target

include $(TGT_DIR)/h/make/defs.library

EXTRA_INCLUDE += -I$(TGT_DIR)/src/hwif -I$(TGT_DIR)/src/hwif/h

CMD_LINE_DIR   = $(TGT_DIR)/config/all

DC_FILE_WR := $(subst \,/,$(sort $(wildcard $(WIND_BASE)/target/config/comps/src/hwif/*.dc)))
DC_FILE_3P := $(subst \,/,$(sort $(wildcard $(WIND_BASE)/target/3rdparty/*/*/*.dc)))
DC_FILE    := $(DC_FILE_WR) $(DC_FILE_3P)
DR_FILE_WR := $(subst \,/,$(sort $(wildcard $(WIND_BASE)/target/config/comps/src/hwif/*.dr)))
DR_FILE_3P := $(subst \,/,$(sort $(wildcard $(WIND_BASE)/target/3rdparty/*/*/*.dr)))
DR_FILE    := $(DR_FILE_WR) $(DR_FILE_3P)

BC_FILE    := $(subst \,/,$(sort $(wildcard $(WIND_BASE)/target/config/comps/src/hwif/*.bc)))
UC_FILE    := $(subst \,/,$(sort $(wildcard $(WIND_BASE)/target/config/comps/src/hwif/*.uc)))
BR_FILE    := $(subst \,/,$(sort $(wildcard $(WIND_BASE)/target/config/comps/src/hwif/*.br)))
UR_FILE    := $(subst \,/,$(sort $(wildcard $(WIND_BASE)/target/config/comps/src/hwif/*.ur)))
U1_FILE    := $(subst \,/,$(sort $(wildcard $(WIND_BASE)/target/config/comps/src/hwif/*.u1)))
U2_FILE    := $(subst \,/,$(sort $(wildcard $(WIND_BASE)/target/config/comps/src/hwif/*.u2)))
U3_FILE    := $(subst \,/,$(sort $(wildcard $(WIND_BASE)/target/config/comps/src/hwif/*.u3)))
U4_FILE    := $(subst \,/,$(sort $(wildcard $(WIND_BASE)/target/config/comps/src/hwif/*.u4)))
U5_FILE    := $(subst \,/,$(sort $(wildcard $(WIND_BASE)/target/config/comps/src/hwif/*.u5)))
U6_FILE    := $(subst \,/,$(sort $(wildcard $(WIND_BASE)/target/config/comps/src/hwif/*.u6)))

OS_TYPE    := $(shell uname)

VXB_USR_CMD_LINE = $(WIND_BASE)/target/config/all/vxbUsrCmdLine.c

.PHONY: vxbUsrCmdLine.c

ifeq ($(OS_TYPE),SunOS)
TEMP_NULL_DEVICE := $(NULL_DEVICE)
endif


vxbUsrCmdLine.c: $(VXB_USR_CMD_LINE)

$(VXB_USR_CMD_LINE): $(DC_FILE) $(DR_FILE) $(BC_FILE) $(UC_FILE) $(BR_FILE) $(UR_FILE) \
		$(U1_FILE) $(U2_FILE) $(U3_FILE) $(U4_FILE) $(U5_FILE) $(U6_FILE)
	@echo Building $(VXB_USR_CMD_LINE) ...
	@$(RM) $(VXB_USR_CMD_LINE)
	@echo '/* vxbUsrCmdLine.c - source file for vxBus command-line builds */' >> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '/*'	>> $(VXB_USR_CMD_LINE)
	@echo ' * Copyright (c) 2007-2010 Wind River Systems, Inc.' >> $(VXB_USR_CMD_LINE)
	@echo ' * '						>> $(VXB_USR_CMD_LINE)
	@echo ' * The right to copy, distribute, modify, or otherwise make use'     >> $(VXB_USR_CMD_LINE)
	@echo ' * of this software may be licensed only pursuant to the terms'	>> $(VXB_USR_CMD_LINE)
	@echo ' * of an applicable Wind River license agreement.'	>> $(VXB_USR_CMD_LINE)
	@echo '*/'						>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '/*' 						>> $(VXB_USR_CMD_LINE)
	@echo ' *' 						>> $(VXB_USR_CMD_LINE)
	@echo ' *                 DO NOT EDIT' 			>> $(VXB_USR_CMD_LINE)
	@echo ' *' 						>> $(VXB_USR_CMD_LINE)
	@echo ' *' 						>> $(VXB_USR_CMD_LINE)
	@echo ' * This file is automatically generated.' 	>> $(VXB_USR_CMD_LINE)
	@echo ' *' 						>> $(VXB_USR_CMD_LINE)
	@echo ' * If you have added/modified files in'   	>> $(VXB_USR_CMD_LINE)
	@echo ' * /target/config/comps/src/hwif folder,' 	>> $(VXB_USR_CMD_LINE)
	@echo ' * you need to re-create vxbUsrCmdLine.c.' 	>> $(VXB_USR_CMD_LINE)
	@echo ' * Move to /target/config/comps/src/hwif and ' 	>> $(VXB_USR_CMD_LINE)
	@echo ' * execute make vxbUsrCmdLine.c ' 		>> $(VXB_USR_CMD_LINE)
	@echo ' */' 						>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '#include <vxWorks.h>' 				>> $(VXB_USR_CMD_LINE)
	@echo '#include "config.h"' 				>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '#ifndef INCLUDE_VXBUS'				>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '/* vxBusIncluded: prevent compiler warning */'	>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo 'BOOL vxBusIncluded = FALSE;' 			>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '#else /* INCLUDE_VXBUS */' 			>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo 'BOOL vxBusIncluded = TRUE;' 			>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '#ifndef PRJ_BUILD'				>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '#include <vxBusLib.h>' 				>> $(VXB_USR_CMD_LINE)
	@echo '#include <hwif/vxbus/vxBus.h>' 			>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo 'IMPORT void plbRegister(void);'			>> $(VXB_USR_CMD_LINE)
	@echo 'IMPORT STATUS vxbDevInitInternal (void);'	>> $(VXB_USR_CMD_LINE)
	@echo 'IMPORT STATUS vxbDevConnectInternal (void);'	>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '/* vxBus Device Driver */'                       >> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@(for dcfile in $(DC_FILE) $(TEMP_NULL_DEVICE); do \
		cat $$dcfile >> $(VXB_USR_CMD_LINE) ; \
		echo '' >> $(VXB_USR_CMD_LINE) ; \
	   done)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '/* vxBus Bus Controller Drivers */'              >> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@( for bcfile in $(BC_FILE) $(TEMP_NULL_DEVICE); do \
		cat $$bcfile >> $(VXB_USR_CMD_LINE); \
		echo '' >> $(VXB_USR_CMD_LINE); \
	   done)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '/* vxBus Utility Modules */'                     >> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@( for ucfile in $(UC_FILE) $(TEMP_NULL_DEVICE); do \
		cat $$ucfile >> $(VXB_USR_CMD_LINE); \
		echo '' >> $(VXB_USR_CMD_LINE); \
	   done)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '/*******************************************' 	>> $(VXB_USR_CMD_LINE)
	@echo '*' 						>> $(VXB_USR_CMD_LINE)
	@echo '* hardWareInterFaceBusInit - initialize bus' 	>> $(VXB_USR_CMD_LINE)
	@echo '*/' 						>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo 'void hardWareInterFaceBusInit (void)' 		>> $(VXB_USR_CMD_LINE)
	@echo '    {' 						>> $(VXB_USR_CMD_LINE)
	@echo '    /* initialize bus subsystem */' 		>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '    vxbLibInit();' 				>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@( for urfile in $(UR_FILE) $(TEMP_NULL_DEVICE); do \
		cat $$urfile >> $(VXB_USR_CMD_LINE); \
		echo '' >> $(VXB_USR_CMD_LINE); \
	   done)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '    /*' 						>> $(VXB_USR_CMD_LINE)
	@echo '     * initialize processor local bus' 		>> $(VXB_USR_CMD_LINE)
	@echo '     * PLB: always included' 			>> $(VXB_USR_CMD_LINE)
	@echo '     */' 					>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '    plbRegister();' 				>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '    /* bus registration */' 			>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@( for brfile in $(BR_FILE) $(TEMP_NULL_DEVICE); do \
		cat $$brfile >> $(VXB_USR_CMD_LINE); \
		echo '' >> $(VXB_USR_CMD_LINE); \
	   done)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '    /* driver registration */' 			>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@( for drfile in $(DR_FILE) $(TEMP_NULL_DEVICE); do \
		cat $$drfile >> $(VXB_USR_CMD_LINE); \
		echo '' >> $(VXB_USR_CMD_LINE); \
	   done)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '    /* probe devices and create instances */' 	>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '    vxbInit();' 					>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '    }' 						>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '/*********************************************' 	>> $(VXB_USR_CMD_LINE)
	@echo '*' 						>> $(VXB_USR_CMD_LINE)
	@echo '* hardWareInterFaceInit - HWIF Pre-Kernel Init' 	>> $(VXB_USR_CMD_LINE)
	@echo '*/' 						>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo 'void hardWareInterFaceInit (void)' 		>> $(VXB_USR_CMD_LINE)
	@echo '    {' 						>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@( for u1file in $(U1_FILE) $(TEMP_NULL_DEVICE); do \
		cat $$u1file >> $(VXB_USR_CMD_LINE); \
		echo '' >> $(VXB_USR_CMD_LINE); \
	   done)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '    /* bus subsystem initialization */' 		>> $(VXB_USR_CMD_LINE)
	@echo '    hardWareInterFaceBusInit();' 		>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@( for u2file in $(U2_FILE) $(TEMP_NULL_DEVICE); do \
		cat $$u2file >> $(VXB_USR_CMD_LINE); \
		echo '' >> $(VXB_USR_CMD_LINE); \
	   done)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '    }' 						>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '' 						>> $(VXB_USR_CMD_LINE)
	@echo '/*********************************************'  >> $(VXB_USR_CMD_LINE)
	@echo '*'                                               >> $(VXB_USR_CMD_LINE)
	@echo '* vxbDevInit - HWIF Post-Kernel Init'            >> $(VXB_USR_CMD_LINE)
	@echo '*/'                                              >> $(VXB_USR_CMD_LINE)
	@echo ''                                                >> $(VXB_USR_CMD_LINE)
	@echo 'STATUS vxbDevInit (void)'                        >> $(VXB_USR_CMD_LINE)
	@echo '    {'                                           >> $(VXB_USR_CMD_LINE)
	@echo '    int status;'                                 >> $(VXB_USR_CMD_LINE)
	@( for u3file in $(U3_FILE) $(TEMP_NULL_DEVICE); do \
		cat $$u3file >> $(VXB_USR_CMD_LINE); \
		echo '' >> $(VXB_USR_CMD_LINE); \
	   done)
	@echo ''                                                >> $(VXB_USR_CMD_LINE)
	@echo '    /* bus Device Initialization */'             >> $(VXB_USR_CMD_LINE)
	@echo '    status = vxbDevInitInternal();'              >> $(VXB_USR_CMD_LINE)
	@echo ''                                                >> $(VXB_USR_CMD_LINE)
	@( for u4file in $(U4_FILE) $(TEMP_NULL_DEVICE); do \
		cat $$u4file >> $(VXB_USR_CMD_LINE); \
		echo '' >> $(VXB_USR_CMD_LINE); \
	   done)
	@echo '    return (status);'                            >> $(VXB_USR_CMD_LINE)
	@echo '    }'                                           >> $(VXB_USR_CMD_LINE)
	@echo ''                                                >> $(VXB_USR_CMD_LINE)
	@echo '/*********************************************'  >> $(VXB_USR_CMD_LINE)
	@echo '*'                                               >> $(VXB_USR_CMD_LINE)
	@echo '* vxbDevConnect - HWIF Post-Kernel Connection'   >> $(VXB_USR_CMD_LINE)
	@echo '*/'                                              >> $(VXB_USR_CMD_LINE)
	@echo ''                                                >> $(VXB_USR_CMD_LINE)
	@echo 'STATUS vxbDevConnect (void)'                     >> $(VXB_USR_CMD_LINE)
	@echo '    {'                                           >> $(VXB_USR_CMD_LINE)
	@echo '    int status;'                                 >> $(VXB_USR_CMD_LINE)
	@( for u5file in $(U5_FILE) $(TEMP_NULL_DEVICE); do \
		cat $$u5file >> $(VXB_USR_CMD_LINE); \
		echo '' >> $(VXB_USR_CMD_LINE); \
	   done)
	@echo ''                                                >> $(VXB_USR_CMD_LINE)
	@echo '    /* Bus Device Connection */'                 >> $(VXB_USR_CMD_LINE)
	@echo '    status = vxbDevConnectInternal();'           >> $(VXB_USR_CMD_LINE)
	@echo ''                                                >> $(VXB_USR_CMD_LINE)
	@( for u6file in $(U6_FILE) $(TEMP_NULL_DEVICE); do \
		cat $$u6file >> $(VXB_USR_CMD_LINE); \
		echo '' >> $(VXB_USR_CMD_LINE); \
	   done)
	@echo '    return (status);'                            >> $(VXB_USR_CMD_LINE)
	@echo '    }'                                           >> $(VXB_USR_CMD_LINE)
	@echo ''                                                >> $(VXB_USR_CMD_LINE)
	@echo '#endif /* PRJ_BUILD */'				>> $(VXB_USR_CMD_LINE)
	@echo '#endif /* INCLUDE_VXBUS */' 			>> $(VXB_USR_CMD_LINE)
	@echo done building $(VXB_USR_CMD_LINE)

