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

namespace Eixini.Maheirema.Wpf;
    /// <summary>
    /// Логика взаимодействия для TagUserControl.xaml
    /// </summary>
    public partial class TagUserControl : UserControl {
        public TagUserControl() {
            InitializeComponent();
        }

        public void TagContent(string text) {
            TagContentLabel.Content = text;
        }

    public void TagDeleteButton_Click(object sender, RoutedEventArgs e) {
        //MessageBox.Show("TagDeleteButton handler call! Tag: " + TagContentLabel.Content);
        ((Button)TagGrid.Parent).Content = null;
        ((Grid)TagDeleteButton.Parent).Children.Remove(this);

    }

}

