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
        TagButton.Content = text;
    }

    public void TagDeleteButton_Click(object sender, RoutedEventArgs e) {
        var caller = sender as Button;
        var grid = caller?.Parent as Grid;
        var userControl = grid?.Parent as UserControl;
        var wrapPanel = userControl?.Parent as WrapPanel;

        wrapPanel?.Children.Remove(userControl);
    }
}
