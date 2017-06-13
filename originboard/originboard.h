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
	Coriginboard(int w, int l);
	 int evaluate();
	 int alphabeta(int player, int depth, int alpha, int beta);
	 void reset();
	// TODO:  �ڴ�������ķ�����
private:
	int testboard[20][20];
	int bw, bl;
};

extern ORIGINBOARD_API int noriginboard;

ORIGINBOARD_API int fnoriginboard(void);
