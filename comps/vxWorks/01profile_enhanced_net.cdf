/* 01profile_enhanced_net.cdf - VxWorks Enhanced Network Profile */

/*
 * Copyright (c) 2004-2007, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02a,07dec11,ggz  Add telnet server. Defect WIND00195031
01z,12nov10,mze  _WRS_VX_SMP is now obsolete replaced with _WRS_CONFIG_SMP
01y,06oct10,gls  added INCLUDE_EDR_POLICY_HOOKS (WIND00234560)
01x,30dec09,jpb  Removed INCLUDE_TASK_VARS from LP64 build.
01w,04aug09,jpb  Defect# 161788.  Removed INCLUDE_SET.
01v,10jan08,jbl  fix DHCPC option names
01u,04oct07,mze  fix for 104829
01t,30aug07,kk   fixed #ifndef within listing which causes listings after to
                 not get pulled in
01s,16aug07,pch  remove INCLUDE_TASK_VARS from SMP build
01r,03jul07,rlp  Removed INCLUDE_BUF_MGR component.
01q,22nov06,kch  Removed coreip telnet server.
01p,18sep06,tkf  Remove INCLUDE_NET_BOOT_CONFIG, INCLUDE_NET_INIT and
                 INCLUDE_BPF (WIND00065689).
01o,10sep06,tkf  Remove INCLUDE_ROUTING_SOCKET, INCLUDE_RAWV4.
01n,08sep06,tkf  Remove INCLUDE_NETSTAT_IPV4, INCLUDE_NETSTAT_ROUTE
                 INCLUDE_NETSTAT_TCP, INCLUDE_NETSTAT_UDP.
01m,06sep06,tkf  Remove INCLUDE_DOMAIN_INIT, INCLUDE_ICMPV4.
01l,16jun06,zl   added INCLUDE_MEM_MGR_INFO.
01k,30mar06,mwv  remove improper DHCP components (SPR#117733)
01j,09jan06,pee  added BSP_DEFAULT
01i,06aug05,jln  added INCLUDE_VX_NATIVE_SCHEDULER
01h,01aug05,yvp  Added newly created components (sem, msgQ & wd create/delete).
01g,09jul05,yvp  Added newly created components.
01f,23mar05,vvv  removed obsolete INCLUDE_NET_GETOPT
01e,08mar05,dlk  Modify SYNOPSIS, remove obsolete INCLUDE_NET_APPUTIL.
01d,16nov04,tam  removed BSP specific components
01c,11oct04,jn   Change name of INCLUDE_ABS_SYMBOLS to INCLUDE_OFFSET_SYMBOLS
01b,01oct04,fle  turned it into a Profile
                 + renamed INCLUDE_RTP_KERNEL into INCLUDE_BASE_KERNEL
01a,16sep04,pee  written
*/

/*
 * ***************************************************************
 *  WARNING WARNING WARNING WARNING
 * ***************************************************************
 *
 * When updating the COMPONENTS listing in this profile,
 * please note there are 2 listings: one for UP and one for SMP.
 * If your new component applies to both SMP and UP, please
 * update both lists.
 */

Profile PROFILE_ENHANCED_NET {
    NAME	Enhanced Network Configuration Profile
    SYNOPSIS    This profile adds to the standard profile certain components \
		appropriate for typical managed network client host devices. \
		The primary components added are the DHCP client and DNS \
		resolver, the Telnet server (shell not included), and \
		several command-line-style configuration utilities.
    PROFILES    BSP_DEFAULT
#if (defined _WRS_CONFIG_SMP) || (defined _WRS_CONFIG_LP64)
    COMPONENTS	INCLUDE_ANSI_ASSERT \
		INCLUDE_ANSI_CTYPE \
		INCLUDE_ANSI_LOCALE \
		INCLUDE_ANSI_MATH \
		INCLUDE_ANSI_STDIO \
		INCLUDE_ANSI_STDIO_EXTRA \
		INCLUDE_ANSI_STDLIB \
		INCLUDE_ANSI_STRING \
		INCLUDE_ANSI_TIME \
		INCLUDE_APPL_LOG_UTIL \
		INCLUDE_ARP_API \
		INCLUDE_BOOT_LINE_INIT \
		INCLUDE_BSD_SOCKET \
		INCLUDE_BSP_MACROS \
		INCLUDE_CACHE_ENABLE \
		INCLUDE_CACHE_SUPPORT \
		INCLUDE_CLASS_LIB \
		INCLUDE_CTORS_DTORS \
		INCLUDE_DEFERRED_INTERRUPT_ENABLE \
		INCLUDE_IPDHCPC \
		INCLUDE_DIAB_INTRINSICS \
		INCLUDE_DNS_RESOLVER \
		INCLUDE_EDR_POLICY_HOOKS \
		INCLUDE_EDR_STUB \
		INCLUDE_END \
		INCLUDE_ENV_VARS \
		INCLUDE_ETHERNET \
		INCLUDE_EXC_HANDLING \
		INCLUDE_EXC_SHOW \
		INCLUDE_EXC_TASK \
		INCLUDE_FLOATING_POINT \
		INCLUDE_FORMATTED_IO \
		INCLUDE_FTP \
		INCLUDE_GETADDRINFO \
		INCLUDE_GETIFADDRS \
		INCLUDE_GETNAMEINFO \
		INCLUDE_GETNETBYNAME \
		INCLUDE_GETSERVBYNAME \
		INCLUDE_GNU_INTRINSICS \
		INCLUDE_GTF \
		INCLUDE_GTF_TIMER_START \
		INCLUDE_HASH \
		INCLUDE_HOOKS \
		INCLUDE_HOST_TBL \
		INCLUDE_ISR_OBJECTS \
		INCLUDE_IFCONFIG \
		INCLUDE_INETLIB \
		INCLUDE_IO_SYSTEM \
		INCLUDE_IPATTACH \
		INCLUDE_IPV4 \
		INCLUDE_JOB_TASK \
		INCLUDE_KERNEL \
		INCLUDE_VX_NATIVE_SCHEDULER \
		INCLUDE_KERN_RANDOM \
		INCLUDE_LINKBUFPOOL \
		INCLUDE_LOGGING \
		INCLUDE_MEMORY_CONFIG \
		INCLUDE_MEM_MGR_BASIC \
		INCLUDE_MEM_MGR_FULL \
		INCLUDE_MEM_MGR_INFO \
		INCLUDE_MIB2_IF \
		INCLUDE_MSG_Q \
		INCLUDE_MSG_Q_CREATE_DELETE \
		INCLUDE_MSG_Q_INFO \
		INCLUDE_MSG_Q_SHOW \
		INCLUDE_MUX \
		INCLUDE_NETBUFLIB \
		INCLUDE_NETBUFPOOL \
		INCLUDE_NETMASK_GET \
		INCLUDE_NETSTAT \
		INCLUDE_NETSTAT_ICMPV4 \
		INCLUDE_NETWORK \
		INCLUDE_NET_BOOT \
		INCLUDE_NET_DAEMON \
		INCLUDE_NET_DRV \
		INCLUDE_NET_FUNCBIND \
		INCLUDE_NET_HOST_SETUP \
		INCLUDE_NET_MD5 \
		INCLUDE_NET_POOL \
		INCLUDE_NET_REM_IO \
		INCLUDE_NET_SYSCTL \
		INCLUDE_OBJ_LIB \
		INCLUDE_OFFSET_SYMBOLS \
		INCLUDE_PIPES \
		INCLUDE_POOL \
		INCLUDE_POSIX_CLOCKS \
		INCLUDE_POSIX_DIRLIB \
		INCLUDE_REBOOT_HOOKS \
		INCLUDE_REMLIB \
		INCLUDE_RNG_BUF \
		INCLUDE_ROUTE \
		INCLUDE_ROUTECMD \
		INCLUDE_ROUTE_STORAGE \
		INCLUDE_BASE_KERNEL \
		INCLUDE_SECURITY \
		INCLUDE_SELECT \
		INCLUDE_SELECT_SUPPORT \
		INCLUDE_SEM_BINARY \
		INCLUDE_SEM_COUNTING \
		INCLUDE_SEM_MUTEX \
		INCLUDE_SEM_LIB \
		INCLUDE_SEM_DELETE \
		INCLUDE_SEM_BINARY_CREATE \
		INCLUDE_SEM_COUNTING_CREATE \
		INCLUDE_SEM_MUTEX_CREATE \
		INCLUDE_SEM_SHOW \
		INCLUDE_SIGNALS \
		INCLUDE_SIO \
		INCLUDE_SOCKLIB \
		INCLUDE_STDIO \
		INCLUDE_STRICMP \
		INCLUDE_STRNICMP \
		INCLUDE_SYM_TBL \
		INCLUDE_SYSCLK_INIT \
		INCLUDE_SYSCTL \
		INCLUDE_SYSHW_INIT \
		INCLUDE_SYS_START \
		INCLUDE_TASK_CREATE_DELETE \
		INCLUDE_TASK_HOOKS \
		INCLUDE_TASK_RESTART \
		INCLUDE_TCPV4 \
                INCLUDE_IPTELNETS \
		INCLUDE_TFTP_CLIENT \
		INCLUDE_TIMESTAMP \
		INCLUDE_TIMEX \
		INCLUDE_TTY_DEV \
		INCLUDE_TYLIB \
		INCLUDE_UDPV4 \
		INCLUDE_USER_APPL \
		INCLUDE_VXEVENTS \
		INCLUDE_WATCHDOGS \
		INCLUDE_WATCHDOGS_CREATE_DELETE \
		INCLUDE_WDB \
		INCLUDE_WDB_BANNER \
		INCLUDE_WDB_BP \
		INCLUDE_WDB_CTXT \
		INCLUDE_WDB_DIRECT_CALL \
		INCLUDE_WDB_EVENTPOINTS \
		INCLUDE_WDB_EVENTS \
		INCLUDE_WDB_EXC_NOTIFY \
		INCLUDE_WDB_EXIT_NOTIFY \
		INCLUDE_WDB_FUNC_CALL \
		INCLUDE_WDB_GOPHER \
		INCLUDE_WDB_MEM \
		INCLUDE_WDB_POST_KERNEL_INIT \
		INCLUDE_WDB_REG \
		INCLUDE_WDB_START_NOTIFY \
		INCLUDE_WDB_SYS \
		INCLUDE_WDB_TASK \
		INCLUDE_WDB_TASK_BP \
		INCLUDE_WDB_TASK_HOOKS \
		INCLUDE_WDB_USER_EVENT \
		INCLUDE_WDB_VIO \
		INCLUDE_WDB_VIO_LIB \
		INCLUDE_XDR
#else /* !_WRS_CONFIG_SMP && ! _WRS_CONFIG_LP64 */
    COMPONENTS	INCLUDE_ANSI_ASSERT \
		INCLUDE_ANSI_CTYPE \
		INCLUDE_ANSI_LOCALE \
		INCLUDE_ANSI_MATH \
		INCLUDE_ANSI_STDIO \
		INCLUDE_ANSI_STDIO_EXTRA \
		INCLUDE_ANSI_STDLIB \
		INCLUDE_ANSI_STRING \
		INCLUDE_ANSI_TIME \
		INCLUDE_APPL_LOG_UTIL \
		INCLUDE_ARP_API \
		INCLUDE_BOOT_LINE_INIT \
		INCLUDE_BSD_SOCKET \
		INCLUDE_BSP_MACROS \
		INCLUDE_CACHE_ENABLE \
		INCLUDE_CACHE_SUPPORT \
		INCLUDE_CLASS_LIB \
		INCLUDE_CTORS_DTORS \
		INCLUDE_DEFERRED_INTERRUPT_ENABLE \
		INCLUDE_IPDHCPC \
		INCLUDE_DIAB_INTRINSICS \
		INCLUDE_DNS_RESOLVER \
		INCLUDE_EDR_POLICY_HOOKS \
		INCLUDE_EDR_STUB \
		INCLUDE_END \
		INCLUDE_ENV_VARS \
		INCLUDE_ETHERNET \
		INCLUDE_EXC_HANDLING \
		INCLUDE_EXC_SHOW \
		INCLUDE_EXC_TASK \
		INCLUDE_FLOATING_POINT \
		INCLUDE_FORMATTED_IO \
		INCLUDE_FTP \
		INCLUDE_GETADDRINFO \
		INCLUDE_GETIFADDRS \
		INCLUDE_GETNAMEINFO \
		INCLUDE_GETNETBYNAME \
		INCLUDE_GETSERVBYNAME \
		INCLUDE_GNU_INTRINSICS \
		INCLUDE_GTF \
		INCLUDE_GTF_TIMER_START \
		INCLUDE_HASH \
		INCLUDE_HOOKS \
		INCLUDE_HOST_TBL \
		INCLUDE_ISR_OBJECTS \
		INCLUDE_IFCONFIG \
		INCLUDE_INETLIB \
		INCLUDE_IO_SYSTEM \
		INCLUDE_IPATTACH \
		INCLUDE_IPV4 \
		INCLUDE_JOB_TASK \
		INCLUDE_KERNEL \
		INCLUDE_VX_NATIVE_SCHEDULER \
		INCLUDE_KERN_RANDOM \
		INCLUDE_LINKBUFPOOL \
		INCLUDE_LOGGING \
		INCLUDE_MEMORY_CONFIG \
		INCLUDE_MEM_MGR_BASIC \
		INCLUDE_MEM_MGR_FULL \
		INCLUDE_MEM_MGR_INFO \
		INCLUDE_MIB2_IF \
		INCLUDE_MSG_Q \
		INCLUDE_MSG_Q_CREATE_DELETE \
		INCLUDE_MSG_Q_INFO \
		INCLUDE_MSG_Q_SHOW \
		INCLUDE_MUX \
		INCLUDE_NETBUFLIB \
		INCLUDE_NETBUFPOOL \
		INCLUDE_NETMASK_GET \
		INCLUDE_NETSTAT \
		INCLUDE_NETSTAT_ICMPV4 \
		INCLUDE_NETWORK \
		INCLUDE_NET_BOOT \
		INCLUDE_NET_DAEMON \
		INCLUDE_NET_DRV \
		INCLUDE_NET_FUNCBIND \
		INCLUDE_NET_HOST_SETUP \
		INCLUDE_NET_MD5 \
		INCLUDE_NET_POOL \
		INCLUDE_NET_REM_IO \
		INCLUDE_NET_SYSCTL \
		INCLUDE_OBJ_LIB \
		INCLUDE_OFFSET_SYMBOLS \
		INCLUDE_PIPES \
		INCLUDE_POOL \
		INCLUDE_POSIX_CLOCKS \
		INCLUDE_POSIX_DIRLIB \
		INCLUDE_REBOOT_HOOKS \
		INCLUDE_REMLIB \
		INCLUDE_RNG_BUF \
		INCLUDE_ROUTE \
		INCLUDE_ROUTECMD \
		INCLUDE_ROUTE_STORAGE \
		INCLUDE_BASE_KERNEL \
		INCLUDE_SECURITY \
		INCLUDE_SELECT \
		INCLUDE_SELECT_SUPPORT \
		INCLUDE_SEM_BINARY \
		INCLUDE_SEM_COUNTING \
		INCLUDE_SEM_MUTEX \
		INCLUDE_SEM_LIB \
		INCLUDE_SEM_DELETE \
		INCLUDE_SEM_BINARY_CREATE \
		INCLUDE_SEM_COUNTING_CREATE \
		INCLUDE_SEM_MUTEX_CREATE \
		INCLUDE_SEM_SHOW \
		INCLUDE_SIGNALS \
		INCLUDE_SIO \
		INCLUDE_SOCKLIB \
		INCLUDE_STDIO \
		INCLUDE_STRICMP \
		INCLUDE_STRNICMP \
		INCLUDE_SYM_TBL \
		INCLUDE_SYSCLK_INIT \
		INCLUDE_SYSCTL \
		INCLUDE_SYSHW_INIT \
		INCLUDE_SYS_START \
		INCLUDE_TASK_CREATE_DELETE \
		INCLUDE_TASK_HOOKS \
		INCLUDE_TASK_RESTART \
		INCLUDE_TASK_VARS \
		INCLUDE_TCPV4 \
                INCLUDE_IPTELNETS \
		INCLUDE_TFTP_CLIENT \
		INCLUDE_TIMESTAMP \
		INCLUDE_TIMEX \
		INCLUDE_TTY_DEV \
		INCLUDE_TYLIB \
		INCLUDE_UDPV4 \
		INCLUDE_USER_APPL \
		INCLUDE_VXEVENTS \
		INCLUDE_WATCHDOGS \
		INCLUDE_WATCHDOGS_CREATE_DELETE \
		INCLUDE_WDB \
		INCLUDE_WDB_BANNER \
		INCLUDE_WDB_BP \
		INCLUDE_WDB_CTXT \
		INCLUDE_WDB_DIRECT_CALL \
		INCLUDE_WDB_EVENTPOINTS \
		INCLUDE_WDB_EVENTS \
		INCLUDE_WDB_EXC_NOTIFY \
		INCLUDE_WDB_EXIT_NOTIFY \
		INCLUDE_WDB_FUNC_CALL \
		INCLUDE_WDB_GOPHER \
		INCLUDE_WDB_MEM \
		INCLUDE_WDB_POST_KERNEL_INIT \
		INCLUDE_WDB_REG \
		INCLUDE_WDB_START_NOTIFY \
		INCLUDE_WDB_SYS \
		INCLUDE_WDB_TASK \
		INCLUDE_WDB_TASK_BP \
		INCLUDE_WDB_TASK_HOOKS \
		INCLUDE_WDB_USER_EVENT \
		INCLUDE_WDB_VIO \
		INCLUDE_WDB_VIO_LIB \
		INCLUDE_XDR
#endif /* _WRS_CONFIG_SMP || _WRS_CONFIG_LP64 */
    _CHILDREN	FOLDER_NOT_VISIBLE
}
