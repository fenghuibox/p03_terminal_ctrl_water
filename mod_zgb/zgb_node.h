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



// ----------------- �� ���ڵĲ��� -------------------------------------------------------
#define NODE_ACTIVE_VAL_UPDATE_GAP     (1)  // �ڵ�Ļ�Ծֵ ���� ���  ��λ: ��
#define NODE_ACTIVE_VAL_VALID_GAP_SEC  (10) // �յ��ڵ����ݺ�� �� ʱ���ڣ���Ϊ �˽ڵ���Ч

// ----------------- ���� ���ڵĲ��� -------------------------------------------------------
#define NODE_ACTIVE_VAL_MAX         (255) // �ڵ�Ļ�Ծֵ�����ֵ
#define NODE_ACTIVE_VAL_VALID       ( NODE_ACTIVE_VAL_MAX - NODE_ACTIVE_VAL_VALID_GAP_SEC / NODE_ACTIVE_VAL_UPDATE_GAP ) // ���ڴ�ֵʱ����Ϊ��Ч 


#define   BIT_G2N_SET_KEY  (1) // gateway send node cmd bit setkey
//#define BIT_G2N_GET_KEY  (2) // 

#define BIT_G2N_SET_AES_SWITCH    (4) // 
//#define BIT_G2N_GET_AES_SWITCH  (8) // 


#define BIT_G2N_RSP_ACK  (0x10) // gateway send node  rsp ack



#define BIT_G2N__MASK_INIT   ( BIT_G2N_SET_KEY | BIT_G2N_SET_AES_SWITCH  ) 
#define BIT_G2N__MASK        ( BIT_G2N_SET_KEY | BIT_G2N_SET_AES_SWITCH | BIT_G2N_RSP_ACK )


typedef struct
{
	u8 pMac[MAC_ADDR_LEN];  // ����  �ڵ��mac��ַ 
	
	u16 saddr;              // �ڵ�� �̵�ַ( short addr )
	
	//u8 pKey[12];            // �ڵ��� �� aes key
	
	u8 active;              // �ڵ�Ļ�Ծֵ Խ��Խ�ã����յ��ڵ�����ʱ������Ϊ255��ÿ1���1����СΪ0
	
	//u8 isLoad;            // load֮ǰΪ0 load��ֵ����ЩNODE ��ֵ 1
	u8 sendCmdBit;          // BIT_G2N__MASK
}ST_NODE;





typedef  void ( *FunNodeTraversalCB)( ST_NODE *pNode ); 






//------ ���� MAC��ַ ��Ӧ �Ķ̵�ַ  ------------------------------------
/*
in: pMac

out: pSaddr

result:  TRUE : ���ҵ��ڵ�  FALSE: û�в��ҵ��ڵ�
*/
extern u8 modNodeGetSaddrByMac( u8 *pMac, u16 *pSaddr );


//-------------------------------------------------------------------------------
/*
result:
   TRUE : �����صĽڵ�
   FALSE: �������صĽڵ�
*/
extern int modNodeMacIsNode( u8 *pMac );


//------del-------------------------------------------------
extern int modNodeDelByMac( u8 *pMac );


//-------------------------------------------------------------------------------
/*
����װ�����صĽڵ�

�յ� ��ѯ����ģ��洢�Ĵӻ���Ϣ���� �Ľ����ֱ�ӵ��ô˺���
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
����ֵ: �ܵ��ֽ���
*/
extern u8 modNodeGet(u8 *pNodeBuf );

extern void modNodeStartIdSet( u8 startId );

//-------------------------------------------------------------------------------
extern void modNodeClear( void );


/* ***********************************
  1 ���յ�����ȷ������֡
  2 ��ȡMAC
  3 ���� �˺���
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
����������Ҫ���͵Ľڵ��У����Ծ�Ľڵ���±�, û��ʱ���� -1
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

