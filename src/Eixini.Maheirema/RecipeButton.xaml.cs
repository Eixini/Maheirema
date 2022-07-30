using System;
using System.Text;
using System.Windows.Controls;
using System.Windows;
using System.Windows.Documents;
using System.IO;
using System.Windows.Input;


namespace Eixini.Maheirema;
public partial class RecipeButton : UserControl {
    public RecipeButton() {
        InitializeComponent();
    }

    public void SetText(string text) {
        RecipeButtonElement.Content = text;
    }

    // to store the path to the recipe file
    public string RecipePath { get; set; }

    private void ShowRecipe(object sender, RoutedEventArgs e) {

        //MessageBox.Show(sender.GetType().ToString());

        //Getting text from a recipe file
        //TextRange recipeFile = new TextRange(RecipeText.Document.ContentStart, RecipeText.Document.ContentEnd);
        //FileStream recipeFileStream = new FileStream(RecipePath, FileMode.Open);
        //recipeFile.Load(recipeFileStream, DataFormats.Rtf);


    }

}

