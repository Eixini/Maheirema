using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.IO;
using System.Xml.Linq;
using System.Linq;

namespace Eixini.Maheirema.Wpf;

public struct RecipeInfo {
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
        MaheiremaMainFrame.Content = new EnteredIngredientsPage();
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

}

