namespace Eixini.Maheirema;

public struct RecipeInfo {
    public string name;              // Имя рецепта
    public string nationalKitchen;   // Нация кухни
    public string dishType;          // Тип блюда
    public List<string> ingredients; // Список ингредиентов
    public string recipeFileName;    // Имя файла, в котором находится текст рецепта
}
