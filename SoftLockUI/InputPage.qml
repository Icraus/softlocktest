import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.0

Page {
    width: 600
    height: 400
    property alias mtitle: label.text
    header: Label {
        id: label
        text: qsTr("Page 1")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }
    ColumnLayout{
        anchors.fill: parent
        spacing: 4
        ColumnLayout{
            anchors.leftMargin: 10
            spacing: 2
            LabeledText{
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                label: qsTr("Key")
            }
            LabeledText{
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                label: qsTr("iv")
            }

            LabeledText{
                id: inputfilePathTextBox
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                label: qsTr("File Path")
                Button{
                    text: qsTr("Browse.")
                    onClicked: {
                        fileDialog.open()
                    }
                }
            }
            LabeledText{
                id: outputfilePathTextBox
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                label: qsTr("File Path")
                text: fileDialog.fileUrl
                Button{
                    text: qsTr("Browse.")
                    onClicked: {
                        fileDialog.open()
                    }
                }
            }
            RowLayout{
                Button{
                    text: qsTr("Encrpyt File.")
                }
                Button{
                    text: qsTr("Decrpyt File.")
                }
            }
        }

        FileDialog {
            id: fileDialog
            title: "Please choose a file."
            folder: shortcuts.home
            onAccepted: {

            }
            onRejected: {
            }
        }

    }


}
