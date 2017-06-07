// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DLLSEARCH_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// DLLSEARCH_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef DLLSEARCH_EXPORTS
#define DLLSEARCH_API __declspec(dllexport)
#else
#define DLLSEARCH_API __declspec(dllimport)
#endif
#include "dllAtaxx.h"
#include<algorithm>
#include<cmath>
using namespace std;
// �����Ǵ� dllsearch.dll ������
class DLLSEARCH_API Cdllsearch:public CdllAtaxx {
public:
	Cdllsearch(void);
	// TODO:  �ڴ�������ķ�����
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
