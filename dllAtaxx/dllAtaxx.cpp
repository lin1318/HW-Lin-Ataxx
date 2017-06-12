// dllAtaxx.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "dllAtaxx.h"


// 这是导出变量的一个示例
DLLATAXX_API int ndllAtaxx=0;

// 这是导出函数的一个示例。
DLLATAXX_API int fndllAtaxx(void)
{
    return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 dllAtaxx.h
CdllAtaxx::CdllAtaxx()
{
    return;
}

void CdllAtaxx::helpsearch() {
	fx = 0; fy = 0; tx = 0; ty = 0;
}
bool  CdllAtaxx::check(int player, int board[7][7]) {
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
bool  CdllAtaxx::validmove(int x, int y, int xi, int yi, int player, int chessboard[7][7]) {
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
void  CdllAtaxx::moving(int x, int y, int player, int chessboard[7][7]) {
	int k, x1, y1;
	chessboard[x][y] = player;
	for (k = 0; k < 8; k++) {
		x1 = x + moveway1[k][0];
		y1 = y + moveway1[k][1];
		if (x1 >= 0 && x1 < 7 && y1 >= 0 && y1 < 7 && chessboard[x1][y1] != 0)
			chessboard[x1][y1] = player;
	}
}
int  CdllAtaxx::getfx() {
	return fx;
}
int  CdllAtaxx::getfy() {
	return fy;
}
int  CdllAtaxx::gettx() {
	return tx;
}
int  CdllAtaxx::getty() {
	return ty;
}
bool  CdllAtaxx::checkmove(int x, int y, int player, int chessboard[7][7]) {
	int k;
	bool flag = true;
	for (k = 0; k<8; k++)
		if (validmove(x, y, x + moveway1[k][0], y + moveway1[k][1], player, chessboard)) {
			flag = false;
			return flag;
		}
	return flag;
}
double  CdllAtaxx::evaluate(int chessboard[7][7]) {
	int i, j;
	double k = 1.0;
	double score = 0.0;
	for (i = 0; i<7; i++)
		for (j = 0; j<7; j++)
			if (chessboard[i][j] == black) {
				score -= k;
				if (checkmove(i, j, black, chessboard)) {
					score -= (k / 2);
				}
			}
			else
				if (chessboard[i][j] == white) {
					score += k;
					if (checkmove(i, j, white, chessboard)) {
						score += (k / 2);
					}
				}
	return score;
}
double  CdllAtaxx::alphabeta(int chessboard[7][7], int depth, double alpha, double beta, int player) {
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
							if (depth < 4)
								v = min(v, alphabeta(chessboard, depth - 1, alpha, beta, 3 - player));
							else {
								p = alphabeta(chessboard, depth - 1, alpha, beta, 3 - player);
								if (v > p) {
									v = p;
									fx = x; fy = y;
									tx = xi; ty = yi;
								}
							}
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
							if (depth < 4)
								v = min(v, alphabeta(chessboard, depth - 1, alpha, beta, 3 - player));
							else {
								p = alphabeta(chessboard, depth - 1, alpha, beta, 3 - player);
								if (v > p) {
									v = p;
									fx = x; fy = y;
									tx = xi; ty = yi;
								}
							}
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