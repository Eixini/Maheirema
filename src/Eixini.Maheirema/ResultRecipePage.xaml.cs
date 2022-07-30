using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Navigation;

namespace Eixini.Maheirema;

public partial class ResultRecipePage : Page {
    public ResultRecipePage() {
        InitializeComponent();
    }

    public ResultRecipePage(List<RecipeInfo> availableRecipes) : this() {
        foreach (var recipe in availableRecipes) {
            var recipeInfoButton = new RecipeButton();
            recipeInfoButton.RecipeButtonElement.Click += ShowRecipe;
            recipeInfoButton.SetText(recipe.name);
            recipeInfoButton.RecipePath = recipe.recipeFileName;
            RecipeList.Items.Add(recipeInfoButton);
            RecipeList.UpdateLayout();
        }
    }

    private void RecipeListItem_Selected(object sender, RoutedEventArgs e) {
        throw new NotImplementedException();
    }

    private void BackToIngredientsEnteredPage_Clicked(object sender, RoutedEventArgs e) {
        NavigationService.GoBack();
    }

    private void ShowRecipe(object sender, RoutedEventArgs e) {
        var recipeButtonElement = sender as Button;
        var recipeInfoObject = recipeButtonElement?.Parent as RecipeButton;

        // Getting text from a recipe file
        var recipeFile = new TextRange(RecipeText.Document.ContentStart, RecipeText.Document.ContentEnd);
        var recipeFileStream = new FileStream(recipeInfoObject.RecipePath, FileMode.Open);
        recipeFile.Load(recipeFileStream, DataFormats.Rtf);
    }
}
