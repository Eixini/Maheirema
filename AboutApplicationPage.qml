import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

Page {
    id: aboutApplicationWindow

    ColumnLayout{
        id: aboutApplicationWindowLayout
        anchors.fill: parent

        AnimatedImage{
            id: maheiremaAnimatedLogo
            source: "qrc:/repository_files/maheirema_gif.gif"
            anchors.margins: 10
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
        // End of code block with animation
        }

        Item{
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Label{
                text: "Application version: In developing"
            }
            Label{
                text: "Developer: Eixini"
            }

        // End of application information code block
        }

        Button{
            text: qsTr("Back")
            Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
            anchors.margins: 10
            onClicked: {
                stackView.pop();
            }
        // End of code block for back to main window button
        }

    // End of app info page builder code block
    }


// End of app info page code block
}
