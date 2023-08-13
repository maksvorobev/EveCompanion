import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material
import Qml.StyleSettings 1.0


Rectangle{
    id: root
    property alias button_width: root.width
    property alias button_height: root.height
    property alias button_image_url: button_image.source

    signal clicked

    color: Material.background
    Image{
        id: button_image
        anchors.fill: parent
    }
    MouseArea{
        id: button_area
        anchors.fill: parent
        onClicked: root.clicked()
    }
}


