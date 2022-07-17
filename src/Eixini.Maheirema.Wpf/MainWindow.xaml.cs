using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.IO;
using System.Xml.Linq;
using System.Linq;

namespace Eixini.Maheirema.Wpf;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>

struct RecipeInfo {
    public string name;                 // Имя рецепта
    public string nationalKitchen;      // Нация кухни
    public string dishType;             // Тип блюда
    public List<string> ingredients;    // Список ингредиентов
    public string recipeFileName;       // Имя файла, в котором находится текст рецепта
}

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

        _ = IngredientsComparison(ingredients); // DEBUG
    }

    private void DirectoryCheck() {  
        var pathApplication = 
            Environment.GetFolderPath(Environment.SpecialFolder.UserProfile) + 
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

    private List<RecipeInfo> IngredientsComparison(List<string> enteredIngredients) {
        List<RecipeInfo> result = new List<RecipeInfo>();

        // LINQ , сравнения введеных ингредиентов с ингредиентами из рецептов (JSON)
        var pathApplication =
            Environment.GetFolderPath(Environment.SpecialFolder.UserProfile) +
            Path.DirectorySeparatorChar + "EixiniSoftware" + Path.DirectorySeparatorChar +
            "Maheirema";
        var pathRecipes = pathApplication + Path.DirectorySeparatorChar + "Recipes";
        var pathIngredients = pathApplication + Path.DirectorySeparatorChar + "Ingredients";

        var recipeInfoFiles = new List<string>();

        // Retrieving Recipe Information Filenames
        //recipeInfoFiles = Directory.GetFiles(pathIngredients).Select(a => Path.GetFileName(a)).Select(s => s).ToList();
        recipeInfoFiles = Directory.GetFiles(pathIngredients).Select(s => s).ToList();

        foreach (var file in recipeInfoFiles) { 

            RecipeInfo recipeInfo = new RecipeInfo();   // Temporary recording of recipe data

            XDocument recipeInfoFile = XDocument.Load(file);

            XElement? rootXmlRecipeElement = recipeInfoFile.Element("recipeInfo");

            // Getting the file name of a recipe
            recipeInfo.recipeFileName = file.Replace(".xml", ".html").Replace("Ingredients", "Recipes");

            if (rootXmlRecipeElement != null) {

                // Traversing the child elements of the root element
                foreach (XElement recipeInfoChild in rootXmlRecipeElement.Elements()) {

                    if (recipeInfoChild.Name == "name") 
                        recipeInfo.name = recipeInfoChild.Value;
                    if(recipeInfoChild.Name == "nationalKitchen")
                        recipeInfo.nationalKitchen = recipeInfoChild.Value;
                    if(recipeInfoChild.Name == "dishType")
                        recipeInfo.dishType = recipeInfoChild.Value;
                    if(recipeInfoChild.Name == "ingredients") {

                        recipeInfo.ingredients = new List<string> { };

                        foreach (XElement ing in recipeInfoChild.Elements()) {
                        
                            recipeInfo.ingredients.Add(ing.Value);

                        }
                    }

                }

            }

            result.Add(recipeInfo);

            // DEBUG ============
            string strTest = $"Ингредиенты рецепта \"{recipeInfo.name}\" : " ;
            foreach (string? test in recipeInfo.ingredients)
                strTest += test + ", ";
            MessageBox.Show(strTest);
            MessageBox.Show($"Файл рецепта - {recipeInfo.recipeFileName}");
            // ==================

        }

        return result;
    }
}

