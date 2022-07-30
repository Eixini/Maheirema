using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.IO;
using System.Xml.Linq;
using System.Linq;

namespace Eixini.Maheirema.Wpf;

    public partial class EnteredIngredientsPage : Page {
        public EnteredIngredientsPage() {
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

            ingredients.Sort();

            List<RecipeInfo> suitableRecipes = IngredientsComparison(ingredients); 

        if (suitableRecipes.Count != 0)
            NavigationService.Navigate(new ResultRecipePage(suitableRecipes));
        else
            MessageBox.Show("Рецепты, удовлетворяющие введеным ингредиентам не найдены.");

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
            recipeInfo.recipeFileName = file.Replace(".xml", ".rtf").Replace("Ingredients", "Recipes");

            if (rootXmlRecipeElement != null) {

                // Traversing the child elements of the root element
                foreach (XElement recipeInfoChild in rootXmlRecipeElement.Elements()) {

                    if (recipeInfoChild.Name == "name")
                        recipeInfo.name = recipeInfoChild.Value;
                    if (recipeInfoChild.Name == "nationalKitchen")
                        recipeInfo.nationalKitchen = recipeInfoChild.Value;
                    if (recipeInfoChild.Name == "dishType")
                        recipeInfo.dishType = recipeInfoChild.Value;
                    if (recipeInfoChild.Name == "ingredients") {

                        recipeInfo.ingredients = new List<string> { };

                        foreach (XElement ing in recipeInfoChild.Elements())
                            recipeInfo.ingredients.Add(ing.Value);

                        recipeInfo.ingredients.Sort();
                    }

                }

            }

            if (!recipeInfo.ingredients.Except(enteredIngredients).Any())
                result.Add(recipeInfo);

        }

        return result;
    }
}

