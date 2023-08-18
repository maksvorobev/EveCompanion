qt_add_library(MainPage STATIC)


qt_add_qml_module(MainPage
    URI Qml.Pages.MainPage
    VERSION 1.0
    QML_FILES MainPage.qml DrawerMainPage.qml DrawerModel.qml
    RESOURCE_PREFIX /maksvorobev/imports
    RESOURCES
)


