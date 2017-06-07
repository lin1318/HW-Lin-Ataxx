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
using namespace std;
// 此类是从 dllAtaxx.dll 导出的
class DLLATAXX_API CdllAtaxx {
public:
	CdllAtaxx(void);
	// TODO:  在此添加您的方法。
    void helpsearch() {
		for (int i = 0; i < 7; i++)
			for (int j = 0; j < 7; j++)
				board[i][j] = 0;
		board[0][0] = black;
		board[0][6] = white;
		board[6][0] = white;
		board[6][6] = black;
	}
	bool check(int player) {
		int i, j, x, y, k, x1, y1;
		bool flag = true;
		for (i = 0; i < 7; i++)
			for (j = 0; j < 7; j++)
				if (board[i][j] == player) {
					x = i; y = j;
					for (k = 0; k < 8; k++) {
						x1 = x + moveway1[k][0];
						y1 = y + moveway1[k][1];
						if (x1 >= 0 && x1 < 7 && y1 >= 0 && y1 < 7 && board[x1][y1] == 0)
							return false;
					}
					for (k = 0; k < 16; k++) {
						x1 = x + moveway2[k][0];
						y1 = y + moveway2[k][1];
						if (x1 >= 0 && x1 < 7 && y1 >= 0 && y1 < 7 && board[x1][y1] == 0)
							return false;
					}
				}
		return flag;
	}
	bool validmove(int x, int y, int xi, int yi, int player, int chessboard[7][7]) {
		if (x < 0 || x>6 || y < 0 || y>6 || xi < 0 || xi>6 || yi < 0 || yi>6)
			return false;
		if (chessboard[xi][yi] != 0)
			return false;
		if (chessboard[x][y] != player)
			return false;
		if (max(abs(x - xi), abs(y - yi)) > 2)
			return false;
		if (x == xi&&y == yi)
			return false;
		return true;
	}
	void moving(int x, int y, int player, int chessboard[7][7]) {
		int k, x1, y1;
		chessboard[x][y] = player;
		for (k = 0; k < 8; k++) {
			x1 = x + moveway1[k][0];
			y1 = y + moveway1[k][1];
			if (x1 >= 0 && x1 < 7 && y1 >= 0 && y1 < 7 && chessboard[x1][y1] != 0)
				chessboard[x1][y1] = player;
		}
	}
	int getfx() {
		return fx;
	}
	int getfy() {
		return fy;
	}
	int gettx() {
		return tx;
	}
	int getty() {
		return ty;
	}
	bool checkmove(int x, int y, int player, int chessboard[7][7]) {
		int k;
		bool flag = true;
		for (k = 0; k<8; k++)
			if (validmove(x, y, x + moveway1[k][0], y + moveway1[k][1], player, chessboard)) {
				flag = false;
				return flag;
			}
		return flag;
	}
public:
	const int black = 1, white = 2;
	int fx, fy, tx, ty, board[7][7];
	const int moveway1[8][2] = { { 1,0 },{ 0,1 },{ -1,0 },{ -1,1 },{ 1,1 },{ 1,-1 },{ 0,-1 },{ -1,-1 } };
	const int moveway2[16][2] = { { -2,-2 },{ -2,-1 },{ -2,0 },{ -2,1 },{ -2,2 },{ -1,-2 },{ -1,2 },{ 0,-2 },{ 0,2 },{ 1,-2 },{ 1,2 },{ 2,-2 },{ 2,-1 },{ 2,0 },{ 2,1 },{ 2,2 } };
};

extern DLLATAXX_API int ndllAtaxx;

DLLATAXX_API int fndllAtaxx(void);
