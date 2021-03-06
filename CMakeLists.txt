cmake_minimum_required(VERSION 3.19)
project(smart_com)

set(CMAKE_CXX_STANDARD 20)

include_directories(include src)

set(SRC_HELPERS
        ${CMAKE_SOURCE_DIR}/src/common/helpers/helper.cpp
        ${CMAKE_SOURCE_DIR}/src/common/helpers/string_helper.cpp
        ${CMAKE_SOURCE_DIR}/src/common/helpers/geteway_helper.cpp
        )

set(SRC_PROVIDERS
        ${CMAKE_SOURCE_DIR}/src/smarteam/data/providers/smarteam_provider.cpp
        ${CMAKE_SOURCE_DIR}/src/smarteam/data/providers/engine_provider.cpp
        ${CMAKE_SOURCE_DIR}/src/smarteam/data/providers/database_provider.cpp
        ${CMAKE_SOURCE_DIR}/src/smarteam/data/providers/session_provider.cpp
        ${CMAKE_SOURCE_DIR}/src/crypto/data/providers/sid_provider_imp.cpp
        ${CMAKE_SOURCE_DIR}/src/crypto/data/providers/crypto_provider_imp.cpp
        )

set(SRC_REPOSITORIES
        ${CMAKE_SOURCE_DIR}/src/smarteam/data/repositories/smarteam_repository_imp.cpp
        ${CMAKE_SOURCE_DIR}/src/crypto/data/repositories/crypto_repository_imp.cpp
        )

set(SRC_GATEWAYS
        ${CMAKE_SOURCE_DIR}/src/smarteam/gateways/user_gateway_imp.cpp
        ${CMAKE_SOURCE_DIR}/src/crypto/gateways/crypto_gateway_imp.cpp
        )

set(SRC_USE_CASES
        ${CMAKE_SOURCE_DIR}/src/smarteam/domain/use_cases/user_use_cases.cpp
        ${CMAKE_SOURCE_DIR}/src/crypto/domain/use_cases/crypto_use_cases.cpp
        )

set(SRC_CONTEXT ${CMAKE_SOURCE_DIR}/src/app_context.cpp)

set(SRC_LIST
        ${SRC_HELPERS}
        ${SRC_PROVIDERS}
        ${SRC_REPOSITORIES}
        ${SRC_GATEWAYS}
        ${SRC_USE_CASES}
        ${SRC_CONTEXT}
        ${CMAKE_SOURCE_DIR}/library.cpp
        )

find_library(BCRYPT bcrypt.lib)

add_library(${PROJECT_NAME} SHARED ${SRC_LIST})


enable_testing()
add_subdirectory(test)

target_link_libraries(${PROJECT_NAME} ${BCRYPT})
