import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import Qml.StyleSettings 1.0
import Qml.CastomButtons 1.0
import QtQuick.Layouts


Page {
    id: main_page
    anchors.fill: parent
    ColumnLayout{

        anchors.fill: parent
        Rectangle{
            id: main_page_header
            height: Style.defaultHeaderHeight
            //anchors.left: parent.left
            //anchors.right: parent.right
            Layout.fillWidth: true
            color: Material.background

            ButtonPageEvent {
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                button_width: Style.defaultIconWidth
                button_image_url: main_root.is_dark ?  "data/imgs/hamburger-menu-white.svg" : "data/imgs/hamburger-menu-black.svg"
                onClicked:{
                    drawerMainPage.open();
                }
            }

        }

        Component.onCompleted: {
            //console.log(MainPageModel.objectName, "wefwef")
        }

        DrawerMainPage{
            id: drawerMainPage
        }


        ListView{
            id: listView
            Layout.fillHeight: true
            Layout.fillWidth: true


            model: MainPageModel


            delegate: Rectangle{
                id: main_page_delegate
                anchors.left: parent.left
                anchors.right: parent.right
                height: 64
                color: "green"
                Row{
                    anchors.fill: parent
                    Image {
                        id: character_img
                        source: model.image_url
                    }
                    Text{
                        text: model.name + "wallet: " + model.wallet_balance
                    }
                }

                Component.onCompleted: {
                    console.log("fwwfw")
                }
            }


        }

    }
}
