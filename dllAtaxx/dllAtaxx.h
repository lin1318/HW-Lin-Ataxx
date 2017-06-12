// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DLLATAXX_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// DLLATAXX_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef DLLATAXX_EXPORTS
#define DLLATAXX_API __declspec(dllexport)
#else
#define DLLATAXX_API __declspec(dllimport)
#endif
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<windows.h>
#include ".\originboard.h"
using namespace std;
// �����Ǵ� dllAtaxx.dll ������
class DLLATAXX_API CdllAtaxx:public Coriginboard {
public:
	CdllAtaxx(void);
	// TODO:  �ڴ�������ķ�����
	void helpsearch();
	bool check(int player, int board[7][7]);
	bool validmove(int x, int y, int xi, int yi, int player, int chessboard[7][7]); 
	int getfx();
	int getfy();
	int gettx();
	int getty();
	void  moving(int x, int y, int player, int chessboard[7][7]);
	bool checkmove(int x, int y, int player, int chessboard[7][7]); 
	double evaluate(int chessboard[7][7]); 
	double alphabeta(int chessboard[7][7], int depth, double alpha, double beta, int player); 
public:
	const int black = 1, white = 2;
	int fx, fy, tx, ty;
	const int moveway1[8][2] = { { 1,0 },{ 0,1 },{ -1,0 },{ -1,1 },{ 1,1 },{ 1,-1 },{ 0,-1 },{ -1,-1 } };
	const int moveway2[16][2] = { { -2,-2 },{ -2,-1 },{ -2,0 },{ -2,1 },{ -2,2 },{ -1,-2 },{ -1,2 },{ 0,-2 },{ 0,2 },{ 1,-2 },{ 1,2 },{ 2,-2 },{ 2,-1 },{ 2,0 },{ 2,1 },{ 2,2 } };
};
extern DLLATAXX_API int ndllAtaxx;

DLLATAXX_API int fndllAtaxx(void);
