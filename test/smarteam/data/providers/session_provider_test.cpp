//
// Created by nim on 13.07.2021.
//

#include "../../../test_config.h"
#include <gtest/gtest.h>
#include <smarteam/data/data_helper.h>
#include <smarteam/data/providers/database_provider.h>
#include <smarteam/data/providers/engine_provider.h>
#include <smarteam/data/providers/session_provider.h>
#include <smarteam/data/providers/smarteam_provider.h>

using namespace smarteam;

class SessionProviderTest : public ::testing::Test {
 public:
  IDispatch *session_app{};
  _bstr_t connection_string;
  _bstr_t database_password;

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
    const auto engine_provider_ptr = SmarteamProvider::GetInstance()
                                         .RightFlatMap([](const auto smarteam_provider_ptr) {
                                           return smarteam_provider_ptr->GetEngine();
                                         })
                                         .RightMap([](const auto engine_app) {
                                           return EngineProvider::GetInstance(engine_app);
                                         })
        | nullptr;
    ASSERT_NE(engine_provider_ptr, nullptr);
    const auto application_name = _bstr_t{kApplicationName};
    const auto configuration_name = _bstr_t{kConfigurationName};
    session_app = engine_provider_ptr->CreateSession(application_name, configuration_name) | nullptr;
    auto database_app = engine_provider_ptr->GetDatabase(0) | nullptr;
    ASSERT_NE(database_app, nullptr);
    const auto database_provider_ptr = DatabaseProvider::GetInstance(database_app);
    database_provider_ptr->GetAlias().WhenRight([this](auto alias) {
      this->connection_string = std::move(alias);
    });
    database_provider_ptr->GetPassword().WhenRight([this](auto password) {
      this->database_password = std::move(password);
    });
  }

  void TearDown() override {
    //    std::cout << "TearDown" << std::endl;
  }
};

TEST_F(SessionProviderTest, SessionProviderGetInstanceTest) {

  ASSERT_NE(session_app, nullptr);

  const auto session_provider_ptr = SessionProvider::GetInstance(session_app);

  ASSERT_EQ(typeid(session_provider_ptr), typeid(SessionProvider *));

  ASSERT_NE(session_provider_ptr, nullptr);
}

TEST_F(SessionProviderTest, SessionProviderOpenDatabaseConnectionTest) {

  const auto session_provider_ptr = SessionProvider::GetInstance(session_app);

  const auto open_either = session_provider_ptr->OpenDatabaseConnection(connection_string, database_password, PasswordType::Encoded);

  ASSERT_TRUE(open_either);

  ASSERT_EQ(typeid(open_either), typeid(SessionProvider::IDispatchEither));

  open_either.WhenRight([](const auto dispatch_ptr) {
    ASSERT_EQ(typeid(dispatch_ptr), typeid(IDispatch *));
  });
}

TEST_F(SessionProviderTest, SessionProviderUserLoginTest) {
  const auto session_provider_ptr = SessionProvider::GetInstance(session_app);

  const auto open_either = session_provider_ptr->OpenDatabaseConnection(connection_string, database_password, PasswordType::Encoded);

  ASSERT_TRUE(open_either);

  const auto user_name = _bstr_t{test_config::kUserName};
  const auto password = _bstr_t{test_config::kUserPassword};

  const auto login_either = session_provider_ptr->UserLogin(user_name, password);

  ASSERT_TRUE(login_either);

  ASSERT_EQ(typeid(login_either), typeid(SessionProvider::BoolEither));

  login_either.WhenRight([](const auto logged_in) {
    ASSERT_TRUE(logged_in);
  });
}

TEST_F(SessionProviderTest, SessionProviderUserLoginFailTest) {
  const auto session_provider_ptr = SessionProvider::GetInstance(session_app);

  const auto open_either = session_provider_ptr->OpenDatabaseConnection(connection_string, database_password, PasswordType::Encoded);

  ASSERT_TRUE(open_either);

  const auto is_logo_off = session_provider_ptr->UserLogoff();
  ASSERT_TRUE(is_logo_off);

  const auto password = _bstr_t{test_config::kUserPassword} + _bstr_t{test_config::kUserPassword};
  const auto login_either = session_provider_ptr->UserLogin(_bstr_t{test_config::kUserName}, password);

  ASSERT_TRUE(login_either);

  ASSERT_EQ(typeid(login_either), typeid(SessionProvider::BoolEither));

  login_either.WhenRight([](const auto is_logged_in) {
    ASSERT_EQ(typeid(is_logged_in), typeid(bool));
    ASSERT_FALSE(is_logged_in);
  });
}

TEST_F(SessionProviderTest, SessionProviderUserLoggedOnTest) {
  const auto session_provider_ptr = SessionProvider::GetInstance(session_app);

  const auto open_either = session_provider_ptr->OpenDatabaseConnection(connection_string, database_password, PasswordType::Encoded);

  ASSERT_TRUE(open_either);

  const auto login_either = session_provider_ptr->UserLogin(_bstr_t{test_config::kUserName}, _bstr_t{test_config::kUserPassword});

  ASSERT_TRUE(login_either);

  const auto logged_either = session_provider_ptr->UserLoggedOn();

  ASSERT_TRUE(logged_either);

  logged_either.WhenRight([](const auto is_logged_on) {
    ASSERT_TRUE(is_logged_on);
  });
}

TEST_F(SessionProviderTest, SessionProviderUserLogoffTest) {
  const auto session_provider_ptr = SessionProvider::GetInstance(session_app);

  const auto open_either = session_provider_ptr->OpenDatabaseConnection(connection_string, database_password, PasswordType::Encoded);

  ASSERT_TRUE(open_either);

  const auto logoff_either = session_provider_ptr->UserLogoff();

  ASSERT_TRUE(logoff_either);

  logoff_either.WhenRight([](const auto logoff) {
    ASSERT_TRUE(logoff);
  });
}