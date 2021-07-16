import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
RowLayout {
    property alias text: text.text
    property alias label: label.text
    Label{
        id: label
        text: qsTr("")
    }
    TextField{
        id: text
        Layout.fillWidth: true
    }
}
