using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.IO;

namespace Eixini.Maheirema.Wpf;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window {
    public MainWindow() {
        InitializeComponent();
        DirectoryCheck();
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

        // Планируется вызов метода сравнения ингредиентов и получение коллекции рецептов (имена файлов)
        // Для дальнейшей обработки (открытие списка рецептов и просмотр в другом окне/странице)
    }

    private void DirectoryCheck() {  
        var pathApplication = 
            Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData) + 
            Path.DirectorySeparatorChar + "EixiniSoftware" + Path.DirectorySeparatorChar +
            "Maheirema";

        // Checking for the existence of the application directory
        if (!Directory.Exists(pathApplication)) {
            MessageBox.Show("Директория приложения не существует! Будет создана новая!"); // DEBUG MESSAGE
            Directory.CreateDirectory(pathApplication);
        } else {
            MessageBox.Show("Директория приложения существует!");   // DEBUG MESSAGE
        }

        // Checking for the existence of a recipe directory
        var pathRecipes = pathApplication + Path.DirectorySeparatorChar + "Recipes";
        var pathIngredients = pathApplication + Path.DirectorySeparatorChar + "Ingredients";
        if(!Directory.Exists(pathRecipes)) {
            Directory.CreateDirectory(pathRecipes);
        }
        if (!Directory.Exists(pathIngredients)) {
            Directory.CreateDirectory(pathIngredients);
        }
    }

    private List<string> IngredientsComparison(List<string> enteredIngredients) {
        List<string> result = new List<string>();



        return result;
    }
}

