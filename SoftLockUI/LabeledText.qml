import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
RowLayout {
    property alias text: text.text
    property alias label: label.text
    property alias control: text.contentItem
    signal editingFinshed(string text)
    id: root

    Label{
        id: label
        text: qsTr("")
    }
    Control{
        id: text
        property alias text: item.text
        contentItem: TextField{
            id: item
            onEditingFinished: root.editingFinshed(text)
        }
        Layout.fillWidth: true
    }

}
