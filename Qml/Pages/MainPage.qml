import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material
import Qml.StyleSettings 1.0
import Qml.CastomButtons 1.0



Page {
    id: main_page
    anchors.fill: parent
    header: Rectangle{
        id: main_page_header
        height: Style.hugeHeaderHeight
        anchors.left: parent.left
        anchors.right: parent.right
        color: Material.background
        ButtonPageEvent {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            button_width: 60
            button_image_url: "data/imgs/879374.png"
            onClicked:{
                drawer.open();
            }
        }
    }
    Text{
        text: "It is MainPage"
        anchors.centerIn: parent
    }
        Drawer {
            id: drawer
            width: 0.66 * main_page.width
            height: main_page.height

            Label {
                text: "Content goes here!"
                anchors.centerIn: parent
            }
        }


}
