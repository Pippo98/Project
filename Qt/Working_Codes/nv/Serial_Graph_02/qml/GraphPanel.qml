import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0

Item {
    id: graphPanel
    visible: true

    implicitWidth: graphsText.implicitWidth + 5
    implicitHeight: graphsText.implicitHeight + 10

    Text{
        id: graphsText

        text: "hola"
    }
}
