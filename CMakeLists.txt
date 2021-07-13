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
        src/smarteam/helper.cpp
        src/smarteam/data/data_helper.cpp
        )

set(SRC_PROVIDERS
        src/smarteam/data/providers/smarteam_provider.cpp
        src/smarteam/data/providers/engine_provider.cpp
        )


set(SRC_LIST ${SRC_HELPERS} ${SRC_PROVIDERS} library.cpp library.h)

add_library(${PROJECT_NAME} SHARED ${SRC_LIST})

enable_testing()
set(SRC_TESTS
        test/helper_test.cpp
        test/smarteam_provider_test.cpp
        test/data_helper_test.cpp
        test/main_test.cpp
        )

add_executable(google_test ${SRC_HELPERS} ${SRC_PROVIDERS} ${SRC_TESTS})

target_link_libraries(google_test gtest_main)

include(GoogleTest)
gtest_discover_tests(google_test)
