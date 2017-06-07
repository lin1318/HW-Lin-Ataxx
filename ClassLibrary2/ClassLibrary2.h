// ClassLibrary2.h

#pragma once
#include "dllsearch.h"
#include<algorithm>
#include<cmath>	
using namespace System;

namespace ClassLibrary2 {

	public ref class wrapper
	{
	public:
		wrapper() { ptr = new Cdllsearch; }
		~wrapper() { this->!wrapper(); }
		!wrapper() { delete ptr; }
		double evaluate(int chessboard[7][7]) {
			return ptr->evaluate(chessboard);
		}
		double alphabeta(int chessboard[7][7], int depth, double alpha, double beta, int player) {
			return ptr->alphabeta(chessboard, depth, alpha, beta, player);
		}
	private:
		Cdllsearch *ptr;
	};
}
