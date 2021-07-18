import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.0
import Qt.labs.settings 1.0
import com.softlock 1.0
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
        GroupBox{
            Layout.fillWidth: true
            title: qsTr("Input file")
            ColumnLayout{
                anchors.fill: parent
                anchors.leftMargin: 10
                spacing: 2
                LabeledText{
                    label: qsTr("Extension:")
                    control: Label{
                        text: inputFile.extension == ""? qsTr("No Extension") : inputFile.extension
                    }
                    Layout.fillWidth: true
                }
                LabeledText{
                    Layout.fillWidth: true
                    label: qsTr("Size:")
                    control: Label{
                        text: inputFile.size
                    }
                }
                LabeledText{
                    Layout.fillWidth: true
                    id: inputfilePathTextBox
                    text: inputFile.filePath
                    Layout.preferredHeight: 30
                    label: qsTr("Input file path")
                    onEditingFinshed: {
                        inputFile.filePath = text
                    }

                    Button{
                        text: qsTr("Browse.")
                        onClicked: {
                            inputFileDialog.open()
                        }
                    }
                }
            }

        }


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
                           , keyTextBox.text, ivTextBox.text)
        }
    }
    Action{
        id: decryptAction
        text: qsTr("&Decrypt")
        onTriggered: {
            crypto.decryptFile(inputfilePathTextBox.text, outputfilePathTextBox.text
                           , keyTextBox.text, ivTextBox.text)
        }
    }
    FileDialog {
        id: inputFileDialog
        title: qsTr("Choose a file to encyrpt.")
        folder: shortcuts.home
        onAccepted: {
            inputFile.filePath = fileUrl.toString()
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
    FileObject{
        id: inputFile
    }

    Settings{
        property alias key: keyTextBox.text
        property alias inputFile: inputfilePathTextBox.text
        property alias outputFile: outputfilePathTextBox.text
        property alias iv: ivTextBox.text
    }
}
