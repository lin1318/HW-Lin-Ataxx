// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 DLLSEARCH_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// DLLSEARCH_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef DLLSEARCH_EXPORTS
#define DLLSEARCH_API __declspec(dllexport)
#else
#define DLLSEARCH_API __declspec(dllimport)
#endif
#include "dllAtaxx.h"
#include<algorithm>
#include<cmath>
using namespace std;
// 此类是从 dllsearch.dll 导出的
class DLLSEARCH_API Cdllsearch:public CdllAtaxx {
public:
	Cdllsearch(void);
	// TODO:  在此添加您的方法。
	double evaluate(int chessboard[7][7]) {
		int i, j;
		double score = 0.0;
		for (i = 0; i<7; i++)
			for (j = 0; j<7; j++)
				if (chessboard[i][j] == black) {
					score--;
					if (checkmove(i, j, black, chessboard)) {
						score -= 0.5;
					}
				}
				else
					if (chessboard[i][j] == white) {
						score++;
						if (checkmove(i, j, white, chessboard)) {
							score += 0.5;
						}
					}
		return score;
	}
	double alphabeta(int chessboard[7][7], int depth, double alpha, double beta, int player) {
		int i, j, k, x, y, xi, yi;
		double v, p;
		int originboard[7][7];
		for (i = 0; i < 7; i++)
			for (j = 0; j < 7; j++)
				originboard[i][j] = chessboard[i][j];
		if (depth == 0)
			return evaluate(chessboard);
		if (player == white) {
			v = -99999999.9;
			for (i = 0; i<7; i++)
				for (j = 0; j<7; j++)
					if (chessboard[i][j] == white) {
						x = i; y = j;
						for (k = 0; k < 8; k++) {
							xi = x + moveway1[k][0];
							yi = y + moveway1[k][1];
							if (validmove(x, y, xi, yi, player, chessboard)) {
								moving(xi, yi, white, chessboard);
								if (depth < 4)
									v = max(v, alphabeta(chessboard, depth - 1, alpha, beta, 3 - player));
								else {
									p = alphabeta(chessboard, depth - 1, alpha, beta, 3 - player);
									if (v < p) {
										v = p;
										fx = x; fy = y;
										tx = xi; ty = yi;
									}
								}
								alpha = max(v, alpha);
								for (int i1 = 0; i1 < 7; i1++)
									for (int j1 = 0; j1 < 7; j1++)
										chessboard[i1][j1] = originboard[i1][j1];
								if (beta <= alpha)
									break;
							}
						}
						for (k = 0; k < 16; k++) {
							xi = x + moveway2[k][0];
							yi = y + moveway2[k][1];
							if (validmove(x, y, xi, yi, player, chessboard)) {
								moving(xi, yi, white, chessboard);
								chessboard[x][y] = 0;
								if (depth < 4)
									v = max(v, alphabeta(chessboard, depth - 1, alpha, beta, 3 - player));
								else {
									p = alphabeta(chessboard, depth - 1, alpha, beta, 3 - player);
									if (v < p) {
										v = p;
										fx = x; fy = y;
										tx = xi; ty = yi;
									}
								}
								alpha = max(v, alpha);
								for (int i1 = 0; i1 < 7; i1++)
									for (int j1 = 0; j1 < 7; j1++)
										chessboard[i1][j1] = originboard[i1][j1];
								if (beta <= alpha)
									break;
							}
						}
					}
			return v;
		}
		else {
			v = 99999999.9;
			for (i = 0; i<7; i++)
				for (j = 0; j<7; j++)
					if (chessboard[i][j] == black) {
						x = i; y = j;
						for (k = 0; k < 8; k++) {
							xi = x + moveway1[k][0];
							yi = y + moveway1[k][1];
							if (validmove(x, y, xi, yi, player, chessboard)) {
								moving(xi, yi, black, chessboard);
								v = min(v, alphabeta(chessboard, depth - 1, alpha, beta, 3 - player));
								beta = min(v, beta);
								for (int i1 = 0; i1 < 7; i1++)
									for (int j1 = 0; j1 < 7; j1++)
										chessboard[i1][j1] = originboard[i1][j1];
								if (beta <= alpha)
									break;
							}
						}
						for (k = 0; k < 16; k++) {
							xi = x + moveway2[k][0];
							yi = y + moveway2[k][1];
							if (validmove(x, y, xi, yi, player, chessboard)) {
								moving(xi, yi, black, chessboard);
								chessboard[x][y] = 0;
								v = min(v, alphabeta(chessboard, depth - 1, alpha, beta, 3 - player));
								beta = min(v, beta);
								for (int i1 = 0; i1 < 7; i1++)
									for (int j1 = 0; j1 < 7; j1++)
										chessboard[i1][j1] = originboard[i1][j1];
								if (beta <= alpha)
									break;
							}
						}
					}
			return v;
		}
	}
};

extern DLLSEARCH_API int ndllsearch;

DLLSEARCH_API int fndllsearch(void);
