import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

Page {
    id: aboutApplicationWindow

    AnimatedImage{
        id: maheiremaAnimatedLogo
        source: "qrc:/repository_files/maheirema_gif.gif"
        anchors.margins: 15
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    } // End of code block with animation

    Label{
        id: applicationVersionLabel
        anchors.top: maheiremaAnimatedLogo.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 20
        text: "Application version: In developing"
    } // End of code block for LABEL "Application version"

    Label{
        id: aboutDeveloperLabel
        anchors.top: applicationVersionLabel.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 20
        text: "Developer: Eixini"
    } // End of code block for LABEL "Developer"

    Button{
        text: qsTr("Back")
        anchors.margins: 10
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {    stackView.pop();   }

    } // End of code block for back to main window button

} // End of app info page code block
