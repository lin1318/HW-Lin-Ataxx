// dllsearch.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "dllsearch.h"


// ���ǵ���������һ��ʾ��
DLLSEARCH_API int ndllsearch=0;

// ���ǵ���������һ��ʾ����
DLLSEARCH_API int fndllsearch(void)
{
    return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� dllsearch.h
Cdllsearch::Cdllsearch()
{
    return;
}
