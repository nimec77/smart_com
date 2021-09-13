project(Google_tests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SRC_TESTS
        src/smarteam/helper_test.cpp
        src/smarteam/data/data_helper_test.cpp
        src/smarteam/data/providers/smarteam_provider_test.cpp
        src/smarteam/data/providers/engine_provider_test.cpp
        src/smarteam/data/providers/database_provider_test.cpp
        src/smarteam/data/providers/session_provider_test.cpp
        src/smarteam/data/repositories/smarteam_repository_test.cpp
        src/smarteam/gateways/user_gateway_test.cpp
        src/smarteam/gateways/helpers/gateway_helper_test.cpp
        src/smarteam/domain/use_case/user_use_cases_test.cpp
        src/crypto/data/repositories/crypto_repository_imp_test.cpp
        src/crypto/domain/use_cases/crypto_use_cases_test.cpp
        src/crypto/data/providers/sid_provider_imp_test.cpp
        src/app_context_test.cpp
        main_test.cpp
        )

add_executable(
        google_test
        ${SRC_LIST}
        ${SRC_TESTS}
)

target_link_libraries(google_test gtest gmock gtest_main ${BCRYPT})