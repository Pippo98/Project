import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0

Item {
    id: spin1

    property int identifier
    property int minimum: 0
    property int maximum: 0

    SpinBox {

        anchors.left: parent.right
        anchors.centerIn: parent.Center

        minimumValue: minimum
        maximumValue: maximum

        onValueChanged: backend.spingChanged(identifier, spin1.value)
    }
}
