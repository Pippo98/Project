import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
//import io.qt.examples.backend 1.0

Item{

    id:button

    property string text: "Option: "
    property variant items: ["Opened"]
    property int currentSelection: 0
    property int identifier
    property bool active: false

    implicitWidth: buttonText.implicitWidth + 5
    implicitHeight: buttonText.implicitHeight + 10

    signal clicked()

    Button{
        id:buttonText
        width: parent.width
        height: parent.height

        style: ButtonStyle{
            label: Component {
                Text {
                    text: button.text + button.items[currentSelection]
                    clip: true
                    wrapMode: Text.WordWrap
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                }
            }
        }
        onClicked: {
            currentSelection = (currentSelection + 1) % items.length
            backend.buttonClicked(identifier, currentSelection)
            active = !active
        }
    }
}
