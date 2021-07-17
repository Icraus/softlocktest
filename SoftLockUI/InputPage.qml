import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.0
import Qt.labs.settings 1.0

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
                id: keyTextBox
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                label: qsTr("Key")
            }
            LabeledText{
                id: ivTextBox
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                label: qsTr("iv")
            }

            LabeledText{
                id: inputfilePathTextBox
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                label: qsTr("Input file path")
                Button{
                    text: qsTr("Browse.")
                    onClicked: {
                        inputFileDialog.open()
                    }
                }
            }
            LabeledText{
                id: outputfilePathTextBox
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                label: qsTr("Output file path")
                Button{
                    text: qsTr("Browse.")
                    onClicked: {
                        outputFileDialog.open()
                    }
                }
            }
            RowLayout{
                Button{
                    action: encryptAction
                }
                Button{
                    action: decryptAction
                }
            }
        }


    }
    Action{
        id: encryptAction
        text: qsTr("&Encrypt")
        onTriggered: {
            crypto.encryptFile(inputfilePathTextBox.text, outputfilePathTextBox.text
                           , keyTextBox, ivTextBox)
        }
    }
    Action{
        id: decryptAction
        text: qsTr("&Decrypt")
        onTriggered: {
            crypto.decryptFile(inputfilePathTextBox.text, outputfilePathTextBox.text
                           , keyTextBox, ivTextBox)
        }
    }
    FileDialog {
        id: inputFileDialog
        title: qsTr("Choose a file to encyrpt.")
        folder: shortcuts.home
        onAccepted: {
            inputfilePathTextBox.text = fileUrl

        }
    }
    FileDialog {
        id: outputFileDialog
        title: qsTr("Save.")
        folder: shortcuts.home
        selectExisting: false
        onAccepted: {
           outputfilePathTextBox.text = fileUrl
        }
    }
    Settings{
        property alias key: keyTextBox.text
        property alias inputFile: inputfilePathTextBox.text
        property alias outputFile: outputfilePathTextBox.text
        property alias iv: ivTextBox.text
    }
}
