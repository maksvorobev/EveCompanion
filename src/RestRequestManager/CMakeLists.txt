project(RestRequestManager)


target_sources(appEveCompanion
    PRIVATE
        include/RestRequestManagerWithoutAuth.h
        src/RestRequestManagerWithoutAuth.cpp
        include/RestRequestManagerWithAuth.h
        src/RestRequestManagerWithAuth.cpp
        src/RefreshTokenSeveralPostRequest.cpp
        include/RefreshTokenSeveralPostRequest.h
)

target_include_directories(appEveCompanion
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/include"
)


