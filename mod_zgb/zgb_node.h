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
#ifndef __ZGB_NODE_H
#define __ZGB_NODE_H


#include "com_typedef.h"

//#include "f_frame_comm.h"


//#define RST_NOT_SEARCH  (-1)

//-------------------------------------------------------------------------------
#define NODE_CNT   (60)



typedef struct
{
	u8 pMac[MAC_ADDR_LEN];
	u16 saddr; // short addr
}ST_NODE_ADDR;



// ----------------- 可 调节的参数 -------------------------------------------------------
#define NODE_ACTIVE_VAL_UPDATE_GAP     (1)  // 节点的活跃值 更新 间隔  单位: 秒
#define NODE_ACTIVE_VAL_VALID_GAP_SEC  (10) // 收到节点数据后的 此 时间内，认为 此节点有效

// ----------------- 不可 调节的参数 -------------------------------------------------------
#define NODE_ACTIVE_VAL_MAX         (255) // 节点的活跃值的最大值
#define NODE_ACTIVE_VAL_VALID       ( NODE_ACTIVE_VAL_MAX - NODE_ACTIVE_VAL_VALID_GAP_SEC / NODE_ACTIVE_VAL_UPDATE_GAP ) // 大于此值时，认为有效 


#define   BIT_G2N_SET_KEY  (1) // gateway send node cmd bit setkey
//#define BIT_G2N_GET_KEY  (2) // 

#define BIT_G2N_SET_AES_SWITCH    (4) // 
//#define BIT_G2N_GET_AES_SWITCH  (8) // 


#define BIT_G2N_RSP_ACK  (0x10) // gateway send node  rsp ack



#define BIT_G2N__MASK_INIT   ( BIT_G2N_SET_KEY | BIT_G2N_SET_AES_SWITCH  ) 
#define BIT_G2N__MASK        ( BIT_G2N_SET_KEY | BIT_G2N_SET_AES_SWITCH | BIT_G2N_RSP_ACK )


typedef struct
{
	u8 pMac[MAC_ADDR_LEN];  // 主键  节点的mac地址 
	
	u16 saddr;              // 节点的 短地址( short addr )
	
	//u8 pKey[12];            // 节点上 的 aes key
	
	u8 active;              // 节点的活跃值 越大越好，当收到节点数据时，更新为255，每1秒减1，最小为0
	
	//u8 isLoad;            // load之前为0 load后值如有些NODE 就值 1
	u8 sendCmdBit;          // BIT_G2N__MASK
}ST_NODE;





typedef  void ( *FunNodeTraversalCB)( ST_NODE *pNode ); 






//------ 查找 MAC地址 对应 的短地址  ------------------------------------
/*
in: pMac

out: pSaddr

result:  TRUE : 查找到节点  FALSE: 没有查找到节点
*/
extern u8 modNodeGetSaddrByMac( u8 *pMac, u16 *pSaddr );


//-------------------------------------------------------------------------------
/*
result:
   TRUE : 是网关的节点
   FALSE: 不是网关的节点
*/
extern int modNodeMacIsNode( u8 *pMac );


//------del-------------------------------------------------
extern int modNodeDelByMac( u8 *pMac );


//-------------------------------------------------------------------------------
/*
用于装载网关的节点

收到 查询主机模块存储的从机信息命令 的结果后，直接调用此函数
*/
extern void modNodeLoad( u8 cnt, ST_NODE_ADDR *pNodeSAddr );



/*
------pNodeBuf----------------------------------
         nodeCnt  startId   getCnt  pNodeMac
------------------------------------------------
  len:    1byte    1byte    1byte   8byte * n 
------------------------------------------------
  value:  1- n     1- n     0- n
------------------------------------------------
返回值: 总的字节数
*/
extern u8 modNodeGet(u8 *pNodeBuf );

extern void modNodeStartIdSet( u8 startId );

//-------------------------------------------------------------------------------
extern void modNodeClear( void );


/* ***********************************
  1 接收到了正确的数据帧
  2 提取MAC
  3 调用 此函数
************************************* */
extern void modNodeUpdate( u8 *pMac );

extern u8 modNodeIsHaveG2Ncmd( void );

extern u8 modNodeIsHaveG2NcmdRsp( u8 index );


//--------------------------------------------------------
extern u8 modNodeIsHaveG2NcmdSetKey( u8 index );

extern u8 modNodeG2NcmdSetKeyBitSet( u8 index );

extern u8 modNodeG2NcmdSetKeyBitClear( u8 index );


//--------------------------------------------------------
extern u8 modNodeIsHaveG2NcmdSetAesSwitch( u8 index );

extern u8 modNodeG2NcmdSetAesSwitchBitSet( u8 index );

extern u8 modNodeG2NcmdSetAesSwitchBitClear( u8 index );


//--------------------------------------------------------

/*
返回有命令要发送的节点中，最活跃的节点的下标, 没有时返回 -1
*/
extern int modNodeGetMaxActiveNodeIndex( void );


extern u8 modNodeGetSaddrByIndex( u8 index, u16 *pSaddr );


extern u8 modNodeGetMacByIndex( u8 index, u8 *pMac );


extern void zgbNodeInit( void );



#ifdef TEST_ZGB_NODE

	extern void testZgbNode( void );

#endif


#endif



#endif

