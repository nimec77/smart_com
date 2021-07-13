//
// Created by nim on 13.07.2021.
//

#include <gtest/gtest.h>
#include <smarteam/data/data_helper.h>
#include <smarteam/data/providers/engine_provider.h>
#include <smarteam/data/providers/session_provider.h>
#include <smarteam/data/providers/smarteam_provider.h>

using namespace smarteam;

class SessionProviderTest : public ::testing::Test {
 public:
  IDispatch *session_app{nullptr};
  _bstr_t *connection_string{nullptr};
  _bstr_t *database_password{nullptr};

 protected:
  static void SetUpTestSuite() {
    //    std::cout << "SetUpTestSuite" << std::endl;
    CoInitialize(nullptr);
  }

  static void TearDownTestSuite() {
    //    std::cout << "TearDownTestSuite" << std::endl;
  }

  void SetUp() override {
    //    std::cout << "SetUp" << std::endl;
    if (session_app != nullptr) {
      return;
    }
//    session_app = SmarteamProvider::GetInstance()
//                      .RightFlatMap([](const auto smarteam_provider_ptr) {
//                        return smarteam_provider_ptr->GetEngine();
//                      })
//                      .RightMap([](const auto engine_app) {
//                        return EngineProvider::GetInstance(engine_app);
//                      })
//                      .RightFlatMap([](const auto engine_provider_ptr) {
//                        const auto application_name = _bstr_t(kApplicationName);
//                        const auto configuration_name = _bstr_t(kConfigurationName);
//                        return engine_provider_ptr->CreateSession(application_name, configuration_name);
//                      })
//        | nullptr;
    auto engine_provider_ptr = SmarteamProvider::GetInstance()
        .RightFlatMap([](const auto smarteam_provider_ptr) {
          return smarteam_provider_ptr->GetEngine();
        })
        .RightMap([](const auto engine_app) {
          return EngineProvider::GetInstance(engine_app);
        }) | nullptr;
    ASSERT_NE(engine_provider_ptr, nullptr);
  }

  void TearDown() override {
    //    std::cout << "TearDown" << std::endl;
  }
};

TEST_F(SessionProviderTest, SessionProviderGetInstanceTest) {

  ASSERT_NE(session_app, nullptr);

  auto session_provider_ptr = SessionProvider::GetInstance(session_app);

  ASSERT_NE(session_provider_ptr, nullptr);

  ASSERT_EQ(typeid(session_provider_ptr), typeid(SessionProvider *));
}

TEST_F(SessionProviderTest, SessionProviderOpenDatabaseConnectionTest) {

  auto session_provider_ptr = SessionProvider::GetInstance(session_app);

  //  auto open_either = session_provider_ptr->OpenDatabaseConnection();
}