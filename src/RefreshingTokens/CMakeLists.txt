project(RefreshingTokens)


target_sources(appEveCompanion
    PRIVATE
        include/Refresh_Manager.h
        src/Refresh_Manager.cpp
)

target_include_directories(appEveCompanion
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/include"
)


