#ifndef _PPC_FPGA_CANDRV_H
#define _PPC_FPGA_CANDRV_H

/********************************/

#define BSPLIB_CANDRV_DBG_ON
//#undef BSPLIB_CANDRV_DBG_ON


#ifdef BSPLIB_CANDRV_DBG_ON
#define BSP_CANDRV_DBG_MSG(X0, X1, X2, X3, X4, X5, X6) logMsg(X0, X1, X2, X3, X4, X5, X6)

#define BSPLIB_CANDRV_TEST
#undef BSPLIB_CANDRV_TEST
#ifdef BSPLIB_CANDRV_TEST
static char sprintFCAN[100];
#define BSP_CANDRV_TEST(X0, X1, X2, X3, X4, X5, X6)	{sprintf(sprintFCAN,X0, X1, X2, X3, X4, X5, X6);ns16550Pollprintf(sprintFCAN);}
#else
#define BSP_CANDRV_TEST(X0, X1, X2, X3, X4, X5, X6)

#endif



#else
#define BSP_CANDRV_DBG_MSG(X0, X1, X2, X3, X4, X5, X6)
#endif




/**********************************/
/* �������� */
#define FCAN_DRV_NAME	"ppcFpgaCan"

/* �汾 */
#ifndef VXB_VER_4_2_1
#define VXB_VER_4_2_1 0x00040201
#endif



typedef volatile unsigned int VUINT32;
typedef volatile UINT8 VUINT8;


/*******************************/
/* CAN�Ĵ�����ַ */
#define FCAN_REGBASE                  0xe1000000
#define FCAN_MEMBASE                  0xe1000100
#define FCAN_DEV_ID   0x11;

#define FCAN_STATUS_REG(CBASE)          (*(VUINT8 *)(CBASE + 0x00))
#define FCAN_BAUDRATE_REG(CBASE)        (*(VUINT8 *)(CBASE + 0x01))
#define FCAN_ID_REG(CBASE)              (*(VUINT8 *)(CBASE + 0x02))
#define FCAN_TXID_REG(CBASE)            (*(VUINT8 *)(CBASE + 0x05))
#define FCAN_TXLEN_REG(CBASE)           (*(VUINT8 *)(CBASE + 0x04))
#define FCAN_TXBUF_REG(CBASE)           ((VUINT8 *)(CBASE + 0x06))
#define FCAN_RXID_REG(CBASE)            (*(VUINT8 *)(CBASE + 0x10))
#define FCAN_RXLEN_REG(CBASE)           (*(VUINT8 *)(CBASE + 0x0f))
#define FCAN_RXBUF_REG(CBASE)           ((VUINT8 *)(CBASE + 0x11))

#define FCAN_MCU_INT_STATUS(CBASE)    (*(VUINT32 *)(CBASE + 0x80))
#define FCAN_MCU_INT_ENABLE(CBASE)      (*(VUINT32 *)(CBASE + 0x84))

#define FCAN_TO_MCU_INT_REG(CBASE)    (*(VUINT32 *)(CBASE + 0x88))


/********************************************/

typedef struct _fCanDataFrame
{
	UINT32 dataEnable;
	UINT32 ID;
	UINT32 len;
	UINT8 data[8];
}FCAN_DATA_FRAME;

typedef struct _fCanDrvCtrl
{
	SEM_ID accessSem;	/* �������ͱ����ź��� */
	UINT32 regBase;		/* �豸��ַ */
//	UINT32 unit;		/* �豸��Ԫ�� */
	UINT32 memBaseAddr;	/* CAN���߹���Ԫ��ַ */
//	UINT32 fCanClkDiv;	/* ��Ƶϵ�� */
	UINT32 deviceId;	/* �豸ID�� */
	FUNCPTR sendCallback;		/* Ӳ���������֪ͨ */
	FUNCPTR rcvCallback;		/* Ӳ���������֪ͨ */
//	fCanBufCtrl *rcvStartAddr;	/* Ӳ���������ݻ����ַ */
//	UINT32 rcvSize;				/* ��������֡�����С */
//    UINT32 rcvCount;			/* ��������֡������� */
//    UINT32 rcvScptr;			/* ��������֡�����±� */
//    UINT32 readScptr;			/* ��ȡ����֡��������±� */
//    UINT32 readPingP;			/* ��ȡ����֡�����±� */
//    UINT32 sndScptr;			/* ��������֡�����±� */
    FCAN_DATA_FRAME rcvDataFrame[2];
//    FCAN_DATA_FRAME sendDataFrame[2];
}FCAN_DRV_CTRL;





/*******************************************/
#endif 
/*******************************************/
