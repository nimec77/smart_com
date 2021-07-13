//
// Created by nim on 13.07.2021.
//

#include <gtest/gtest.h>
#include <iostream>
#include <smarteam/data/providers/engine_provider.h>
#include <smarteam/data/providers/smarteam_provider.h>

using namespace smarteam;

IDispatch *engine_app = nullptr;

class EngineProviderTest : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    //    std::cout << "SetUpTestSuite" << std::endl;
    CoInitialize(nullptr);
    SmarteamProvider::GetInstance()
        .RightFlatMap([](const auto smarteam_provider_ptr) {
          return smarteam_provider_ptr->GetEngine();
        })
        .WhenRight([](const auto engine_app_ptr) {
          engine_app = engine_app_ptr;
        });
  }

  static void TearDownTestSuite() {
    //    std::cout << "TearDownTestSuite" << std::endl;
    EngineProvider::GetInstance(nullptr).WhenRight([](const auto engine_provider_ptr) {
      engine_provider_ptr->~EngineProvider();
    });
    SmarteamProvider::GetInstance().WhenRight([](const auto smarteam_provider_ptr) {
      smarteam_provider_ptr->~SmarteamProvider();
    });
    engine_app = nullptr;
    CoUninitialize();
  }

  void SetUp() override {
    //    std::cout << "SetUp" << std::endl;
  }

  void TearDown() override {
    //    std::cout << "TearDown" << std::endl;
  }
};

TEST_F(EngineProviderTest, EngineProvederGetInstanceTest) {
  ASSERT_NE(engine_app, nullptr);

  auto engine_either = EngineProvider::GetInstance(engine_app);

  ASSERT_TRUE(engine_either);

  ASSERT_EQ(typeid(engine_either), typeid(EngineProvider::EngineEither));

  engine_either.WhenRight([](const auto engine_provider_ptr) {
    ASSERT_EQ(typeid(engine_provider_ptr), typeid(EngineProvider *));
  });
}
