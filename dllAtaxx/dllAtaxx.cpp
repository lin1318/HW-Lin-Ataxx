// dllAtaxx.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "dllAtaxx.h"


// ���ǵ���������һ��ʾ��
DLLATAXX_API int ndllAtaxx=0;

// ���ǵ���������һ��ʾ����
DLLATAXX_API int fndllAtaxx(void)
{
    return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� dllAtaxx.h
CdllAtaxx::CdllAtaxx()
{
    return;
}
