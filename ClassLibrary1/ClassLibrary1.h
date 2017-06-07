// ClassLibrary1.h

#pragma once
#include "dllAtaxx.h"
#include<algorithm>
#include<cmath>	
using namespace System;
namespace ClassLibrary1 {
	public ref class wrapper {
	public:
		wrapper() { ptr = new CdllAtaxx; }
		~wrapper() { this->!wrapper(); }
		!wrapper() { delete ptr; }
		void helpsearch() {
			return ptr->helpsearch();
		}
		bool validmove(int x, int y, int xi, int yi, int player, int chessboard[7][7]) {
			return ptr->validmove(x,y,xi,yi,player,chessboard);
		}
		bool check(int player) {
			return ptr->check(player);
		}
		int getfx() {
			return ptr->getfx();
		}
		int getfy() {
			return ptr ->getfy();
		}
		int gettx() {
			return ptr->gettx();
		}
		int getty() {
			return ptr->getty();
		}
		void moving(int x, int y, int player, int chessboard[7][7]) {
			return ptr->moving(x,y,player,chessboard);
		}
		bool checkmove(int x, int y, int player, int chessboard[7][7]) {
			return ptr->checkmove(x, y, player, chessboard);
		}
		double evaluate(int chessboard[7][7]) {
			return ptr->evaluate(chessboard);
		}
		double alphabeta(int chessboard[7][7], int depth, double alpha, double beta, int player) {
			return ptr->alphabeta(chessboard, depth, alpha, beta, player);
		}
	private:
		CdllAtaxx *ptr;
	};
}
