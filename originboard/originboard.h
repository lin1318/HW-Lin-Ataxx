// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ORIGINBOARD_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ORIGINBOARD_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef ORIGINBOARD_EXPORTS
#define ORIGINBOARD_API __declspec(dllexport)
#else
#define ORIGINBOARD_API __declspec(dllimport)
#endif

// �����Ǵ� originboard.dll ������
class ORIGINBOARD_API Coriginboard {
public:
	Coriginboard(void);
	virtual void alphabeta() {

	}
	virtual void evaluate() {

	}
	// TODO:  �ڴ�������ķ�����
};

extern ORIGINBOARD_API int noriginboard;

ORIGINBOARD_API int fnoriginboard(void);
