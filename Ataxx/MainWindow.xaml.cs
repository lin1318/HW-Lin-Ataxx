using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Xml.Serialization;
using ClassLibrary1;
using System.Threading;
namespace Ataxx
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        private ClassLibrary1.wrapper invoke;
        int[,] board = new int[7, 7];
        int x, y, x1, y1;
        int click_times;
        private List<UIElement> visuals = new List<UIElement>();
        private int turn = 1;
        public MainWindow()
        {
            InitializeComponent();
            InitWindow();
        }
        void drawing()
        {
            for(int i=0;i<visuals.Count;++i)
                chessboard.Children.Remove(visuals[i]);
            visuals.Clear();
            for(int i=0;i<7;i++)
              for(int j=0;j<7;j++)
                    if(board[i,j]!=0)
                    {
                        System.Windows.Shapes.Ellipse circle;
                    circle = new System.Windows.Shapes.Ellipse()
                    {
                        Height = 50,
                        Width = 50
                    };
                        double left = -15-164*(3-j);
                        double top = -40-164*(3-i);
                        circle.Margin = new Thickness(left, top, 0, 0);
                    if (board[i, j] == 1)
                        circle.Fill = new SolidColorBrush(Colors.Black);
                    else
                    if (board[i, j] == 2)
                        circle.Fill = new SolidColorBrush(Colors.White);
                        chessboard.Children.Add(circle);
                        visuals.Add(circle);
                    }
        }
        public void winprinter()
        {

        }
        private async Task playbyAI()
        {
         /*   if (invoke.check(2, board))
            {
                winprinter();
            }*/
            Task<double> com;
            com = Task.Run(() =>invoke.alphabeta(board,4,-99999999.9,99999999.9,2));
            await com;
            var data=com.Result;
            int fx = invoke.getfx();
            int fy = invoke.getfy();
            int tx = invoke.gettx();
            int ty = invoke.getty();
            int way = Math.Max(Math.Abs(fx - tx), Math.Abs(fy - ty));
            if (way == 2)
                board[fx, fy] = 0;
            invoke.moving(tx, ty, 2, ref board);
            WhiteLabel.Content = "White: " +fx.ToString()+" "+fy.ToString()+" "+tx.ToString()+" "+ty.ToString();
            Thread.Sleep(500);
            drawing();
        }
        public void playing()
        {
            while (!invoke.check(2, board))
            {
                if (turn % 2 == 0)
                {
                    ModeLabel.Content = "Mode Computer Thinking!";
#pragma warning disable CS4014
                    playbyAI();
#pragma warning restore CS4014
                    turn++;
                }
                else
                    return;
            }
            return;

        }
        private void Rectangle_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            if (turn % 2 == 0)
              return;
            int tmp;
            Point pt = e.GetPosition(this);
            ModeLabel.Content = "Mode Your turn!";
            if (click_times == 0)
            {
                x = Convert.ToInt32(Math.Floor((pt.X - 35) / 82));
                tmp = x;
                y = Convert.ToInt32(Math.Floor((pt.Y - 30) / 82));
                x = y - 1;
                y = tmp;
                click_times++;
                if (x < 0 || y < 0 || x > 6 || y > 6)
                {
                    return;
                }
            }
            else
            {
                x1 = Convert.ToInt32(Math.Floor((pt.X - 35) / 82));
                y1= Convert.ToInt32(Math.Floor((pt.Y - 30) / 82));
                tmp = x1;
                x1 = y1 - 1;
                y1= tmp;
                if (x1 < 0 || y1 < 0 || x1 > 6 || y1 > 6)
                {
                    return;
                }
                if (invoke.validmove(x, y, x1, y1, 1, board))
                {
                    invoke.moving(x1, y1, 1, ref board);
                    int way = Math.Max(Math.Abs(x - x1), Math.Abs(y - y1));
                    if (way == 2)
                        board[x, y] = 0;
                    ++turn;
                    playing();
                }
                else
                {
                    x = x1;
                    y = y1;
                    return;
                }
                click_times = 0;
                drawing();
            }
            return;
        }
        private void OptionButton_Click(object sender, RoutedEventArgs e)
        {

        }
        private void AboutButton_Click(object sender, RoutedEventArgs e)
        {

        }
        private void RestartButton_Click(object sender, RoutedEventArgs e)
        {

        }
        public void Drawchessboard(int i, bool horizontal)
        {
            System.Windows.Shapes.Line line;
            line = new System.Windows.Shapes.Line();
            if (horizontal == true)
            {
                line.X1 = 50;
                line.X2 = 624;
                line.Y1 = 50+(82) *i;
                line.Y2 = 50+(82) * i;
            }
            else
            {
                line.Y1 = 50;
                line.Y2 = 624;
                line.X1 = 50+(82) * i;
                line.X2 = 50+(82) * i;
            }
            line.Stroke = new SolidColorBrush(Colors.Black);
            line.StrokeThickness = 1;
            chessboard.Children.Add(line);
        }
        public void InitWindow()
        {
            for (int i = 0; i < 7; i++)
                for (int j = 0; j < 7; j++)
                    board[i, j] = 0;
            board[0, 6] = 2;
            board[6, 0] = 2;
            board[0, 0] = 1;
            board[6, 6] = 1;
            for (int ii = 0; ii <=7; ++ii)
            {
                Drawchessboard(ii, true);
                Drawchessboard(ii, false);
            }
            drawing();
            invoke = new ClassLibrary1.wrapper();
            click_times= 0;
            BlackLabel.Content = "Black: " +"player";
            WhiteLabel.Content = "White: " + "computer";
            ModeLabel.Content = "Mode: Your turn!";
        }
    }
}
