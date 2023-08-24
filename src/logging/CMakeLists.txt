project(logging)


target_sources(appEveCompanion
    PRIVATE
        Logger.cpp
        Logger.h
)

target_include_directories(appEveCompanion
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}"
)


