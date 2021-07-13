//
// Created by nim on 07.07.2021.
//

#include "test_config.h"
#include <gtest/gtest.h>
#include <smarteam/constatns.h>
#include <smarteam/data/data_helper.h>
#include <smarteam/data/providers/smarteam_provider.h>

IDispatch *smarteam_app{nullptr};

class DataHelperClassTest : public ::testing::Test {
 public:
 protected:
  static void SetUpTestSuite() {
    //    std::cout << "SetUpTestSuite" << std::endl;
    CoInitialize(nullptr);
    data_helper::GetClassId(smarteam::kSmarTeamProdId).When([](const auto l) { FAIL() << l.what(); }, [](const auto clsid) {
      IDispatch *app{};
      auto hr = CoCreateInstance(clsid, nullptr, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void **) &app);
      if (FAILED(hr)) {
        FAIL() << "Error create Smarteam Object";
      }
      smarteam_app = app; });
  }

  static void TearDownTestSuite() {
    //    std::cout << "TearDownTestSuite" << std::endl;
  }

  void SetUp() override {
  }

  void TearDown() override {
  }
};

TEST(DataHelperTest, MakeErrorMessageTest) {
  const auto message = data_helper::MakeErrorMessage("Error message", -2147221021);

  ASSERT_STREQ(message.c_str(), "Error message 800401e3");
}

TEST(DataHelperTest, GetClassIdFailTest) {
  auto result = data_helper::GetClassId(L"EmptyClassId");

  ASSERT_EQ(typeid(result), typeid(data_helper::ClassIdEither));

  ASSERT_FALSE(result);

  result.WhenLeft([](auto l) {
    EXPECT_EQ(typeid(l), typeid(std::exception));
    const auto message = l.what();
    EXPECT_STREQ(message, "data_helper::GetClassId CLSIDFromProgID error: 800401f3");
  });
}

TEST(DataHelperTest, GetClassIdSuccessTest) {
  auto result = data_helper::GetClassId(smarteam::kSmarTeamProdId);

  ASSERT_EQ(typeid(result), typeid(data_helper::ClassIdEither));

  ASSERT_TRUE(result);

  const CLSID clsid = {};
  auto smart_app = result | clsid;

  ASSERT_EQ(typeid(smart_app), typeid(CLSID));

  ASSERT_NE(smart_app, clsid);
}

TEST_F(DataHelperClassTest, GetNamesTest) {
  auto result = data_helper::GetNames(reinterpret_cast<IDispatch &>(*smarteam_app), smarteam::kSmarTeamEngine);

  ASSERT_TRUE(result);

  ASSERT_EQ(typeid(result), typeid(data_helper::NamesEither));

  result.WhenRight([](const auto dispid) {
    ASSERT_EQ(typeid(dispid), typeid(DISPID));
  });
}

TEST_F(DataHelperClassTest, GetNamesFailTest) {
  auto result = data_helper::GetNames(reinterpret_cast<IDispatch &>(*smarteam_app), test_config::kFakeProdId);

  ASSERT_FALSE(result);

  ASSERT_EQ(typeid(result), typeid(data_helper::NamesEither));

  result.WhenLeft([](const auto l) {
    EXPECT_EQ(typeid(l), typeid(std::exception));
    const auto message = l.what();
    EXPECT_STREQ(message, "data_helper::GetNames GetIDsOfNames 'FakeProdId' error: 80020006");
  });
}