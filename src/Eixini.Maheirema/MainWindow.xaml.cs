using System.IO;
using System.Windows;

namespace Eixini.Maheirema;

public partial class MainWindow : Window {
    public MainWindow() {
        InitializeComponent();
        DirectoryCheck();
        MaheiremaMainFrame.Content = new EnteredIngredientsPage();
    }

    private static void DirectoryCheck() {
        var pathApplication = 
            Environment.GetFolderPath(Environment.SpecialFolder.UserProfile) +
            Path.DirectorySeparatorChar + "EixiniSoftware" + Path.DirectorySeparatorChar +
            "Maheirema";

        // Checking for the existence of the application directory
        if (!Directory.Exists(pathApplication)) {
#if DEBUG
            MessageBox.Show("Директория приложения не существует! Будет создана новая!");
#endif
            Directory.CreateDirectory(pathApplication);
        }

        // Checking for the existence of a recipe directory
        var pathRecipes = pathApplication + Path.DirectorySeparatorChar + "Recipes";
        var pathIngredients = pathApplication + Path.DirectorySeparatorChar + "Ingredients";
        if (!Directory.Exists(pathRecipes)) {
            Directory.CreateDirectory(pathRecipes);
        }
        if (!Directory.Exists(pathIngredients)) {
            Directory.CreateDirectory(pathIngredients);
        }
    }
}
