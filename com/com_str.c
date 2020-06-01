/*--------------------------------------------------------------|
 *| company | ���ϻ�����ľ�ƿƼ����޹�˾                        |
 *|-------------------------------------------------------------|
 *| date    | 2019-09-20                                        |
 *|-------------------------------------------------------------|
 *| author  | ��  ��                                            |
 *|-------------------------------------------------------------|
 *| contact | QQ:258820709    email:fenghuibox@qq.com           |
 *|-------------------------------------------------------------*/
 

#include "com_typedef.h"



// ����ֵ��

// �ɹ�ʱ���������سɹ����Ĳ����б��е���Ŀ���� �����������ƥ��Ԥ�ڵ���Ŀ������

// ��ƥ��ʧ�ܵ�����¿���С�� - ����Ϊ�㡣

// ���κ����ݿɱ��ɹ�����֮ǰ����ʧ�ܵ�����£�����FAIL(-1)��
int strScanf(const char *pStr, const char *pFormat, ...)
{
    va_list args;
    int cnt;

    if( pStr == NULL || pFormat == NULL )
    	return FAIL;

    va_start(args, pFormat);
    cnt = vsscanf(pStr, pFormat, args);
    va_end(args);

    return cnt;
}









void strPrintfBuf(u8 *pOutBuf, u32 bufLen, const char *pFormat, ...)
{
	//char buffer[256];
	va_list args;
	
	va_start (args, pFormat);
	vsnprintf ((char *)pOutBuf, bufLen, pFormat, args);
	//perror (buffer);
	va_end (args);

}



