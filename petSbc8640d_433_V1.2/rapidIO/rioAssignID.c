/* sysRapidIOEnum.c - Initialization,Enum,Configration Routting Pathes .*/

/*
 * Copyright (c) 2012- Prophet Electronic,Inc.
 * 
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Prophet license agreement. 
 */

/*
modification history
-----------------------
12/09/2012,sjy Created the file.
 */

/*
 * DESCRIPTION
 * Initialize the RapidIO Switch .
 * 
 */

/* includes*/

#include<vxworks.h>
#include "rioConfig.h"
#include "sysRapidIO.h"
#include "rioPrivate.h"
#include "rioExplore.h"



/*****************************************************************************
*
* assignEpID - second stage device connection
* This function assign the RapidIO endpoint ID .
* mode: 0/1 0:the ID is assigned to a ordered number. 1:the ID is assigned with
* slot number,id = slotNum * 4 + cpuID 
*
* RETURNS: N/A
*
*/

STATUS assignEpID()
{
	UINT32 switchIndex;
	RIO_ID destId;
	struct switch_desc * tempSwPtr;
	UINT8 * routeArray;
	UINT32 regVal;
	UINT8 connPort;
	int i = 0;
	UINT32 portIndex;
	RIO_ID domain_id = 0x0;
	
	ASSIGN_ID_DBG_LOG("enter assignEpID,\n",1,2,3,4,5,6);
	
	for(switchIndex=1; switchIndex<detectedSwitchNum; switchIndex++)
	{
		/* ����switchͨ·�е�·��·�ɱ� */
		tempSwPtr = switchArray[switchIndex];
		routeArray = tempSwPtr->routePortsArray;
		ASSIGN_ID_DBG_LOG("In assignEpID switch index %d\n",switchIndex,2,3,4,5,6);
		destId = DEF_ID;
		for(i=0; i<tempSwPtr->hopCount; i++)
		{
			CONFIG_READ(DEF_ID,i,SPICAR,&regVal);
			connPort = regVal & 0xFF;
			ROUTE_SET_P_TO_P(DEF_ID,i,&destId,routeArray++,&connPort);
		}

		ASSIGN_ID_DBG_LOG("In assignEpID assign id\n",1,2,3,4,5,6);
		CONFIG_READ(DEF_ID,tempSwPtr->hopCount,SPICAR,&regVal);

		connPort = regVal & 0xFF;

		/* debug */
		//DEBUG_LOG("regVal is %d,connect port is %d\n",regVal,connPort,3,4,5,6);
		/* debug */
		/* Set all Maintenance respones packet route to connPort*/
		ROUTE_SET_P_FOR_ALL(DEF_ID,tempSwPtr->hopCount,&hostCpuID,&connPort); 
		for(portIndex=0; portIndex< tempSwPtr->portNum; portIndex++)
		{
			/* ����˿ں�Ϊά��������˿ڣ��򲻼��ö˿�*/
			if ((portIndex == connPort)||(tempSwPtr->device_IDs[portIndex].type != DEVICE)) 
			{
				//ASSIGN_ID_DBG_LOG("This is the port which connected to the upstream device!\n",1,2,3,4,5,6);
				continue;
			}
			ASSIGN_ID_DBG_LOG("89 In assignEpID assign id\n",1,2,3,4,5,6);
			/* ���ô�Host Port���������ݰ���Port i��·�ɱ��� */
			destId = DEF_ID;
			ROUTE_SET_P_TO_P(DEF_ID,tempSwPtr->hopCount,&destId,&portIndex,&connPort); 
#ifdef RIO_ID_16
			regVal = tempSwPtr->device_IDs[portIndex].ID;
#else
			regVal = tempSwPtr->device_IDs[portIndex].ID << 16;
#endif // RIO_ID_16
			
			/* set the rapidIO switch domain*/
			if((((tempSwPtr->device_IDs[portIndex].ID)&0xff00) != 0x0)&&(((tempSwPtr->device_IDs[portIndex].ID)&0xff00) != 0xdd00))
			{
				domain_id = (tempSwPtr->device_IDs[portIndex].ID&0xff00)>>8;
				CONFIG_WRITE(DEF_ID,tempSwPtr->hopCount,RDR,&domain_id);
			}

			destId = tempSwPtr->device_IDs[portIndex].oldID;
			CONFIG_WRITE(destId,tempSwPtr->hopCount + 1,BDIDCSR,&regVal);
			tempSwPtr->device_IDs[portIndex].oldID = tempSwPtr->device_IDs[portIndex].ID;
		}

	}
	ASSIGN_ID_DBG_LOG("exit assignEpID,\n",1,2,3,4,5,6);
	return OK;
}
