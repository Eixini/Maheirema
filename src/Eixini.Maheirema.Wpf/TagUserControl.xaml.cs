using System.Windows;
using System.Windows.Controls;

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
