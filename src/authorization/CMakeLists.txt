project(authorization)


target_sources(appEveCompanion
    PRIVATE
        include/Authorization_engine.h
        src/Authorization_engine.cpp
        include/Tcp_server.h
        src/Tcp_server.cpp
        src/Validating_JWT.cpp
        include/Validating_JWT.h
)

target_include_directories(appEveCompanion
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/include"
)


