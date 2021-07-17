import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Tabs")
    Connections{
        target: crypto
        function onState(progress, message){
            operationProgressBar.value = (progress / 100.0);
            statusText.text = message
        }

        function onError(errorMessage){
            statusText.text = errorMessage;
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        InputPage {
            mtitle: qsTr("SoftLock")
        }

    }

    footer: ColumnLayout{
        spacing: 5
        ProgressBar {
            id: operationProgressBar
            value: 0
            Layout.fillWidth: true
        }
        Label{
            id: statusText
            text: qsTr("idle.")
            Layout.fillWidth: true
        }
    }
}
