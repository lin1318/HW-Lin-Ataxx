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
		bool validmove(int x, int y, int xi, int yi, int player, cli::array<int,2>^ cboard) {
			int chessboard[7][7];
			for (int i = 0; i < 7; i++)
				for (int j = 0; j < 7; j++)
					chessboard[i][j] = cboard[i,j];
			return ptr->validmove(x,y,xi,yi,player,chessboard);
		}
		bool check(int player, cli::array<int, 2>^ cboard) {
			int chessboard[7][7];
			for (int i = 0; i < 7; i++)
				for (int j = 0; j < 7; j++)
					chessboard[i][j] = cboard[i, j];
			return ptr->check(player,chessboard);
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
		void moving(int x, int y, int player, cli::array<int, 2>^% cboard) {
			int chessboard[7][7];
			for (int i = 0; i < 7; i++)
				for (int j = 0; j < 7; j++)
					chessboard[i][j] = cboard[i, j];
			   ptr->moving(x,y,player,chessboard);
			   for (int i = 0; i < 7; i++)
				   for (int j = 0; j < 7; j++)
					   cboard[i, j]=chessboard[i][j];
		}
		bool checkmove(int x, int y, int player, cli::array<int, 2>^ cboard) {
			int chessboard[7][7];
			for (int i = 0; i < 7; i++)
				for (int j = 0; j < 7; j++)
					chessboard[i][j] = cboard[i, j];
			return ptr->checkmove(x, y, player, chessboard);
		}
		double evaluate(cli::array<int, 2>^ cboard) {
			int chessboard[7][7];
			for (int i = 0; i < 7; i++)
				for (int j = 0; j < 7; j++)
					chessboard[i][j] = cboard[i, j];
			return ptr->evaluate(chessboard);
		}
		double alphabeta(cli::array<int, 2>^ cboard, int depth, double alpha, double beta, int player) {
			int chessboard[7][7];
			for (int i = 0; i < 7; i++)
				for (int j = 0; j < 7; j++)
					chessboard[i][j] = cboard[i, j];
			return ptr->alphabeta(chessboard, depth, alpha, beta, player);
		}
	private:
		CdllAtaxx *ptr;
	};
}
