pragma Singleton
import QtQuick



QtObject{
    readonly property real defaultOpacity: 1
    readonly property real emphasisOpacity: 0.87
    readonly property real secondaryOpacity: 0.6
    readonly property real disabledOpacity: 0.38


    readonly property int defaultOffset: 15
    readonly property int mediumOffset: 10
    readonly property int tinyOffset: 5

    readonly property int defaultHeaderHeight: 40
    readonly property int hugeHeaderHeight: 60

    readonly property int defaultIconWidth: 40
}
