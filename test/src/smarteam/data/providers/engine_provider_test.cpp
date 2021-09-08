//
// Created by nim on 13.07.2021.
//

#include <gtest/gtest.h>
#include <iostream>
#include <smarteam/constatns.h>
#include <smarteam/data/providers/engine_provider.h>
#include <smarteam/data/providers/smarteam_provider.h>

using namespace smarteam;

IDispatch *engine_app{};

class EngineProviderTest : public ::testing::Test {
 public:

 protected:
  static void SetUpTestSuite() {
    //    std::cout << "SetUpTestSuite" << std::endl;
    CoInitialize(nullptr);
    engine_app = SmarteamProvider::GetInstance()
        .RightFlatMap([](const auto smarteam_provider_ptr) {
          return smarteam_provider_ptr->GetEngine();
        })
        | nullptr;
    ASSERT_NE(engine_app, nullptr);
  }

  static void TearDownTestSuite() {
    //    std::cout << "TearDownTestSuite" << std::endl;
  }

  void SetUp() override {
    //    std::cout << "SetUp" << std::endl;
  }

  void TearDown() override {
    //    std::cout << "TearDown" << std::endl;
  }
};

TEST_F(EngineProviderTest, EngineProviderGetInstanceTest) {

  const auto engine_provider_ptr_ = EngineProvider::GetInstance(engine_app);

  ASSERT_EQ(typeid(engine_provider_ptr_), typeid(EngineProvider::EngineProviderPtr));

  ASSERT_TRUE(engine_provider_ptr_);
}

TEST_F(EngineProviderTest, EngineProviderCreateSessionTest) {
  const auto engine_provider_ptr_ = EngineProvider::GetInstance(engine_app);

  const auto session_either_ = engine_provider_ptr_->CreateSession(_bstr_t{kApplicationName}, _bstr_t{kConfigurationName});

  ASSERT_TRUE(session_either_);

  ASSERT_EQ(typeid(session_either_), typeid(EngineProvider::IDispatchEither));

  session_either_.WhenRight([](const auto session_app_ptr) {
    ASSERT_EQ(typeid(session_app_ptr), typeid(IDispatch *));

    ASSERT_NE(session_app_ptr, nullptr);
  });
}

TEST_F(EngineProviderTest, EngineProviderGetDatabeTest) {
  const auto engine_provider_ptr_ = EngineProvider::GetInstance(engine_app);

  const auto database_either_ = engine_provider_ptr_->GetDatabase(0);

  ASSERT_TRUE(database_either_);

  ASSERT_EQ(typeid(database_either_), typeid(EngineProvider::IDispatchEither));

  database_either_.WhenRight([](const auto session_app_ptr) {
    ASSERT_EQ(typeid(session_app_ptr), typeid(IDispatch *));

    ASSERT_NE(session_app_ptr, nullptr);
  });
}