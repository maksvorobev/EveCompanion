project(RestRequestManager)


target_sources(appEveCompanion
    PRIVATE
        include/RestRequestManager.h
        src/RestRequestManager.cpp
)

target_include_directories(appEveCompanion
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/include"
)


