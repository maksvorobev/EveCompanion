
qt_add_library(Qml.StyleSettings STATIC)
set_source_files_properties(Style.qml PROPERTIES
    QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(Qml.StyleSettings
    URI UriStyleSettings
    VERSION 1.0
    QML_FILES Style.qml
    RESOURCE_PREFIX /maksvorobev/imports
)
