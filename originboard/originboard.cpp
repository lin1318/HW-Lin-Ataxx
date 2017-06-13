// originboard.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "originboard.h"
#include<algorithm>
using namespace std;
// 这是导出变量的一个示例
ORIGINBOARD_API int noriginboard=0;

// 这是导出函数的一个示例。
ORIGINBOARD_API int fnoriginboard(void)
{
    return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 originboard.h
Coriginboard::Coriginboard()
{
	bw = 15; bl = 15;
	reset();
    return;
}
Coriginboard::Coriginboard(int w,int l)
{
	bw = w; bl = l;
	reset();
	return;
}

void Coriginboard::reset() {
	for (int i = 0; i < bl; i++)
		for (int j = 0; j < bw; j++)
			testboard[i][j] = 0;
}
int Coriginboard::alphabeta(int player, int depth, int alpha, int beta) {
	int v;
	if (depth == 0)
		return evaluate();
	if (player == 1) {
		v = 0x7ffffff;
		for(int i=1;i<bl-1;i++)
			for (int j = 1; j < bw - 1; j++)
			{
				v = max(v, alphabeta(1 - player, depth - 1, alpha, beta));
				alpha = max(v, alpha);
				if (beta <= alpha)
					break;
			}
	}
	else {
		v = -0x7ffffff;
		for(int i=1;i<bl-1;i++)
			for (int j = 1; j < bw - 1; j++) {
				v = min(v, alphabeta(1 - player, depth - 1, alpha, beta));
				beta = min(v, beta);
				if (beta <= alpha)
					break;
			}
	}
	return v;
}
int Coriginboard::evaluate() {
	int score = 0;
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			score++;
	return score;
}
