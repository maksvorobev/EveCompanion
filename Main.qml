import QtQuick
import QtQuick.Window
import QtQuick.Controls 2.15
import Qml.StyleSettings 1.0
import Qml.Pages 1.0
import QtQuick.Controls.Material

Window {
    id: main_root
    width: 360
    height: 640
    visible: true
    title: qsTr("Hello World")
    property bool is_dark: false
    Material.theme: is_dark ? Material.Dark : Material.Light
    Material.primary: is_dark ? Material.Indigo : Material.Teal
    Material.accent: is_dark ? Material.Pink : Material.Pink
    Material.background: is_dark ? "#121212" : Material.BlueGrey
    Material.foreground: is_dark ? "#FFFFFF" : "#000000"


    AuthPage{

    }



}
