var component;
var tag;

function createTagObject(inputText) {
    component = Qt.createComponent("Tag.qml");

    var inputIngredientText = inputText;

    tag = component.createObject(tagarea, {text: inputIngredientText});

    if (tag == null) {
        // Error Handling
        console.log("Error creating object");
    }
}
