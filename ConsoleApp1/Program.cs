using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClassLibrary1;
namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            ClassLibrary1.wrapper searcher;
            searcher = new ClassLibrary1.wrapper();
            int[,] board = new int[7, 7];
            int fx, fy, tx, ty;
            string ans = ".0X";
            board[0, 0] = 1;
            board[6, 6] = 1;
            board[0, 6] = 2;
            board[6, 0] = 2;
            searcher.helpsearch();
            int player = 1;
            int times = 0;
            while (times<4)
            {
                searcher.alphabeta(board, 4, 999999.9, -999999.9, player);
                fx = searcher.getfx();
                fy = searcher.getfy();
                tx = searcher.gettx();
                ty = searcher.getty();
                int way = Math.Max(Math.Abs(fx - tx), Math.Abs(tx - ty));
                if (way == 2)
                {
                    board[tx, ty] = 0;
                }
                searcher.moving(tx, ty, player, ref board);
                for (int i = 0; i < 7; i++)
                {
                    for (int j = 0; j < 7; j++)
                    {
                        Console.Write(ans[board[i, j]] + "  ");
                    }
                    Console.WriteLine();
                }
                Console.WriteLine();
                player = 3 - player;
                times++;
            }
        }
    }
}
