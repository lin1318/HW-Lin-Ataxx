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
using System.Windows.Shapes;
namespace Ataxx
{
    /// <summary>
    /// Result.xaml 的交互逻辑
    /// </summary>
    public partial class Result : Window
    {
        public Result()
        {
            InitializeComponent();
            BlackLabel.Content ="Black: "+MainWindow.b.ToString();
            WhiteLabel.Content = "White: "+MainWindow.w.ToString();
            ResultLabel.Content = "Result: "+MainWindow.sb;
        }
    }
}
