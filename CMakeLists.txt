cmake_minimum_required(VERSION 3.19)
project(smart_com)

set(CMAKE_CXX_STANDARD 20)

include_directories(include src)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SRC_HELPERS
        src/common/helpers/data_helper.cpp
        src/smarteam/helper.cpp
        src/smarteam/gateways/helpers/geteway_helper.cpp
        )

set(SRC_PROVIDERS
        src/smarteam/data/providers/smarteam_provider.cpp
        src/smarteam/data/providers/engine_provider.cpp
        src/smarteam/data/providers/database_provider.cpp
        src/smarteam/data/providers/session_provider.cpp
        )

set(SRC_REPOSITORIES
        src/smarteam/data/repositories/smarteam_repository_imp.cpp
        )

set(SRC_GATEWAYS
        src/smarteam/gateways/smarteam_gateway.cpp
        src/smarteam/gateways/user_gateway_imp.cpp
        )

set(SRC_USECASES
        )

set(SRC_CONTEXT src/app_context.cpp)

set(SRC_LIST
        ${SRC_HELPERS}
        ${SRC_PROVIDERS}
        ${SRC_REPOSITORIES}
        ${SRC_GATEWAYS}
        ${SRC_USECASES}
        library.cpp
        )

add_library(${PROJECT_NAME} SHARED ${SRC_LIST})

enable_testing()
set(SRC_TESTS
        test/src/smarteam/helper_test.cpp
        test/src/smarteam/data/data_helper_test.cpp
        test/src/smarteam/data/providers/smarteam_provider_test.cpp
        test/src/smarteam/data/providers/engine_provider_test.cpp
        test/src/smarteam/data/providers/database_provider_test.cpp
        test/src/smarteam/data/providers/session_provider_test.cpp
        test/src/smarteam/data/repositories/smarteam_repository_test.cpp
        test/src/smarteam/gateways/user_gateway_test.cpp
        test/src/smarteam/gateways/helpers/gateway_helper_test.cpp
        test/src/app_context_test.cpp
        test/main_test.cpp
        )

add_executable(
        google_test
        ${SRC_HELPERS}
        ${SRC_PROVIDERS}
        ${SRC_REPOSITORIES}
        ${SRC_GATEWAYS}
        ${SRC_USECASES}
        ${SRC_CONTEXT}
        ${SRC_TESTS}
)

target_link_libraries(google_test gtest_main)

include(GoogleTest)
gtest_discover_tests(google_test)
