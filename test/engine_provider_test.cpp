//
// Created by nim on 13.07.2021.
//

#include <gtest/gtest.h>
#include <iostream>
#include <smarteam/constatns.h>
#include <smarteam/data/providers/engine_provider.h>
#include <smarteam/data/providers/smarteam_provider.h>

using namespace smarteam;

class EngineProviderTest : public ::testing::Test {
 public:
  IDispatch* engine_app = nullptr;

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
    if (engine_app == nullptr) {
      engine_app = SmarteamProvider::GetInstance()
          .RightFlatMap([](const auto smarteam_provider_ptr) {
            return smarteam_provider_ptr->GetEngine();
          }) | nullptr;
    }
  }

  void TearDown() override {
    //    std::cout << "TearDown" << std::endl;
  }
};

TEST_F(EngineProviderTest, EngineProviderGetInstanceTest) {

  ASSERT_NE(engine_app, nullptr);

  auto engine_either = EngineProvider::GetInstance(engine_app);

  ASSERT_TRUE(engine_either);

  ASSERT_EQ(typeid(engine_either), typeid(EngineProvider::EngineEither));

  engine_either.WhenRight([](const auto engine_provider_ptr) {
    ASSERT_EQ(typeid(engine_provider_ptr), typeid(EngineProvider *));
  });
}

TEST_F(EngineProviderTest, EngineProviderCreateSessionTest) {
  auto engine_either = EngineProvider::GetInstance(engine_app);

  ASSERT_TRUE(engine_either);

  auto session_either = engine_either.RightFlatMap([](const auto engine_provider_ptr) {
    const auto application_name = _bstr_t(kApplicationName);
    const auto configuration_name = _bstr_t(kConfigurationName);
    return engine_provider_ptr->CreateSession(application_name, configuration_name);
  });

  ASSERT_TRUE(session_either);

  ASSERT_EQ(typeid(session_either), typeid(EngineProvider::IDispatchEither));

  session_either.WhenRight([](const auto session_app_ptr) {
    ASSERT_EQ(typeid(session_app_ptr), typeid(IDispatch *));
  });
}

TEST_F(EngineProviderTest, EngineProviderGetDatabeTest) {
  auto engine_either = EngineProvider::GetInstance(engine_app);

  ASSERT_TRUE(engine_either);

  auto database_either = engine_either.RightFlatMap([](const auto engine_provider_ptr) {
    return engine_provider_ptr->GetDatabase(0);
  });

  ASSERT_TRUE(database_either);

  ASSERT_EQ(typeid(database_either), typeid(EngineProvider::IDispatchEither));

  database_either.WhenRight([](const auto session_app_ptr) {
    ASSERT_EQ(typeid(session_app_ptr), typeid(IDispatch *));
  });
}