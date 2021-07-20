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

IDispatch *session_app{};
_bstr_t connection_string;
_bstr_t database_password;

class SessionProviderTest : public ::testing::Test {
 public:

 protected:
  static void SetUpTestSuite() {
    //    std::cout << "SetUpTestSuite" << std::endl;
    CoInitialize(nullptr);
    const auto engine_provider_ptr_ = SmarteamProvider::GetInstance()
        .RightFlatMap([](const auto smarteam_provider_ptr) {
          return smarteam_provider_ptr->GetEngine();
        })
        .RightMap([](const auto engine_app) {
          return EngineProvider::GetInstance(engine_app);
        })
        | nullptr;
    ASSERT_NE(engine_provider_ptr_, nullptr);
    const auto application_name = _bstr_t{kApplicationName};
    const auto configuration_name = _bstr_t{kConfigurationName};
    session_app = engine_provider_ptr_->CreateSession(application_name, configuration_name) | nullptr;
    auto database_app = engine_provider_ptr_->GetDatabase(0) | nullptr;
    ASSERT_NE(database_app, nullptr);
    const auto database_provider_ptr_ = DatabaseProvider::GetInstance(database_app);
    database_provider_ptr_->GetAlias().WhenRight([](auto alias) {
      connection_string = std::move(alias);
    });
    database_provider_ptr_->GetPassword().WhenRight([](auto password) {
      database_password = std::move(password);
    });
  }

  static void TearDownTestSuite() {
    //    std::cout << "TearDownTestSuite" << std::endl;
  }

  void SetUp() override {
    //    std::cout << "SetUp" << std::endl;
    if (session_app != nullptr) {
      return;
    }
  }

  void TearDown() override {
    //    std::cout << "TearDown" << std::endl;
  }
};

TEST_F(SessionProviderTest, SessionProviderGetInstanceTest) {

  const auto session_provider_ptr_ = SessionProvider::GetInstance(session_app);

  ASSERT_EQ(typeid(session_provider_ptr_), typeid(SessionProvider *));

  ASSERT_NE(session_provider_ptr_, nullptr);
}

TEST_F(SessionProviderTest, SessionProviderOpenDatabaseConnectionTest) {

  const auto session_provider_ptr_ = SessionProvider::GetInstance(session_app);

  const auto open_either_ = session_provider_ptr_->OpenDatabaseConnection(connection_string, database_password, PasswordType::kEncoded);

  ASSERT_TRUE(open_either_);

  ASSERT_EQ(typeid(open_either_), typeid(SessionProvider::IDispatchEither));

  open_either_.WhenRight([](const auto dispatch_ptr) {
    ASSERT_EQ(typeid(dispatch_ptr), typeid(IDispatch *));
  });
}

TEST_F(SessionProviderTest, SessionProviderUserLoginTest) {
  const auto session_provider_ptr_ = SessionProvider::GetInstance(session_app);

  const auto open_either_ = session_provider_ptr_->OpenDatabaseConnection(connection_string, database_password, PasswordType::kEncoded);

  ASSERT_TRUE(open_either_);

  const auto login_either_ = session_provider_ptr_->UserLogin(_bstr_t{test_config::kUserName}, _bstr_t{test_config::kUserPassword});

  ASSERT_TRUE(login_either_);

  ASSERT_EQ(typeid(login_either_), typeid(SessionProvider::BoolEither));

  login_either_.WhenRight([](const auto logged_in) {
    ASSERT_TRUE(logged_in);
  });
}

TEST_F(SessionProviderTest, SessionProviderUserLoginFailTest) {
  const auto session_provider_ptr_ = SessionProvider::GetInstance(session_app);

  const auto open_either_ = session_provider_ptr_->OpenDatabaseConnection(connection_string, database_password, PasswordType::kEncoded);

  ASSERT_TRUE(open_either_);

  const auto is_logo_off_ = session_provider_ptr_->UserLogoff();
  ASSERT_TRUE(is_logo_off_);

  const auto password_ = _bstr_t{test_config::kUserPassword} + _bstr_t{"1"};
  const auto login_either_ = session_provider_ptr_->UserLogin(_bstr_t{test_config::kUserName}, password_);

  ASSERT_TRUE(login_either_);

  ASSERT_EQ(typeid(login_either_), typeid(SessionProvider::BoolEither));

  login_either_.WhenRight([](const auto is_logged_in) {
    ASSERT_EQ(typeid(is_logged_in), typeid(bool));
    ASSERT_FALSE(is_logged_in);
  });
}

TEST_F(SessionProviderTest, SessionProviderUserLoggedOnTest) {
  const auto session_provider_ptr_ = SessionProvider::GetInstance(session_app);

  const auto open_either_ = session_provider_ptr_->OpenDatabaseConnection(connection_string, database_password, PasswordType::kEncoded);

  ASSERT_TRUE(open_either_);

  const auto login_either_ = session_provider_ptr_->UserLogin(_bstr_t{test_config::kUserName}, _bstr_t{test_config::kUserPassword});

  ASSERT_TRUE(login_either_);

  const auto logged_either_ = session_provider_ptr_->UserLoggedOn();

  ASSERT_TRUE(logged_either_);

  logged_either_.WhenRight([](const auto is_logged_on) {
    ASSERT_TRUE(is_logged_on);
  });
}

TEST_F(SessionProviderTest, SessionProviderUserLogoffTest) {
  const auto session_provider_ptr_ = SessionProvider::GetInstance(session_app);

  const auto open_either_ = session_provider_ptr_->OpenDatabaseConnection(connection_string, database_password, PasswordType::kEncoded);

  ASSERT_TRUE(open_either_);

  const auto logoff_either_ = session_provider_ptr_->UserLogoff();

  ASSERT_TRUE(logoff_either_);

  logoff_either_.WhenRight([](const auto logoff) {
    ASSERT_TRUE(logoff);
  });
}