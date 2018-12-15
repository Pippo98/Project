import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import com.serial 1.0

Item{
    id: itemCombo

    property variant members
    property int currentSelection: 0
    property bool edit: true

    implicitWidth: combo.implicitWidth + 5
    implicitHeight: combo.implicitHeight + 10

    ComboBox{
        id: combo

        width: parent.width
        height: parent.height
        model: members

        Serial_qml {
            id: serial_qml
        }

        onActivated: {
            backend.comboChanged(currentText, currentIndex)
        }

        Timer{
            id: timer1
            repeat: true
            interval: 1000
            running: true

            onTriggered: {
                members = serial_qml.detectPort
            }
        }
    }
}
