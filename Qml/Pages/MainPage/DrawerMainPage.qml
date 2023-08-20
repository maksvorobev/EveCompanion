import QtQml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material
import Qml.StyleSettings 1.0
import Qml.CastomButtons 1.0
import QtQuick.Layouts




Drawer {
    id: root
    width: 0.66 * main_page.width
    height: main_page.height
    //opened: false
    visible: false
    Label {
        text: "Content goes here!"
        anchors.centerIn: parent
    }
    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        spacing: 0

        Rectangle{
            id: header
            height: 120
            Layout.fillWidth: true
            color: "red"
            //color: Material.background

        }
        DrawerModel {
            id: drawerModel
        }

        Rectangle{
            Layout.fillWidth: true
            height:  450
            color: "green"
            //color: Material.background
            ListView{
                id: listView
                anchors.fill: parent
                model: drawerModel
                clip: true

                delegate: Rectangle{
                    property var isCurrent: ListView.isCurrentItem
                    property var view: ListView.view
                    //color: "blue"
                    color: mouseArea.containsMouse ? "lightgrey" : "white"
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 40

                    Text{
                        anchors.centerIn: parent
                        text: model.name
                    }
                    MouseArea {
                        id: mouseArea
                        hoverEnabled: true
                        anchors.fill: parent
                        onClicked: {
                            console.log(model.index)
                            view.currentIndex = model.index
                        }
                        onEntered: {
                            console.log(model.index)
                        }
                    }
                }

            }
        }
        Rectangle{
            id: footer
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: Material.background
            RowLayout {
                anchors.centerIn: parent

                Text {
                    text: "Night Mode"
                    color: Material.foreground
                    Layout.alignment: Qt.AlignVCenter // Выравнивание текста по вертикали
                }

                Switch {
                    // Ваши настройки для Switch
                    onClicked: {
                        main_root.is_dark = !main_root.is_dark;
                    }
                }
            }
        }
    }
}
