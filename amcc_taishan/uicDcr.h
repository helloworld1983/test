/* uicDcr.h - IBM quad UIC DCR access assembly routines */

/*
********************************************************************************
   This source and object code has been made available to you by IBM on an
   AS-IS basis.

   IT IS PROVIDED WITHOUT WARRANTY OF ANY KIND, INCLUDING THE WARRANTIES OF
   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE OR OF NONINFRINGEMENT
   OF THIRD PARTY RIGHTS.  IN NO EVENT SHALL IBM OR ITS LICENSORS BE LIABLE
   FOR INCIDENTAL, CONSEQUENTIAL OR PUNITIVE DAMAGES.  IBM'S OR ITS LICENSOR'S
   DAMAGES FOR ANY CAUSE OF ACTION, WHETHER IN CONTRACT OR IN TORT, AT LAW OR
   AT EQUITY, SHALL BE LIMITED TO A MAXIMUM OF $1,000 PER LICENSE.  No license
   under IBM patents or patent applications is to be implied by the copyright
   license.

   Any user of this software should understand that neither IBM nor its
   licensors will be responsible for any consequences resulting from the use
   of this software.

   Any person who transfers this source code or any derivative work must
   include the IBM copyright notice, this paragraph, and the preceding two
   paragraphs in the transferred software.

   Any person who transfers this object code or any derivative work must
   include the IBM copyright notice in the transferred software.

   COPYRIGHT   I B M   CORPORATION 2000
   LICENSED MATERIAL  -  PROGRAM PROPERTY OF  I B M"

********************************************************************************
\NOMANUAL
*/

/* Copyright 1984-2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01e,12nov04,dr   Sharing with bamboo
01d,29sep04,mdo  Documentation fixes for apigen
01c,15aug03,jtp  Formal code inspection changes: documentation
01b,12jun02,pch  SPR 74987: C++
01a,10dec02,saw  port to 440gx from 440gp.  Added UIC2 and UICB support
*/

/*
This file contains the definitions of the UIC interrupt controller DCR
register access functions.  This version of the UIC interrupt controller
contains four UIC cores: UIC0, UIC1, UIC2 and UICB.
*/

#ifndef INCuicDcrh
#define INCuicDcrh

#ifdef __cplusplus
    extern "C" {
#endif

/*
 * Universal Interrupt Controller register definitions. Each is a separate
 * DCR register.
 */

#define UIC0_SR        (UIC0_DCR_BASE+0x0)  /* UIC status                  */
#define UIC0_ER        (UIC0_DCR_BASE+0x2)  /* UIC enable                  */
#define UIC0_CR        (UIC0_DCR_BASE+0x3)  /* UIC critical                */
#define UIC0_PR        (UIC0_DCR_BASE+0x4)  /* UIC polarity                */
#define UIC0_TR        (UIC0_DCR_BASE+0x5)  /* UIC triggering              */
#define UIC0_MSR       (UIC0_DCR_BASE+0x6)  /* UIC masked status           */
#define UIC0_VR        (UIC0_DCR_BASE+0x7)  /* UIC vector                  */
#define UIC0_VCR       (UIC0_DCR_BASE+0x8)  /* UIC vector configuration    */

#define UIC1_SR        (UIC1_DCR_BASE+0x0)  /* UIC status                  */
#define UIC1_ER        (UIC1_DCR_BASE+0x2)  /* UIC enable                  */
#define UIC1_CR        (UIC1_DCR_BASE+0x3)  /* UIC critical                */
#define UIC1_PR        (UIC1_DCR_BASE+0x4)  /* UIC polarity                */
#define UIC1_TR        (UIC1_DCR_BASE+0x5)  /* UIC triggering              */
#define UIC1_MSR       (UIC1_DCR_BASE+0x6)  /* UIC masked status           */
#define UIC1_VR        (UIC1_DCR_BASE+0x7)  /* UIC vector                  */
#define UIC1_VCR       (UIC1_DCR_BASE+0x8)  /* UIC vector configuration    */

#ifndef PPC440EP

#define UIC2_SR        (UIC2_DCR_BASE+0x0)  /* UIC status                  */
#define UIC2_ER        (UIC2_DCR_BASE+0x2)  /* UIC enable                  */
#define UIC2_CR        (UIC2_DCR_BASE+0x3)  /* UIC critical                */
#define UIC2_PR        (UIC2_DCR_BASE+0x4)  /* UIC polarity                */
#define UIC2_TR        (UIC2_DCR_BASE+0x5)  /* UIC triggering              */
#define UIC2_MSR       (UIC2_DCR_BASE+0x6)  /* UIC masked status           */
#define UIC2_VR        (UIC2_DCR_BASE+0x7)  /* UIC vector                  */
#define UIC2_VCR       (UIC2_DCR_BASE+0x8)  /* UIC vector configuration    */

#define UICB_SR        (UICB_DCR_BASE+0x0)  /* UIC status                  */
#define UICB_ER        (UICB_DCR_BASE+0x2)  /* UIC enable                  */
#define UICB_CR        (UICB_DCR_BASE+0x3)  /* UIC critical                */
#define UICB_PR        (UICB_DCR_BASE+0x4)  /* UIC polarity                */
#define UICB_TR        (UICB_DCR_BASE+0x5)  /* UIC triggering              */
#define UICB_MSR       (UICB_DCR_BASE+0x6)  /* UIC masked status           */
#define UICB_VR        (UICB_DCR_BASE+0x7)  /* UIC vector                  */
#define UICB_VCR       (UICB_DCR_BASE+0x8)  /* UIC vector configuration    */

#endif /* PPC440EP */

#ifndef _ASMLANGUAGE

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
    }
#endif

#endif  /* INCuicDcrh */