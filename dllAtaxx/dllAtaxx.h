// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 DLLATAXX_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// DLLATAXX_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
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
// 此类是从 dllAtaxx.dll 导出的
class DLLATAXX_API CdllAtaxx:public Coriginboard {
public:
	CdllAtaxx(void);
	// TODO:  在此添加您的方法。
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
