qt_add_library(CastomButtons STATIC)


qt_add_qml_module(CastomButtons
    URI Qml.CastomButtons
    VERSION 1.0
    QML_FILES ButtonPageEvent.qml
    RESOURCE_PREFIX /maksvorobev/imports
    RESOURCES
        ../../data/imgs/879374.png
        ../../data/imgs/60775.png
        ../../data/imgs/left-right-arrow-button-png-left-arrow-icon-sv-11562991530uuomzdoifr.png
        ../../data/imgs/burger-menu-svgrepo-com.svg
        ../../data/imgs/hamburger-menu-white.svg
        ../../data/imgs/hamburger-menu-black.svg
        ../../data/imgs/left-arrow-white.svg
        ../../data/imgs/left-arrow-black.svg

)
