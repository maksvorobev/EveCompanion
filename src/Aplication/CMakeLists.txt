project(Aplication)


target_sources(appEveCompanion
    PRIVATE
        Aplication.cpp
        Aplication.h

)

target_include_directories(appEveCompanion
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}"
)


