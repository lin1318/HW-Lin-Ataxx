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
    ///  
    public partial class MainWindow : Window
    {
        public static string sb;
        String wl;
        String bl;
        private ClassLibrary1.wrapperlin invoke;
        int[,] board = new int[7, 7];
        public static int b = 0, w = 0;
        int x, y, x1, y1;
        int click_times;
        int mode=3;
        private List<UIElement> visuals = new List<UIElement>();
        int sta = 0;
        private int turn = 1;
        public MainWindow()
        {
            InitializeComponent();
            InitWindow();
        }
        void drawing(int dx,int dy,int dx1,int dy1,int g)
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
            if (g == 1)
            {
                System.Windows.Shapes.Ellipse circle;
                circle = new System.Windows.Shapes.Ellipse()
                {
                    Height = 5,
                    Width = 5
                };
                double left = -15 - 164 * (3 - dy);
                double top = -40 - 164 * (3 - dx);
                circle.Margin = new Thickness(left, top, 0, 0);
                circle.Fill = new SolidColorBrush(Colors.Red);
                chessboard.Children.Add(circle);
                visuals.Add(circle);
            }
            if (g == 1)
            {
                System.Windows.Shapes.Ellipse circle;
                circle = new System.Windows.Shapes.Ellipse()
                {
                    Height = 5,
                    Width = 5
                };
                double left = -15 - 164 * (3 - dy1);
                double top = -40 - 164 * (3 - dx1);
                circle.Margin = new Thickness(left, top, 0, 0);
                circle.Fill = new SolidColorBrush(Colors.Red);
                chessboard.Children.Add(circle);
                visuals.Add(circle);
            }
        }

        public void winprinter()
        {
            for (int i = 0; i < 7; i++)
                for (int j = 0; j < 7; j++)
                {
                    if (board[i, j] == 1)
                        ++b;
                    if (board[i, j] == 2)
                        ++w;
                }
            if (b > w && mode == 1)
                sb = "Computer(Black) wins!";
            if (b > w && mode == 3)
                sb = "Human(Black) wins!";
            if (w > b && mode==1)
                sb = "Human(White) wins!";
            if (w > b && mode == 3)
                sb = "Computer(White) wins!";
            if (mode == 2 && w > b)
                sb = "Player2(White) wins!";
            if (mode == 2 && b > w)
                sb = "Player1(Black) wins!";
            if (b == w)
                sb = "Draw!";
            MessageBoxResult result = MessageBox.Show("Black: "+b.ToString()+"\nWhite: "+w.ToString()+"\nResult: "+sb,"Result");
            b = 0;w = 0;
        }
        private async Task playbyAI()
        {
            StatusLabel.Content = "Status: The robot is thinking!";
            Task<double> com;
            int what = 2 - turn % 2;
            if (mode == 1)
                what = 3 - what;
            com = Task.Run(() =>invoke.alphabeta(board,4,-99999999.9,99999999.9,what));
            await com;
            var data=com.Result;
            int fx = invoke.getfx();
            int fy = invoke.getfy();
            int tx = invoke.gettx();
            int ty = invoke.getty();
            int way = Math.Max(Math.Abs(fx - tx), Math.Abs(fy - ty));
            if (way == 2)
                board[fx, fy] = 0;          
            invoke.moving(tx, ty, what, ref board);
            if(what==2)
                WhiteLabel.Content =wl+"  ("+fx.ToString()+","+fy.ToString()+") "+"-> ("+tx.ToString()+","+ty.ToString()+")";
            else
                BlackLabel.Content =bl+ "  (" + fx.ToString() + "," + fy.ToString() + ") " + "-> (" + tx.ToString() + "," + ty.ToString() + ")";
            //Thread.Sleep(500);
            drawing(fx,fy,tx,ty,1);
            if (invoke.check(3 - what, board))
            {
                winprinter();
                return;
            }
        }
        public void playing()
        {
            if (mode == 2)
            {
                StatusLabel.Content = "Status: "+"Player"+(2-turn%2).ToString()+" Turn";
                return;
            }
            int x;
            if (mode == 1)
                x = 1;
            else
                x = 2;
            if (!invoke.check(x, board))
            {
                if (turn % 2 == 0)
                {
                    
#pragma warning disable CS4014
                    playbyAI();
#pragma warning restore CS4014
                    turn++;
                    StatusLabel.Content = "Status:" + "Player1 Turn";

                }
                else
                { 
                    return;
                }
            }
            else
            {
                winprinter();
            }
            return;

        }
        private void Rectangle_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            if (sta == 0)
                return;
            if (turn % 2 == 0&&mode!=2)
              return;
            int tmp;
            Point pt = e.GetPosition(this);
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
                int what = 2 - turn % 2;
                if (mode == 1)
                    what = 3 - what;
                if (invoke.validmove(x, y, x1, y1, what, board))
                {
                    invoke.moving(x1, y1, what, ref board);
                    int way = Math.Max(Math.Abs(x - x1), Math.Abs(y - y1));
                    if (way == 2)
                        board[x, y] = 0;
                    ++turn;
                    drawing(x,y,x1,y1,1);
                    if (invoke.check(3-what, board))
                    {
                        winprinter();
                        return;
                    }
                    playing();
                }
                else
                {
                    x = x1;
                    y = y1;
                    return;
                }
                click_times = 0;
            }
            return;
        }
        private void OptionButton_Click(object sender, RoutedEventArgs e)
        {

        }
        private void AboutButton_Click(object sender, RoutedEventArgs e)
        {

        }
        private void StartButton_Click(object sender,RoutedEventArgs e)
        {
            sta = 1;
            GStatusLabel.Content = "Game Status: Start";
            if (mode != 1)
            {
                wl = WhiteLabel.Content.ToString();
                bl = BlackLabel.Content.ToString();
            }
            OptionButton.IsEnabled= false;
            Start.IsEnabled = false;
        }
        private void Chuman_Click(object sender,RoutedEventArgs e)
        {
            mode = 1;
            BlackLabel.Content = "Black: " + "Computer";
            WhiteLabel.Content = "White: " + "Player";
            ModeLabel.Content = "Mode: " + "computer vs human";
            StatusLabel.Content = "Status: " + "The robot is thinking";
            OptionButton.IsEnabled = false;
            Start.IsEnabled = true;
            turn++;
            wl = WhiteLabel.Content.ToString();
            bl = BlackLabel.Content.ToString();
            playing();
        }

        private void Hhuman_Click(object sender, RoutedEventArgs e)
        {
            mode = 2;
            BlackLabel.Content = "Black: " + "Player1";
            WhiteLabel.Content = "White: " + "Player2";
            ModeLabel.Content = "Mode: "+"human vs computer";
            StatusLabel.Content = "Status: " + "Player1 Turn";
            OptionButton.IsEnabled = false;
            Start.IsEnabled = true;
        }

        private void Hcomputer_Click(object sender, RoutedEventArgs e)
        {
            mode = 3;
            BlackLabel.Content = "Black: " + "Player";
            WhiteLabel.Content = "White: " + "Computer";
            ModeLabel.Content = "Mode: " + "human vs computer";
            StatusLabel.Content = "Status: " + "Player Turn";
            GStatusLabel.Content = "Game Status: No start";
            OptionButton.IsEnabled = false;
            Start.IsEnabled = true;
        }
        private void RestartButton_Click(object sender, RoutedEventArgs e)
        {
            for (int i = 0; i < 7; i++)
                for (int j = 0; j < 7; j++)
                    board[i, j] = 0;
            board[0, 6] = 2;
            board[6, 0] = 2;
            board[0, 0] = 1;
            board[6, 6] = 1;
            OptionButton.IsEnabled = true;
            click_times = 0;
            BlackLabel.Content = "Black: ";
            WhiteLabel.Content = "White: ";
            ModeLabel.Content = "Mode: ";
            StatusLabel.Content = "Status: ";
            GStatusLabel.Content = "Game Status: " + "No start";
            Start.IsEnabled =false;
            turn = 1;
            sta = 0;
            drawing(0,0,0,0,0);
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
            drawing(0,0,0,0,0);
            invoke = new ClassLibrary1.wrapperlin();
            click_times = 0;
            Start.IsEnabled = false;
        }
    }
}
