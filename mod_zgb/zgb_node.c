/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 
#if 0

#include "com_includes.h"

#include "dbg_uart.h"

#include "timer.h"





#include "zgb_cmd.h"

#include "zgb_node.h"
#include "zgb_mac.h"


//#include "f_frame_comm.h"





static ST_NODE _pstNode[NODE_CNT];

static u8 _nodeCnt; // �ڵ����

static u8 _isHaveCmdToNode; // �����Ƿ�������Ҫ���͸��ڵ�  1: ��  0: û��

static u8 _getChildInfoStartId;

//-------------------------------------------------------------------------------

/*
static void _nodeInit( ST_NODE *pNode )
{
	memset( pNode, 0, sizeof(ST_NODE)  );

	pNode->sendCmdBit = BIT_G2N__MASK_INIT;
}
*/

void modNodeClear( void )
{
	u8 i;
	
	memset( _pstNode, 0, sizeof(ST_NODE) * NODE_CNT  );
	

	for( i = 0; i < NODE_CNT; i++ )
	{
		_pstNode[i].sendCmdBit = BIT_G2N__MASK_INIT;
	}

	_nodeCnt = 0;

	_isHaveCmdToNode = 0;

	_getChildInfoStartId = 0;
	

	
}






//-------------------------------------------------------------------------------
/*
����ֵ
�������ֵ < 0�����ʾ û�ҵ���  pMac < _pstNode[ *pIndex].pMac ��
�������ֵ > 0�����ʾ û�ҵ���  pMac > _pstNode[ *pIndex].pMac ��
�������ֵ = 0�����ʾ �ҵ��ˣ�  pMac = _pstNode[ *pIndex].pMac ��
*/
int binarySearchMac( u8 *pMac, u8 *pIndex ) 
{
    u8 low, high, mid;
	int cmpRst;

	cmpRst = -1;
	
    low = 0;

	if( _nodeCnt == 0 )
	{
		*pIndex = 0;
		return -1; // fenghuiwait
	}
	else if( _nodeCnt == 1 )
	{
		*pIndex = 0;
		return memcmp( pMac, _pstNode[0].pMac, MAC_ADDR_LEN );
	}
	
    high = _nodeCnt - 1;
	
    while( low <= high )    //���ҷ�Χ��Ϊ0ʱִ��ѭ�������
    {        
        mid = ( low + high ) / 2;    //���м�λ��

		cmpRst =  memcmp( pMac, _pstNode[mid].pMac, MAC_ADDR_LEN );
        
        if( cmpRst < 0 )    //key С���м�ֵʱ
        {
        	if( mid == 0 )
        	{
        		*pIndex = 0;
				return cmpRst;
        	}
						
            high = mid - 1;    //ȷ�����ӱ�Χ
        }
        else if( cmpRst > 0 )    //key �����м�ֵʱ
        {
        	if( mid == high )
    		{
        		*pIndex = mid;
				return cmpRst;
    		}
			
            low = mid + 1;    //ȷ�����ӱ�Χ
        }
        else if( cmpRst == 0 )    //��key�����м�ֵʱ��֤�����ҳɹ�
        {
			break;
        }
    }

	*pIndex = mid;

    return cmpRst;
}





u8 modNodeCntGet( void )
{
	return _nodeCnt;
}


//------ ���� MAC��ַ ��Ӧ �Ķ̵�ַ  ------------------------------------
/*
in: pMac

out: pSaddr

result:  TRUE : ���ҵ��ڵ�  FALSE: û�в��ҵ��ڵ�
*/
u8 modNodeGetSaddrByMac( u8 *pMac, u16 *pSaddr )
{
	u8 index;
	
	if( binarySearchMac( pMac, &index ) != 0 )
	{
		return FALSE;
	}

	*pSaddr = _pstNode[ index ].saddr;

	return TRUE;
}




//------find-------------------------------------------------
/*
����ֵ
�������ֵ < 0�����ʾ û�ҵ���  pMac < _pstNode[ *pIndex].pMac ��
�������ֵ > 0�����ʾ û�ҵ���  pMac > _pstNode[ *pIndex].pMac ��
�������ֵ = 0�����ʾ �ҵ��ˣ�  pMac = _pstNode[ *pIndex].pMac ��
*/
int modNodeFindByMac( u8 *pMac, u8 *pIndex )
{
	return binarySearchMac( pMac, pIndex );
}


/*
result:
   TRUE : �����صĽڵ�
   FALSE: �������صĽڵ�
*/
int modNodeMacIsNode( u8 *pMac )
{
	u8 index;
	
	if( binarySearchMac( pMac, &index ) == 0 )
		return TRUE;

	//modUartDebugTx0( "\r\nmodNodeMacIsNode_x1" );

	return FALSE;
}


//------del-------------------------------------------------
int modNodeDelByMac( u8 *pMac )
{
	u8 index;
	u8 i;
	
	if( 0 != binarySearchMac( pMac, &index ) )
	{
		return FALSE;
	}

	//---------------------------------------
	_nodeCnt--;
	
	for( i = index; i < _nodeCnt; i++ )
	{
		memcpy( &_pstNode[ i ], &_pstNode[ i + 1 ], sizeof(ST_NODE) );
	}

	memset( &_pstNode[ _nodeCnt ], 0, sizeof(ST_NODE) );

	return TRUE;
}







//------add----���� load �е���---------------------------------------------
int modNodeAddByMac( ST_NODE_ADDR *pNodeAddr )
{
	int rst;
	u8 index;
	u8 i;

	if( _nodeCnt >= NODE_CNT )
	{
		dprintf( "\r\nmodNodeAdd X0" );
		return FALSE;
	}

	if( _nodeCnt == 0 )
	{
		//_nodeInit( &_pstNode[0] );
		memcpy( &_pstNode[0], pNodeAddr, sizeof(ST_NODE_ADDR) );
		_nodeCnt = 1;
		return TRUE;
	}
	
	rst = binarySearchMac( pNodeAddr->pMac, &index );

	if( rst == 0 )
	{
		dprintf( "\r\nmodNodeAdd X1" );
		return FALSE;
	}

	if( rst > 0 )
	{
		index ++;
	}

	if( _nodeCnt == index ) // inset tail
	{
		//_nodeInit( &_pstNode[_nodeCnt] );
		memcpy( &_pstNode[_nodeCnt], pNodeAddr, sizeof(ST_NODE_ADDR) );
		_nodeCnt++;
		return TRUE;
	}

	//---------------------------------------
	for( i = _nodeCnt; i > index; i-- )
	{
		memcpy( &_pstNode[ i ], &_pstNode[ i - 1 ], sizeof(ST_NODE_ADDR) );
	}

	memcpy( &_pstNode[ index ], pNodeAddr, sizeof(ST_NODE_ADDR) );

	_nodeCnt++;

	return TRUE;
	
	
}







//-------------------------------------------------------
/*
�����ڵ�
*/
void modNodeTraversal( FunNodeTraversalCB  nodeTraversalCB )
{
	u8 i;

	if( nodeTraversalCB == NULL )
		return;
	
	for( i = 0; i < _nodeCnt; i++ )
	{
		nodeTraversalCB(  _pstNode + i );
	}
}



static void _nodeOnePrint( ST_NODE *pNode )
{

	dprintfBuf( "\r\nmac=", pNode->pMac,  MAC_ADDR_LEN, 0 ); 
	
	dprintf( " saddr=%2X", pNode->saddr ); 
}



static void _nodePrint( void )
{
	dprintf( "\r\n_nodeCnt=%d", _nodeCnt  ); 

	modNodeTraversal( _nodeOnePrint );
}


//-------------------------------------------------------
/*
����װ�����صĽڵ�

�յ� ��ѯ����ģ��洢�Ĵӻ���Ϣ���� �Ľ����ֱ�ӵ��ô˺���
*/
void modNodeLoad( u8 cnt, ST_NODE_ADDR *pNodeSAddr  )
{
	u8 i;

	dprintf( "\r\nmodNodeLoad cnt=%d", cnt  ); 

	// 1 clear 
	modNodeClear();


	// 2 add
	for( i = 0; i < cnt; i++ )
	{
		modNodeAddByMac( pNodeSAddr + i );
	}

	_nodePrint();
	
}


/*
------pNodeBuf----------------------------------
         nodeCnt  startId   getCnt  pNodeMac
------------------------------------------------
  len:    1byte    1byte    1byte   8byte * n 
------------------------------------------------
  value:  1- n     1- n     0- n
------------------------------------------------
����ֵ: �ܵ��ֽ���
*/
u8 modNodeGet( u8 *pNodeBuf )
{
	u8 i, j;
	u8 *pTemp;

	pNodeBuf[0] = _nodeCnt;
	pNodeBuf[1] = _getChildInfoStartId;

	pTemp = pNodeBuf + 3;
	j = 0;
	
	for( i = _getChildInfoStartId - 1 ; i < _nodeCnt && j < 10; i++, j++ )
	{
		macCopy( pTemp,  _pstNode[ i ].pMac );

		pTemp += MAC_ADDR_LEN;
	}

	
	pNodeBuf[2] = j;

	return 3 + j * MAC_ADDR_LEN;

}


void modNodeStartIdSet( u8 startId )
{
	_getChildInfoStartId = startId;
}




static u8 _IsHaveG2Ncmd( ST_NODE *pNode )
{
	u8 cmdBit;

	cmdBit = pNode->sendCmdBit;
	
	if( cmdBit & BIT_G2N__MASK  )
		return TRUE;

	return FALSE;
}






/* ***********************************
  1 ���յ�����ȷ������֡
  2 ��ȡMAC
  3 ���� �˺���
************************************* */
void modNodeUpdate( u8 *pMac )
{
	//int rst;
	u8 index;
	
	//if( _isHaveCmdToNode == 0 ) // fenghuiwait_1
	//	return;

	if( modNodeFindByMac( pMac, &index ) == 0 ) // �ҵ��˴˽ڵ�
	{
		if( _IsHaveG2Ncmd( _pstNode + index ) )
		{
			_pstNode[index].active = NODE_ACTIVE_VAL_MAX; // �˽ڵ���Ҫ���͵�����
		}
		else
		{
			return; // �˽ڵ�û��Ҫ���͵�����
		}
	}
	else
	{
		// ���µĽڵ�,���¶�ȡ

		dprintfBuf( "\r\nmodNodeUpdate have new node:", pMac, 8, 0 ); //
		
		zcmdChildInfoGet(); // ���¶�ȡ���нڵ�  or driSoftReset()  fenghuiwait_1
		//driSoftReset();
	}
}




u8 modNodeIsHaveG2Ncmd( void )
{
	return _isHaveCmdToNode;
}

//-----------------------------------------------------------------

u8 modNodeIsHaveG2NcmdRsp( u8 index )
{
	u8 cmdBit;

	cmdBit = _pstNode[index].sendCmdBit;
	
	if( cmdBit & BIT_G2N_RSP_ACK  )
		return TRUE;

	return FALSE;
}
//-----------------------------------------------------------------

u8 modNodeIsHaveG2NcmdSetKey( u8 index )
{
	u8 cmdBit;

	cmdBit = _pstNode[index].sendCmdBit;
	
	if( ( cmdBit & BIT_G2N_SET_KEY ) == 0 )
		return TRUE;

	return FALSE;
}

u8 modNodeG2NcmdSetKeyBitSet( u8 index )
{
	if( index >= _nodeCnt )
		return FALSE;

	_pstNode[index].sendCmdBit |= BIT_G2N_SET_KEY;

	return TRUE;
}

u8 modNodeG2NcmdSetKeyBitClear( u8 index )
{
	if( index >= _nodeCnt )
		return FALSE;

	_pstNode[index].sendCmdBit &= ~BIT_G2N_SET_KEY;

	return TRUE;
}


//-----------------------------------------------------------------
u8 modNodeIsHaveG2NcmdSetAesSwitch( u8 index )
{
	u8 cmdBit;

	cmdBit = _pstNode[index].sendCmdBit;
	
	if( ( cmdBit & BIT_G2N_SET_AES_SWITCH ) == 0 )
		return TRUE;

	return FALSE;
}

u8 modNodeG2NcmdSetAesSwitchBitSet( u8 index )
{
	if( index >= _nodeCnt )
		return FALSE;
	
	_pstNode[index].sendCmdBit |= BIT_G2N_SET_AES_SWITCH;

	return TRUE;
}

u8 modNodeG2NcmdSetAesSwitchBitClear( u8 index )
{
	if( index >= _nodeCnt )
		return FALSE;

	_pstNode[index].sendCmdBit &= ~BIT_G2N_SET_AES_SWITCH;

	return TRUE;
}
//-----------------------------------------------------------------




/*  �Ӵ�С����  ����:
-------------------------------------------------------
                  index  0 1 2 3
_pstNode[ index ].active 5 7 8 2
-------------------------------------------------------
            index  0 1 2 3
  pIndex[ index ]  2 1 0 3 ( --> 8 7 5 2)
-------------------------------------------------------
*/
static int _sortActive( u8 *pIndex )
{
	
    u8 n;     //�������a��Ԫ�صĸ���
    u8 i;     //�Ƚϵ�����
    u8 j;     //ÿ�ֱȽϵĴ���
    u8 temp;  //��������ʱ���ڴ���м�����
    

	if( _nodeCnt == 0 )
		return 0;

	//--------------------------------
    n = _nodeCnt;

	for( i = 0; i < _nodeCnt; i++ )
	{
		pIndex[i] = i;
	}
	//--------------------------------
	
	
    for ( i = 0; i < n - 1; ++i )  //�Ƚ�n-1��
    {
        for ( j =  0; j < n - 1 - i; ++j )  //ÿ�ֱȽ�n-1-i��,
        {
            if ( _pstNode[ pIndex[j] ].active < _pstNode[ pIndex[j+1] ].active )
            {
                temp        = pIndex[j];
                pIndex[j]   = pIndex[j+1];
                pIndex[j+1] = temp;
            }
        }
    }

    return n;
}


/*
����������Ҫ���͵Ľڵ��У����Ծ�Ľڵ���±�, û��ʱ���� -1
*/
int modNodeGetMaxActiveNodeIndex( void )
{
	u8 i;
	U8 pIndex[ NODE_CNT ];
	
	_sortActive( pIndex );

	for( i = 0; i < _nodeCnt; i++ )
	{
		if(_pstNode[ pIndex[i] ].active > NODE_ACTIVE_VAL_VALID )
		{
			if( _IsHaveG2Ncmd( _pstNode + pIndex[i] ) )
				return pIndex[i];
		}
	}

	return -1;
}


u8 modNodeGetSaddrByIndex( u8 index, u16 *pSaddr )
{
	if( index >= _nodeCnt )
		return FALSE;
	
	*pSaddr = _pstNode[index].saddr;

	return TRUE;
}


u8 modNodeGetMacByIndex( u8 index, u8 *pMac )
{
	if( index >= _nodeCnt )
		return FALSE;
	
	macCopy( pMac, _pstNode[index].pMac );

	return TRUE;
}



static void _nodeCB( void )
{
	u8 i;
	U8 haveCmd = 0;
	
	for( i = 0; i < _nodeCnt; i++ )
	{
		if( _IsHaveG2Ncmd( _pstNode + i ) ) // ����������Ҫ���͸��˽ڵ�
		{
			haveCmd = 1;
			
			if( _pstNode[i].active > 0 )
			{
				_pstNode[i].active--;
			}
 		}
	}

	if( haveCmd == 0 )
	{
		_isHaveCmdToNode = 0;
	}
	else
	{
		_isHaveCmdToNode = 1;
	}
}

void zgbNodeInit( void )
{
	modNodeClear();

	timerStartSec( NODE_ACTIVE_VAL_UPDATE_GAP, TIMER_REPEAT_FOREVER, _nodeCB );
}





#ifdef TEST_ZGB_NODE

const ST_NODE_ADDR stTestNode[5] = {
	   {{0x03,  0x77,  0x3B,	0xE6,  0x00,  0x15,  0x8D,	0x00},  {1}}  // 1
	,  {{0x03,  0x77,  0x47,	0x9A,  0x00,  0x15,  0x8D,	0x00},  {2}}  // 2
	,  {{0x04,  0xA8,  0x1B,	0x6B,  0x00,  0x15,  0x8D,	0x00},  {3}}  // 3
	,  {{0x04,  0xA8,  0x08,	0x68,  0x00,  0x15,  0x8D,	0x00},  {4}}  // 4
	,  {{0x04,  0xA8,  0x2A,	0x00,  0x00,  0x15,  0x8D,	0x00},  {5}}  // 5

};


const u8 pNode3Mac[] = { 0x04,  0xA8,  0x1B,	0x6B,  0x00,  0x15,  0x8D,	0x00 };// 3

const u8 pNodeErrMac[] = { 0x04,  0xA8,  0x11,	0x61,  0x00,  0x15,  0x8D,	0x00 };// err


void testZgbNode( void )
{
	u16 saddr;
	
	zgbNodeInit();

	modNodeLoad( 5, (ST_NODE_ADDR *) &stTestNode[0] );


	//-----------------------------------------------
	if( modNodeMacIsNode( (u8 *)pNode3Mac ) == FALSE )
	{
		dprintf( "\r\ntestModNode x1" ); //
	}

	
	if( modNodeMacIsNode( (u8 *)pNodeErrMac ) == TRUE )
	{
		dprintf( "\r\ntestModNode x2" ); //
	}

	
	//-----------------------------------------------
	if( modNodeGetSaddrByMac( (u8 *)pNode3Mac, &saddr ) == TRUE )
	{
		dprintf( "\r\nsaddr=%02X", saddr ); //
	}
	else
	{
		dprintf( "\r\ntestModNode x3" ); //
	}

	if( modNodeGetSaddrByMac( (u8 *)pNodeErrMac, &saddr ) == TRUE )
	{
		dprintf( "\r\ntestModNode x4" ); //
	}



	//-----------------------------------------------
	dprintf( "\r\n  cnt=%d", modNodeCntGet()  ); 

	

	//-----------------------------------------------
	
	if( modNodeDelByMac( (u8 *)pNode3Mac ) == TRUE )
	{
		dprintf( "\r\ntestModNode del ok" ); //
	}

	
	dprintf( "\r\n  cnt=%d", modNodeCntGet()  ); 

	
	
	if( modNodeDelByMac( (u8 *)pNodeErrMac ) == TRUE )
	{
		dprintf( "\r\ntestModNode del ERR" ); //
	}

	
	if( modNodeMacIsNode( (u8 *)pNode3Mac ) == TRUE )
	{
		dprintf( "\r\ntestModNode x5" ); //
	}


	
}


#endif


#endif


