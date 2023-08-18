project(cppModels)


target_sources(appEveCompanion
    PRIVATE
        src/MainPageModel.cpp
        include/MainPageModel.h
        src/MainPageModelData.cpp
        include/MainPageModelData.h
)

target_include_directories(appEveCompanion
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/include"
)


