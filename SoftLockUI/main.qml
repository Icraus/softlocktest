import QtQuick 2.12
import QtQuick.Controls 2.15

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Tabs")
    Connections{
        target: crypto
        function onError(errorMessage){
            console.log(errorMessage);
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        InputPage {
            mtitle: "kyasd"
        }

    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Page 1")
            onClicked: {
                crypto.error("Errdasdasdadador")
            }
        }
        TabButton {
            text: qsTr("Page 2")
        }
    }
}
