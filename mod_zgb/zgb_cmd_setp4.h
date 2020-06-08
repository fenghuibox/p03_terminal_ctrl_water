/*--------------------------------------------------------------|
 *| company | 湖南华中苗木云科技有限公司                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | 冯  辉                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/



//=================================================

/*----------------------------------------------
临时参数配置协议与命令
------------------------------------------------
3 字节（协议标志）  1 字节    N 字节
 DE DF EF           功能码     参数
------------------------------------------------*/
const u8 zcmdTempHead[] = {0xDE, 0xDF, 0xEF};



/*----------------------------------------------
永久参数配置协议与命令
------------------------------------------------
3 字节（协议标志）   1 字节     N 字节      1 字节（帧尾）
    AB BC CD       命令标识符   命令实体      AA
------------------------------------------------*/
const u8 zcmdForeverHead[] = {0xAB, 0xBC, 0xCD};





//====================================================================================
//===== // step 4 =====解释接收内容，转化为结果=======================================
//====================================================================================
int zcmdRx( u8 *pBuf, u32 len )
{
	u8 pTemp[2];
	
	if( len < 4 )
		return FALSE;

	if( memcmp(pBuf, zcmdForeverHead, ZCMD_FOREVER_HEAD_LEN ) == 0)
	{
		switch(pBuf[ZCMD_FOREVER_ID_OFFSET] )
		{
		case ZCMD_FOREVER_HEAD_ID_DEF:
			if( ZCMD_FOREVER_HEAD_ID_DEF_RST_LEN != len )
				return FALSE;
		
			if( pBuf[ZCMD_FOREVER_HEAD_ID_DEF_RST_LEN - 1] != 0 )
				return FALSE;
		
			_stZcmdTx.def = 0;
		
			return TRUE;
		
		//------------- dev info get-----------------------------------------------------------		
		case ZCMD_FOREVER_HEAD_ID_DEV_INFO_GET:
			if( ZCMD_FOREVER_HEAD_ID_DEV_INFO_GET_RST_LEN != len )
				return FALSE;

			memcpy( &_stZdevInfo, pBuf + ZCMD_FOREVER_PARA1_OFFSET, sizeof(ST_ZIGBEE_DEV_INFO ) );

			_stZcmdTx.devInfoGet = 0;

			//_stZcmdPara.isOk = 1;

			return TRUE;

		//------------- dev info set-----------------------------------------------------------
		case ZCMD_FOREVER_HEAD_ID_DEV_INFO_SET:
			if( ZCMD_FOREVER_HEAD_ID_DEV_INFO_SET_RST_LEN != len )
				return FALSE;
			
			_stZcmdTx.devInfoSet = 0;

			_stZcmdTx.reboot = 1; // 重启一下 fenghuiwait
			
			return TRUE;
			

		//-------------auto net -----------------------------------------------------------
		case ZCMD_FOREVER_HEAD_ID_AUTO_NET:
			if( ZCMD_FOREVER_HEAD_ID_AUTO_NET_RST_LEN != len )
				return FALSE;

			if( pBuf[ZCMD_FOREVER_PARA1_OFFSET] )
				_stZcmdPara.autoNet = 1;
			else
				_stZcmdPara.autoNet = 0;
			
			
			_stZcmdTx.autoNet = 0;

			return TRUE;
						
		//------------- work state -----------------------------------------------------------
		case ZCMD_FOREVER_HEAD_ID_WORK_STATE:
			if( ZCMD_FOREVER_HEAD_ID_WORK_STATE_RST_LEN != len )
				return FALSE;
			
			_stZcmdPara.workState = pBuf[ZCMD_FOREVER_PARA1_OFFSET];
			
			_stZcmdTx.workState = 0;

			_stZcmdPara.isOk = 1;
		
			return TRUE;

			
			
		default: 
			//return FALSE;// fenghuierr
			return TRUE;
		}

	}
	else if ( memcmp(pBuf, zcmdTempHead, ZCMD_TEMP_HEAD_LEN ) == 0)
	{
		switch(pBuf[ZCMD_TEMP_ID_OFFSET] )
		{
		case ZCMD_TEMP_HEAD_ID_LQI:
			if( ZCMD_TEMP_HEAD_ID_LQI_RST_LEN != len )
				//return FALSE;// fenghuierr
				return TRUE;
		

			// RSP: DE DF EF DA 20 02 BA // 获取到的信号强度为 0xBA
			_Lqi = pBuf[6];
			
			_stZcmdTx.lqi = 0;
		
			return TRUE;

		default: 
			//return FALSE;// fenghuierr
			return TRUE;
		}
	}

	return FALSE;
}

