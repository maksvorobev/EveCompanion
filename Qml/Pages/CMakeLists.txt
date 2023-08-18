qt_add_library(Pages STATIC)


qt_add_qml_module(Pages
    URI Qml.Pages
    VERSION 1.0
    QML_FILES AuthPage.qml SecondPage.qml
    RESOURCE_PREFIX /maksvorobev/imports
    RESOURCES
        ../../data/imgs/eve-sso-login-white-large.png
        # ../../data/imgs/60775.png


)

add_subdirectory(MainPage)
target_link_libraries(Pages PRIVATE MainPageplugin)


