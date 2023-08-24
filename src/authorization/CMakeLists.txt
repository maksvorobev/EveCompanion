project(authorization)


target_sources(appEveCompanion
    PRIVATE
        include/Authorization_engine.h
        src/Authorization_engine.cpp
        include/TcpServer.h
        src/TcpServer.cpp
        src/Validating_JWT.cpp
        include/Validating_JWT.h
        include/Auth_user_data.h
        src/Auth_user_data.cpp
        src/AuthUserDataManager.cpp
        include/AuthUserDataManager.h
        include/DataStorage.h
        src/DataStorage.cpp
        include/CastomNetworkAccessManager.h
        src/CastomNetworkAccessManager.cpp
        src/AuthorizationUrl.cpp
        include/AuthorizationUrl.h
)

target_include_directories(appEveCompanion
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/include"
)


