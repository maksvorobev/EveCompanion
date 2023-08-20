import QtQuick
import QtQuick.Window
import QtQuick.Controls 2.15
import QtQuick.Controls.Material
import Qml.StyleSettings 1.0
import Qml.CastomButtons 1.0

Rectangle{
    id:root
    anchors.fill : parent
    Page {
        id: page
        anchors.fill : parent

        header: Rectangle{
            id: main_page_header
            height: Style.hugeHeaderHeight
            anchors.left: parent.left
            anchors.right: parent.right
            color: Material.background
            ButtonPageEvent {
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                button_width: Style.defaultIconWidth
                button_image_url: main_root.is_dark ?  "data/imgs/left-arrow-white.svg" : "data/imgs/left-arrow-black.svg"
                onClicked:{
                    var component = Qt.createComponent("MainPage/MainPage.qml");
                    if( component.status != Component.Ready )
                    {
                        if( component.status == Component.Error )
                            console.debug("Error:"+ component.errorString() );
                        return; // or maybe throw
                    }
                    component.createObject(root);
                    console.log("create MainPage.qml");
                }
            }
        }

        Text{
            id: welcome_text
            width: 100
            height: 40
            color: Material.foreground
            anchors.left: login_img.left
            anchors.bottom: login_img.top
            anchors.bottomMargin: 200
            font.pointSize: 20
            font.bold : true
            text: "o7 capsuleer,\nlogin with your account"

        }

        Image {
            id: login_img
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height/3
            source: "data/imgs/eve-sso-login-white-large.png"
            MouseArea{
                anchors.fill : parent
                onClicked: {
                    console.log("click");
                    Qt.openUrlExternally(Authorization_engine.p_Direct_URL);
                }
            }
        }

    }

    Connections {
        target: Authorization_engine
        onLaod_main_page_in_qml: {
            var component = Qt.createComponent("MainPage/MainPage.qml");
            if( component.status != Component.Ready )
            {
                if( component.status == Component.Error )
                    console.debug("Error:"+ component.errorString() );
                return; // or maybe throw
            }
            component.createObject(root);
            console.log("create MainPage.qml");
        }
    }

}
