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

#ifndef _F_TXT_FRAME_H
#define _F_TXT_FRAME_H


#include "com_typedef.h"

#include "f_frame_comm.h"

#include "f_txt_frame_data.h"

/*
����֡��ʽ���汾�ţ�0��			
----------------------------------------------------------------------------------
���	֡��Ա��	�ֽ���	����
----------------------------------------------------------------------------------
D1		֡��ʼ		1		ֵ��0xAA��
D2		֡����		1		֡�����ֽ�����
D3		֡�汾		1		֡��ʽ�İ汾�š�
D4		֡��Ϊ		1		֡�Ĳ�����Ϊ������
D5		У���		1		����֡���ݰ��޷��������ֽ��ۼӣ����������
D6		Ŀ��ID		8		��ƷID��
D7		�ỰID		1		�������½ڵ�������
D8	    ������	    1	    1�����ݰ�  2��Э���
D9		    ��		n		��Լ�� n < 230��
D10		֡����		1		ֵ��0x88��
----------------------------------------------------------------------------------*/



//------------------------------------------------------
#define  TXT_FRAME_ELE_LEN_HEAD       (1)
#define  TXT_FRAME_ELE_LEN_LEN        (1)
#define  TXT_FRAME_ELE_LEN_VER        (1)
#define  TXT_FRAME_ELE_LEN_ACTION     (1)
#define  TXT_FRAME_ELE_LEN_CHECK      (1)
#define  TXT_FRAME_ELE_LEN_TARGET_ID  (8)
#define  TXT_FRAME_ELE_LEN_SID        (1)
#define  TXT_FRAME_ELE_LEN_PACK_TYPE  (1)
//#define  TXT_FRAME_ELE_LEN_PACK     (N)
#define  TXT_FRAME_ELE_LEN_TAIL       (1)



//------------------------------------------------------


#define TXT_FRAME_LEN_CONST_ELE  ( TXT_FRAME_ELE_LEN_HEAD + TXT_FRAME_ELE_LEN_LEN + TXT_FRAME_ELE_LEN_VER + \
	                               TXT_FRAME_ELE_LEN_ACTION + TXT_FRAME_ELE_LEN_CHECK + TXT_FRAME_ELE_LEN_TARGET_ID + \
	                               TXT_FRAME_ELE_LEN_SID + TXT_FRAME_ELE_LEN_PACK_TYPE + TXT_FRAME_ELE_LEN_TAIL )
	                               

#define TXT_FRAME_LEN_MIN  ( TXT_FRAME_LEN_CONST_ELE + DPACK_LEN_MIN )

	                    

#define TXT_FRAME_LEN_MAX  (252)


//------------------------------------------------------
#define TXT_FRAME_OFFSET_HEAD          (0)
#define TXT_FRAME_OFFSET_LEN           (TXT_FRAME_OFFSET_HEAD      + TXT_FRAME_ELE_LEN_HEAD)
#define TXT_FRAME_OFFSET_VER           (TXT_FRAME_OFFSET_LEN       + TXT_FRAME_ELE_LEN_LEN)
#define TXT_FRAME_OFFSET_ACTION        (TXT_FRAME_OFFSET_VER       + TXT_FRAME_ELE_LEN_VER)
#define TXT_FRAME_OFFSET_CHECK         (TXT_FRAME_OFFSET_ACTION    + TXT_FRAME_ELE_LEN_ACTION)
#define TXT_FRAME_OFFSET_TARGET_ID     (TXT_FRAME_OFFSET_CHECK     + TXT_FRAME_ELE_LEN_CHECK)
#define TXT_FRAME_OFFSET_SID           (TXT_FRAME_OFFSET_TARGET_ID + TXT_FRAME_ELE_LEN_TARGET_ID)
#define TXT_FRAME_OFFSET_PACK_TYPE     (TXT_FRAME_OFFSET_SID       + TXT_FRAME_ELE_LEN_SID)
#define TXT_FRAME_OFFSET_PACK          (TXT_FRAME_OFFSET_PACK_TYPE + TXT_FRAME_ELE_LEN_PACK_TYPE)
//#define TXT_FRAME_OFFSET_TAIL          (TXT_FRAME_OFFSET_PACK       + 4) //


#define  TXT_FRAME_VER_ENC_BIT                 (0x80) // ֡�ļ���λ
#define  TXT_FRAME_VER_COMM_TERMINAL_BIT       (0x40) // ͨ�Ŷ˱�־ Communication terminal flag   1:�ڵ������� 0:�ڵ��������
#define  TXT_FRAME_VER_BIT_MASK                ( TXT_FRAME_VER_ENC_BIT | TXT_FRAME_VER_COMM_TERMINAL_BIT )


//------------------------------------------------------
#define TXT_FRAME_START  (0xAA)
#define TXT_FRAME_END    (0x88)

#define TXT_FRAME_VER_01    (0x01) // ������
//#define TXT_FRAME_VER_02    (0x02) //






extern U8 txtFrameHeadIsOk( u8 head );


extern u8 txtFrameTailIsOk( u8 tail );


extern u8 txtFrameVerIsOk( u8 ver );

extern u8 txtFrameVerIsEnc( u8 ver );
extern void txtFrameEncBitSet( u8 *pVer );
extern void txtFrameEncBitClear( u8 *pVer );

extern u8 txtFrameLenIsOk( u8 len );


extern u8 txtFrameActionIsOk( u8 action );



extern u8 txtFramePackTypeIsOk( u8 type );




extern u8 txtFramePackTypeIsD( u8 type );// data pack



extern u8 txtFramePackTypeIsP( u8 type );// protocol pack



extern u8 txtFrameCheckGet( u8 *pFrame );


extern u8 txtFrameCheckIsOk( u8 *pFrame );




//��֡����ʱ���Ƿ�ظ�
extern u8 txtFrameOnErrIsToRsp( u8 *pFrame, u8 len );


/* ********************* ����֡�ǲ���͸��  ****************************  
-----------------------------------------------------------------------
	ͨ�Ŷ˱�־ ��� �� 1, ���� �ڵ�������ͨ��, ����͸��
-----------------------------------------------------------------------
	ͨ�Ŷ˱�־ ��� �� 0, ���� �ڵ��������ͨ��, ��͸��
-----------------------------------------------------------------------
*/
extern u8 txtFrameIsPass( u8 *pFrame, u8 len );

//extern u8 txtFrameIsEnc( u8 *pFrame, u8 len );


extern EN_FRAME_UNPACK txtFrameUnpackHeadNotMac( u8 *pFrame, u8 len );


extern EN_FRAME_UNPACK txtFrameUnpackNotMac( u8 *pFrame, u8 len );


// ���� txtFrame
extern EN_FRAME_UNPACK txtFrameUnpack( u8 *pFrame, u8 len, u8 isNode );







/*
����֡��ʽ���汾�ţ�0��			
----------------------------------------------------------------------------------
���	֡��Ա��	�ֽ���	����
----------------------------------------------------------------------------------
D1		֡��ʼ		1		ֵ��0xAA��
D2		֡����		1		֡�����ֽ�����
D3		֡�汾		1		֡��ʽ�İ汾�š�
D4		֡��Ϊ		1		֡�Ĳ�����Ϊ������
D5		У���		1		����֡���ݰ��޷��������ֽ��ۼӣ����������
D6		Ŀ��ID		8		��ƷID��
D7		�ỰID		1		�������½ڵ�������
D8	    ������	    1	    1�����ݰ�  2��Э���
D9		    ��		n		��Լ�� n < 230��
D10		֡����		1		ֵ��0x88��
----------------------------------------------------------------------------------*/
// in : dpack is OK
extern u8 txtFrameCreateG2S( EN_TXT_FRAME_ACTION action, u8 sid, ST_FRAME  *pFrame );



extern u8 txtFrameCreateG2N( EN_TXT_FRAME_ACTION action, u8 sid, ST_FRAME  *pFrame );


#endif

#endif


