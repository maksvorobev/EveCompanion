import QtQuick
import QtQuick.Window
import QtQuick.Controls 2.15
import Qml.StyleSettings 1.0
import Qml.Pages 1.0
import QtQuick.Controls.Material

Window {
    id: root
    width: 360
    height: 640
    visible: true
    title: qsTr("Hello World")
    property bool is_dark: false
    Material.theme: is_dark ? Material.Dark : Material.Light
    /*
    function onPushSecondPage(){
        stackView.push(page2);
    }
    */

    AuthPage{

    }

    /*
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: page1
    }

    AuthPage {
        id : page1
    }

    Connections {
        target: User_data_handler
        onPushSecondPage: {
            console.log("onPushSecondPage!!!")
            stackView.push(page2);
        }
    }


    SecondPage {
        id: page2
        visible: false

    }
    */
    /*
    Button {
        anchors.centerIn: parent

        onClicked: {
            //var path = Autho_engine.Direct_URL.toString();
            Qt.openUrlExternally(p_Direct_URL);
        }
    }
    */
}
