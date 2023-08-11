project(authorization)


target_sources(appEveCompanion
    PRIVATE
        include/Authorization_engine.h
        src/Authorization_engine.cpp
        include/Tcp_server.h
        src/Tcp_server.cpp
        src/Validating_JWT.cpp
        include/Validating_JWT.h
        include/Auth_user_data.h
        src/Auth_user_data.cpp
        src/User_data_handler.cpp
        include/User_data_handler.h
)

target_include_directories(appEveCompanion
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/include"
)


