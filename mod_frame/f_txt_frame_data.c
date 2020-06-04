/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 
#if 0

#include "com_includes.h"
#include "dbg_uart.h"

#include "f_txt_frame_data.h"



#include "f_txt_frame_dpara_base.h"
#include "f_txt_frame_dpara_zgb.h"
#include "f_txt_frame_dpara_4g.h"
#include "f_txt_frame_dpara_ctrl.h"
#include "f_txt_frame_dpara_ctrl_out_sec.h"
#include "f_txt_frame_dpara_485.h"
#include "f_txt_frame_dpara_adc.h"
#include "f_txt_frame_dpara_dac.h"



const u16 paraIdArr[] = {
	DPACK_PARA_ID_CONFIG_VER,
	DPACK_PARA_ID_DEF,
	DPACK_PARA_ID_AES_SWITCH,
	DPACK_PARA_ID_AES_KEY,
	DPACK_PARA_ID_REBOOT,
	DPACK_PARA_ID_VER,
	DPACK_PARA_ID_DEV_TYPE,
	DPACK_PARA_ID_HEARTBEAT,
	DPACK_PARA_ID_BATTERY,
	DPACK_PARA_ID_WORK_STATE,
	DPACK_PARA_ID_CTRL_IN,
	DPACK_PARA_ID_CTRL_OUT,
	DPACK_PARA_ID_ZIGBEE_TO_RESET,
	DPACK_PARA_ID_ZIGBEE_TO_DEF,
	DPACK_PARA_ID_ZIGBEE_AUTO_NET,
	DPACK_PARA_ID_ZIGBEE_ALLOW_JOIN,
	DPACK_PARA_ID_ZIGBEE_DEL_BY_MAC_ADDR,
	DPACK_PARA_ID_ZIGBEE_CHILD_INFO,
	DPACK_PARA_ID_ZIGBEE_WORK_STATE,
	DPACK_PARA_ID_ZIGBEE_INFO,
	DPACK_PARA_ID_G4_TO_RESET,
	DPACK_PARA_ID_G4_TO_DEF,
	DPACK_PARA_ID_G4_STATE_GET,
	DPACK_PARA_ID_G4_IMEI_GET,
	DPACK_PARA_ID_G4_RSSI_BER_GET,
	DPACK_PARA_ID_G4_QMT_OPEN_NET,
	DPACK_PARA_ID_G4_QMT_CONN_USER,
	DPACK_PARA_ID_G4_QMT_CONN_PWD,
	DPACK_PARA_ID_G4_QMT_CLIENT_ID,
	DPACK_PARA_ID_G4_QMT_PUBEX_QOS,
	DPACK_PARA_ID_G4_QMT_SUB_TOPIC_QOS,
	DPACK_PARA_ID_UART485,
	DPACK_PARA_ID_ADC1,
	DPACK_PARA_ID_ADC2,
	DPACK_PARA_ID_DAC1,
	DPACK_PARA_ID_DAC2,
	
	DPACK_PARA_ID_CTRL_OUT1_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT2_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT3_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT4_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT5_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT6_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT7_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT8_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT9_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT10_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT11_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT12_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT13_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT14_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT15_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT16_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT17_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT18_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT19_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT20_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT21_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT22_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT23_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT24_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT25_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT26_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT27_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT28_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT29_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT30_ON_SEC,
	DPACK_PARA_ID_CTRL_OUT31_ON_SEC,
	
	
};

#define DPACK_PARA_ID_CNT  (67)// 总数




//-------------------------------------------------------------------------------
/*
返回值
如果返回值   FAIL，则表示 没找到
如果返回值 >= 0，则表示 找到了
*/
int dpackFindParaId( u16 paraId ) // 2分查找
{
    u8 low, high, mid;

    low  = 0;
    high = DPACK_PARA_ID_CNT - 1;
	
    while( low <= high )    //査找范围不为0时执行循环体语句
    {        
        mid = ( low + high ) / 2;    //求中间位置

		if( paraId < paraIdArr[mid] )
        {
            high = mid - 1;    //确定左子表范围
        }
        else if( paraId > paraIdArr[mid] )    //key 大于中间值时
        {
            low = mid + 1;    //确定右子表范围
        }
        else //当key等于中间值时，证明查找成功
        {
			return mid;
        }
    }

    return FAIL;
}




/*
数据包 格式定义		
------------------------------------------------------
数据包成员名	字节数	解释
------------------------------------------------------
长度				1	数据包的长度。
终端的端口ID		1	产品的端口编号。
终端端口的通信地址	1	例：485地址号。
参数ID				2	数据包的参数编号。
参数值				n	参数的值。
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
数据包 格式定义		
------------------------------------------------------
数据包成员名	字节数	解释
------------------------------------------------------
长度				1	数据包的长度。
终端的端口ID		1	产品的端口编号。
终端端口的通信地址	1	例：485地址号。
参数ID				2	数据包的参数编号。
参数值				n	参数的值。
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
数据包 格式定义		
------------------------------------------------------
数据包成员名	字节数	解释
------------------------------------------------------
长度				1	数据包的长度。
终端的端口ID		1	产品的端口编号。
终端端口的通信地址	1	例：485地址号。
参数ID				2	数据包的参数编号。
参数值				n	参数的值。
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
	para_ver_exe,
	para_dev_type_exe,
	para_heartbeat_exe,
	para_battery_exe,
	para_work_state_exe,
	para_ctrl_in_exe,
	para_ctrl_out_exe,
	para_zigbee_to_reset_exe,
	para_zigbee_to_def_exe,
	para_zigbee_auto_net_exe,
	para_zigbee_allow_join_exe,
	para_zigbee_del_by_mac_addr_exe,
	para_zigbee_child_info_exe,
	para_zigbee_work_state_exe,
	para_zigbee_info_exe,
	para_g4_to_reset_exe,
	para_g4_to_def_exe,
	para_g4_state_get_exe,
	para_g4_imei_get_exe,
	para_g4_rssi_ber_get_exe,
	para_g4_qmt_open_net_exe,
	para_g4_qmt_conn_user_exe,
	para_g4_qmt_conn_pwd_exe,
	para_g4_qmt_client_id_exe,
	para_g4_qmt_pubex_qos_exe,
	para_g4_qmt_sub_topic_qos_exe,
	para_uart485_exe,
	para_adc1_exe,
	para_adc2_exe,
	para_dac1_exe,
	para_dac2_exe,		
	
	para_ctrl_out1_on_sec_exe,
	para_ctrl_out2_on_sec_exe,
	para_ctrl_out3_on_sec_exe,
	para_ctrl_out4_on_sec_exe,
	para_ctrl_out5_on_sec_exe,
	para_ctrl_out6_on_sec_exe,
	para_ctrl_out7_on_sec_exe,
	para_ctrl_out8_on_sec_exe,
	para_ctrl_out9_on_sec_exe,
	para_ctrl_out10_on_sec_exe,
	para_ctrl_out11_on_sec_exe,
	para_ctrl_out12_on_sec_exe,
	para_ctrl_out13_on_sec_exe,
	para_ctrl_out14_on_sec_exe,
	para_ctrl_out15_on_sec_exe,
	para_ctrl_out16_on_sec_exe,
	para_ctrl_out17_on_sec_exe,
	para_ctrl_out18_on_sec_exe,
	para_ctrl_out19_on_sec_exe,
	para_ctrl_out20_on_sec_exe,
	para_ctrl_out21_on_sec_exe,
	para_ctrl_out22_on_sec_exe,
	para_ctrl_out23_on_sec_exe,
	para_ctrl_out24_on_sec_exe,
	para_ctrl_out25_on_sec_exe,
	para_ctrl_out26_on_sec_exe,
	para_ctrl_out27_on_sec_exe,
	para_ctrl_out28_on_sec_exe,
	para_ctrl_out29_on_sec_exe,
	para_ctrl_out30_on_sec_exe,
	para_ctrl_out31_on_sec_exe,
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


