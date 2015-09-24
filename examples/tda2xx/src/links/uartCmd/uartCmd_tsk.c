/**
 *                                                                            
 * Copyright (c) 2015 CAMMSYS - http://www.cammsys.net/                       
 *                                                                            
 * All rights reserved.                                                       
 *                                                                            
 * @file	uartInput_tsk.c
 * @author  Raven
 * @date	Sep 21, 2015
 * @brief	                                                                     
 */

#include <examples/tda2xx/include/chains.h>
#include <examples/tda2xx/include/chains_common.h>
#include <src/utils_common/include/utils_prcm_stats.h>
#include <src/utils_common/include/utils_uart.h>
#include "uartCmd_priv.h"

#pragma DATA_ALIGN(UartCmd_tskStack, 32)
#pragma DATA_SECTION(UartCmd_tskStack, ".bss:taskStackSection")
UInt8 UartCmd_tskStack[1024*4];


BspOsal_TaskHandle tsk;
static uint8_t RxBuf[DATA_MAX_LEN];
static uint8_t TxBuf[DATA_MAX_LEN];
static uint32_t RxBufPos = 0;


static int LOCAL_UART_isReceivedAll(uint8_t *buf, uint16_t len)
{
	uint16_t dataLen;

	if ( len < MIN_MSG_SIZE )
	{
		return -1;
	}
	dataLen = GET_LENGTH(buf);
	if ( len < dataLen + MSG_HEADER_LEN )
	{
		return -1;
	}
	return 0;
}


static uint8_t Make_BCC(uint8_t *pData, uint16_t len)
{
	uint8_t chksum = 0;
	int i;

    for(i = 0; i< (len+4); i++)
    	chksum ^= (*pData++);
    chksum |= 0x20; 			//in order not to same as 0x02,0x03, 0x0X
    return chksum;
}

static int UART_SendCmd(uint8_t targetId, uint8_t srcId, uint8_t *data, uint16_t dataLen)
{
	uint8_t bcc;
	size_t len;

	SET_START_TAG(TxBuf);
	SET_TARGET_ID(TxBuf, targetId);
	SET_SOURCE_ID(TxBuf, srcId);
	SET_LENGTH(TxBuf, dataLen);
	SET_DATA(TxBuf, data, dataLen);
	bcc = Make_BCC(&TxBuf[1], dataLen);
	SET_BCC(TxBuf, bcc);
	SET_END_TAG(TxBuf);

	len = MSG_HEADER_LEN+dataLen;
	UtillUartWrite(UART_CH_MICOM,TxBuf,&len);

	return 0;
}



static int UART_ParseCmd(uint8_t *rxBuf)
{
	uint8_t calcBcc;
	uint16_t dataLen;
	uint8_t buf[64];

	//
	/////////////////////////////////////////
	///   Error Check
	if ( GET_START_TAG(rxBuf) != START_TAG )
	{
		Vps_printf("START TAG Error");
		return MSG_ERROR_BAD_PARAMETER;
	}
	if ( GET_END_TAG(rxBuf) != END_TAG )
	{
		Vps_printf("END TAG Error");
		return MSG_ERROR_BAD_PARAMETER;
	}

	dataLen = GET_LENGTH(rxBuf);
	calcBcc = Make_BCC(&rxBuf[1], dataLen);
	if ( calcBcc != GET_BCC(rxBuf) )
	{
		Vps_printf("BCC error, calcBcc(%d), bcc(%d)\n", calcBcc, GET_BCC(rxBuf));
		return MSG_ERROR_BCC;
	}

	////////////////////////////////////////
	/// Parse message
	Vps_printf("ParserCMD [0x%02X] len[%d] data[0x%02X 0x%02X 0x%02X 0x%02X]", GET_COMMAND(rxBuf),dataLen,GET_ARG1(rxBuf), GET_ARG2(rxBuf), GET_ARG3(rxBuf), GET_ARG4(rxBuf));

	switch(GET_COMMAND(rxBuf))
	{
		case CMD_REQ_DSP_STANDBY:
		{

		}
		break;

		case CMD_REQ_DSP_STATUS:
		{
			Vps_printf("STATUS REQ");
			buf[0] = CMD_REQ_DSP_STATUS;
			buf[1] = ACK;
			buf[2] = DSP_STATUS_AVM_MODE;
			UART_SendCmd(DEV_ID_AVM_MICOM, DEV_ID_AVM_DSP, buf, 3);
		}
		break;

		case CMD_REQ_MICOM_VER:		// Recv version of AVM MICOM
			break;
		case CMD_SEND_IRDA_KEY:		// Recv IrDA command with Key value
			break;
		case CMD_SEND_RGEAR:		// Recv Rear Gear On/Off
			break;
		case CMD_CONTROL_VIDEO_OUT:	// ???
			break;
		case CMD_SDCARD_HPD:		// ???
			break;
		case CMD_REQ_VBAT_ADC:		// ???
			break;
		case CMD_DSP_REQ_TEST:
			break;

		case CMD_SEND_TURN_SIGNAL:
			break;
		case CMD_SEND_BUTTON_PRESSED:	///Recv Button Event
			break;
		case CMD_REQ_LVDS_STATUS:
			break;
		case CMD_REQ_AUDIO_OUT:
			break;
		default:
		{
			Vps_printf("UNKNOWN CMD\n");

		}
		break;
	}
	///
	////////////////////////////////////////
	return MSG_NO_ERROR;
}


static void SendDSPStatus(void)
{
	uint8_t buf[3];

	buf[0] = CMD_REQ_DSP_STATUS;
	buf[1] = ACK;
	buf[2] = DSP_STATUS_AVM_MODE;

	UART_SendCmd(DEV_ID_AVM_MICOM, DEV_ID_AVM_DSP, buf, 3);
}

Void UartCmd_tsk_main(UArg arg0, UArg arg1)
{
	SendDSPStatus();

	for(;;)
	{
		int parseResult = MSG_NO_ERROR;
		size_t len;
		UtillUartRead(UART_CH_MICOM,RxBuf+RxBufPos,&len);
		RxBufPos += len;
		if ( GET_START_TAG(RxBuf) != START_TAG)
		{
			//Vps_printf("[UART8] 0x%02x\n", rxBuf8[0]);
			RxBufPos = 0;
			continue;
		}
		if(RxBufPos >= DATA_MAX_LEN)
			RxBufPos = 0;
		if ( LOCAL_UART_isReceivedAll(RxBuf, RxBufPos) != 0 )
		{
			continue;
		}

		parseResult = UART_ParseCmd(RxBuf);
		RxBufPos = 0;

		if( parseResult != MSG_NO_ERROR)
		{
			///Error
			;
		}
	}
}


Int32 UartCmd_tsk_init()
{
	tsk = BspOsal_taskCreate(
			(BspOsal_TaskFuncPtr)UartCmd_tsk_main,
			1,
			UartCmd_tskStack,
			sizeof(UartCmd_tskStack),
			NULL);

    return 0;
}


Int32 UartCmd_tsk_deInit()
 {

    return 0;
 }