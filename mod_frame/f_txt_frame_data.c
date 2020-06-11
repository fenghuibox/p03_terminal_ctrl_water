/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 
#if 1

#include "com_includes.h"
#include "dbg_uart.h"

#include "f_txt_frame_data.h"



#include "f_txt_frame_dpara_base.h"
#include "f_txt_frame_dpara_zgb.h"
#include "f_txt_frame_dpara_ctrl.h"
#include "f_txt_frame_dpara_485.h"



const u16 paraIdArr[] = {
	DPACK_PARA_ID_CONFIG_VER,
	DPACK_PARA_ID_DEF,
	DPACK_PARA_ID_AES_SWITCH,
	DPACK_PARA_ID_AES_KEY,
	DPACK_PARA_ID_REBOOT,
	DPACK_PARA_ID_SLEEP_SEC,
	DPACK_PARA_ID_WORK_SEC,
	DPACK_PARA_ID_VER,
	DPACK_PARA_ID_DEV_TYPE,
	DPACK_PARA_ID_HEARTBEAT,
	DPACK_PARA_ID_BATTERY,
	DPACK_PARA_ID_CTRL_MODE,
	DPACK_PARA_ID_CMD_CTRL,
	DPACK_PARA_ID_OPEN_SEC,
	DPACK_PARA_ID_PERIOD_CTRL,
	DPACK_PARA_ID_CTRL_PACK,
	DPACK_PARA_ID_ZIGBEE_TO_RESET,
	DPACK_PARA_ID_ZIGBEE_TO_DEF,
	DPACK_PARA_ID_ZIGBEE_AUTO_NET,
	DPACK_PARA_ID_ZIGBEE_STATE,
	DPACK_PARA_ID_ZIGBEE_INFO,
	DPACK_PARA_ID_UART485,

};

#define DPACK_PARA_ID_CNT  (22)// ����




//-------------------------------------------------------------------------------
/*
����ֵ
�������ֵ   FAIL�����ʾ û�ҵ�
�������ֵ >= 0�����ʾ �ҵ���
*/
int dpackFindParaId( u16 paraId ) // 2�ֲ���
{
    u8 low, high, mid;

    low  = 0;
    high = DPACK_PARA_ID_CNT - 1;
	
    while( low <= high )    //���ҷ�Χ��Ϊ0ʱִ��ѭ�������
    {        
        mid = ( low + high ) / 2;    //���м�λ��

		if( paraId < paraIdArr[mid] )
        {
            high = mid - 1;    //ȷ�����ӱ�Χ
        }
        else if( paraId > paraIdArr[mid] )    //key �����м�ֵʱ
        {
            low = mid + 1;    //ȷ�����ӱ�Χ
        }
        else //��key�����м�ֵʱ��֤�����ҳɹ�
        {
			return mid;
        }
    }

    return FAIL;
}




/*
���ݰ� ��ʽ����		
------------------------------------------------------
���ݰ���Ա��	�ֽ���	����
------------------------------------------------------
����				1	���ݰ��ĳ��ȡ�
�ն˵Ķ˿�ID		1	��Ʒ�Ķ˿ڱ�š�
�ն˶˿ڵ�ͨ�ŵ�ַ	1	����485��ַ�š�
����ID				2	���ݰ��Ĳ�����š�
����ֵ				n	������ֵ��
-----------------------------------------------------*/




u8 dpackLenIsOk( u8 len )
{
	if( len < DPACK_LEN_MIN || len > DPACK_LEN_MAX )
		return FALSE;

	return TRUE;
}



u8 dpackPortIdIsOk( u8 portId )
{
	if(  portId >= DPACK_PORT_ID_MAX )
		return FALSE;

	return TRUE;
}



u8 dpackParaIdIsOk( u16 paraId )
{
	if( dpackFindParaId( paraId ) != FAIL )
		return TRUE;
		
		return FALSE;
	
}



u16 dpackGetParaId( u8 *pDpack )
{
	return byteMergeto16( pDpack[DPACK_OFFSET_PARA_ID_1], pDpack[DPACK_OFFSET_PARA_ID_2] );
}



EN_FRAME_UNPACK dpackUnpack( u8 *pDpack )
{
	u16 paraId;
	
	if( dpackLenIsOk( pDpack[DPACK_OFFSET_LEN] ) == FALSE )
	{
		dprintf("lenNG");
		return FRAME_UNPACK_NG_DPACK_LEN;
	}

	if( dpackPortIdIsOk( pDpack[DPACK_OFFSET_PORT_ID] ) == FALSE )
	{
		dprintf("portIdNG");
		return FRAME_UNPACK_NG_DPACK_PORT_ID;
	}

	paraId = byteMergeto16( pDpack[DPACK_OFFSET_PARA_ID_1], pDpack[DPACK_OFFSET_PARA_ID_2] );
	
	if( dpackParaIdIsOk( paraId ) == FALSE )
	{
		dprintf("paraIdNG");
		return FRAME_UNPACK_NG_DPACK_PARA_ID;
	}

	return FRAME_UNPACK_OK;
}


/*
���ݰ� ��ʽ����		
------------------------------------------------------
���ݰ���Ա��	�ֽ���	����
------------------------------------------------------
����				1	���ݰ��ĳ��ȡ�
�ն˵Ķ˿�ID		1	��Ʒ�Ķ˿ڱ�š�
�ն˶˿ڵ�ͨ�ŵ�ַ	1	����485��ַ�š�
����ID				2	���ݰ��Ĳ�����š�
����ֵ				n	������ֵ��
-----------------------------------------------------*/
void dpackCreate( EN_DPACK_PORT_ID portId, u8 addr, EN_DPACK_PARA_ID paraId, u8 *pVal,u8 valLen, u8 *pDpack )
{
	#if 1
	u16 temp;

	pDpack[DPACK_OFFSET_LEN]        = DPACK_LEN_CONST_ELE + valLen;
	pDpack[DPACK_OFFSET_PORT_ID]    = portId;
	pDpack[DPACK_OFFSET_PORT_ADDR]  = addr;

	temp = (u16)paraId;

	u16splitToByteHL(temp, pDpack + DPACK_OFFSET_PARA_ID_1 );


	if( valLen )
		memcpy( pDpack + DPACK_OFFSET_PARA, pVal, valLen);
	
	#else
	u16 temp;

	pDpack[0]		 = DPACK_LEN_CONST_ELE + valLen;
	pDpack[1]	 = portId;
	pDpack[2]  = addr;

	temp = (u16)paraId;

	pDpack[3] = temp>>8;
	pDpack[4] = temp&0xFF;
	
	if( valLen )
		memcpy( pDpack + DPACK_OFFSET_PARA, pVal, valLen);

	#endif
}

/*
���ݰ� ��ʽ����		
------------------------------------------------------
���ݰ���Ա��	�ֽ���	����
------------------------------------------------------
����				1	���ݰ��ĳ��ȡ�
�ն˵Ķ˿�ID		1	��Ʒ�Ķ˿ڱ�š�
�ն˶˿ڵ�ͨ�ŵ�ַ	1	����485��ַ�š�
����ID				2	���ݰ��Ĳ�����š�
����ֵ				n	������ֵ��
-----------------------------------------------------*/
void dpackCreate1( EN_DPACK_PORT_ID portId, u8 addr, EN_DPACK_PARA_ID paraId, u8 valLen, u8 *pDpack )
{
	#if 1
	u16 temp;

	pDpack[DPACK_OFFSET_LEN]        = DPACK_LEN_CONST_ELE + valLen;
	pDpack[DPACK_OFFSET_PORT_ID]    = portId;
	pDpack[DPACK_OFFSET_PORT_ADDR]  = addr;
		
	temp = (u16)paraId;
	
	u16splitToByteHL(temp, pDpack + DPACK_OFFSET_PARA_ID_1 );

	#else

	u16 temp;

	pDpack[0]        = DPACK_LEN_CONST_ELE + valLen;
	pDpack[1]    = portId;
	pDpack[2]  = addr;

	temp = (u16)paraId;
	
	pDpack[3] = temp>>8;
	pDpack[4] = temp&0xFF;
	
	//*( (U16 *)(pDpack + 3) )  = paraId;

	#endif

	
}




//==============================================================================================



typedef  u8 ( *FunDPackParaExeCB)(  ST_FRAME *pstFrame );



	

const FunDPackParaExeCB _dpackParaExeArr[] = {
	para_config_ver_exe,
	para_def_exe,
	para_aes_switch_exe,
	para_aes_key_exe,
	para_reboot_exe,
	para_sleep_sec_exe,
	para_work_sec_exe,
	para_ver_exe,
	para_dev_type_exe,
	para_heartbeat_exe,
	para_battery_exe,
	para_ctrl_mode_exe,
	para_cmd_ctrl_exe,
	para_open_sec_exe,
	para_period_ctrl_exe,
	para_ctrl_pack_exe,
	para_zigbee_to_reset_exe,
	para_zigbee_to_def_exe,
	para_zigbee_auto_net_exe,
	para_zigbee_state_exe,
	para_zigbee_info_exe,
	para_uart485_exe,

};




int dpackExe(ST_FRAME *pstFrame )
{
	U16 paraId;
	int index;

	paraId = byteMergeto16( pstFrame->pBuf[DPACK_OFFSET_PARA_ID_1], pstFrame->pBuf[DPACK_OFFSET_PARA_ID_2] );

	index = dpackFindParaId(paraId);
	if( index == FAIL )
	{
		dprintf("err paraId=%d",paraId );
		return FALSE;
	}

	return _dpackParaExeArr[index]( pstFrame );

}



void dpackInit( void )
{



}



#endif


