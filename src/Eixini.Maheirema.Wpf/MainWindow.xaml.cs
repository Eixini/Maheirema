using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Eixini.Maheirema.Wpf;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window {
    public MainWindow() {
        InitializeComponent();
    }

    private void EntryLineTextBox_KeyDown(object sender, KeyEventArgs e) {
        if (e.Key == Key.Enter && EntryLineTextBox.Text != "") {
            var ingredient = EntryLineTextBox.Text;

            var testTag = new Button {
                Content = ingredient
            };

            var tag = new TagUserControl();
            tag.TagContent(ingredient);
            TagFieldWrapPanel.Children.Add(tag);

            EntryLineTextBox.Clear();
        }
    }

    private void RecipeRequestButton_Click(object sender, RoutedEventArgs e) {

        if (TagFieldWrapPanel.Children.Count == 0) {
            MessageBox.Show("Вы не ввели ингредиенты!");
            return;
        }
        var ingredients = new List<string>();

        foreach (var tag in TagFieldWrapPanel.Children) {
            
            var grid = tag as TagUserControl;
            var ingredient = grid?.TagButton.Content as string;

            ingredients.Add(ingredient);
        }
    }

    private void DirectoryCheck() {
        var systemUserName = Environment.UserName as string;
    }
}

