//
// Created by nim on 09.07.2021.
//

#include "../../../test_config.h"
#include <common/helpers/helper.h>
#include <gtest/gtest.h>
#include <smarteam/constatns.h>
#include <smarteam/data/providers/smarteam_provider.h>

IDispatch *smarteam_app{nullptr};

class DataHelperClassTest : public ::testing::Test {
 public:
 protected:
  static void SetUpTestSuite() {
   //    std::cout << "SetUpTestSuite" << std::endl;
   CoInitialize(nullptr);
   helper::GetClassId(smarteam::kSmarTeamProdId)
   .When([](const auto l) { FAIL() << l.what(); },
         [](const auto clsid) {
     IDispatch *app{};
     auto hr = CoCreateInstance(clsid, nullptr, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void **) &app);
     if (FAILED(hr)) {
       FAIL() << "Error create Smarteam Object";
     }
     smarteam_app = app;
   });
 }

 static void TearDownTestSuite() {
   //    std::cout << "TearDownTestSuite" << std::endl;
 }

 void SetUp() override {
 }

 void TearDown() override {
 }
};

TEST(HelperTest, Utf16ToUtf8Test) {
  const auto result_en = helper::Utf16ToUtf8(L"Test string");

  ASSERT_TRUE(result_en);

  const auto result_en_ = result_en | std::string{};
  ASSERT_STREQ(result_en_.c_str(), "Test string");

  const auto result_ru = helper::Utf16ToUtf8(test_config::kTestUtf16RuStr);

  ASSERT_TRUE(result_ru);

  const auto result_ru_ = result_ru | std::string{};
  ASSERT_STREQ(result_ru_.c_str(), "Тестовая строка");

  const auto result = helper::Utf16ToUtf8(test_config::kTestUtf16Str);

  ASSERT_TRUE(result);

  const auto result_ = result | std::string{};
  ASSERT_STREQ(result_.c_str(), "Test string, Тестовая строка");
}

TEST(HelperTest, Utf16ToUtf8FailTest) {
  const auto result = helper::Utf16ToUtf8(nullptr);

  ASSERT_FALSE(result);

  result.WhenLeft([](auto l) {
    EXPECT_EQ(typeid(l), typeid(std::exception));
    const auto message = l.what();
    EXPECT_STREQ(message, "helper::Utf16ToUtf8 WideCharToMultiByte error get string length");
  });
}

TEST(DataHelperTest, MakeErrorMessageTest) {
  const auto message_ = helper::MakeErrorMessage("Error message", -2147221021);

  ASSERT_STREQ(message_.c_str(), "Error message 800401e3");
}

TEST(DataHelperTest, GetClassIdFailTest) {
  const auto result_ = helper::GetClassId(L"EmptyClassId");

  ASSERT_EQ(typeid(result_), typeid(ClassIdEither));

  ASSERT_FALSE(result_);

  result_.WhenLeft([](auto l) {
    EXPECT_EQ(typeid(l), typeid(std::exception));
    const auto message = l.what();
    EXPECT_STREQ(message, "data_helper::GetClassId CLSIDFromProgID error: 800401f3");
  });
}

TEST(DataHelperTest, GetClassIdSuccessTest) {
  const auto result_ = helper::GetClassId(smarteam::kSmarTeamProdId);

  ASSERT_EQ(typeid(result_), typeid(ClassIdEither));

  ASSERT_TRUE(result_);

  const CLSID kClsidEmpty = {};
  auto smart_app_ = result_ | kClsidEmpty;

  ASSERT_EQ(typeid(smart_app_), typeid(CLSID));

  ASSERT_NE(smart_app_, kClsidEmpty);
}

TEST_F(DataHelperClassTest, GetNamesTest) {
  const auto result_ = helper::GetNames(reinterpret_cast<IDispatch &>(*smarteam_app), smarteam::kSmarTeamEngine);

  ASSERT_TRUE(result_);

  ASSERT_EQ(typeid(result_), typeid(NamesEither));

  result_.WhenRight([](const auto dispid) {
    ASSERT_EQ(typeid(dispid), typeid(DISPID));
  });
}

TEST_F(DataHelperClassTest, GetNamesFailTest) {
  const auto result_ = helper::GetNames(reinterpret_cast<IDispatch &>(*smarteam_app), test_config::kFakeProdId);

  ASSERT_FALSE(result_);

  ASSERT_EQ(typeid(result_), typeid(NamesEither));

  result_.WhenLeft([](const auto l) {
    EXPECT_EQ(typeid(l), typeid(std::exception));
    const auto message = l.what();
    EXPECT_STREQ(message, "data_helper::GetNames GetIDsOfNames 'FakeProdId' error: 80020006");
  });
}