//
// Created by nim on 13.07.2021.
//

#include <gtest/gtest.h>
#include <smarteam/data/data_helper.h>
#include <smarteam/data/providers/database_provider.h>
#include <smarteam/data/providers/engine_provider.h>
#include <smarteam/data/providers/smarteam_provider.h>

using namespace smarteam;

IDispatch *database_app{};

class DatabaseProviderTest : public ::testing::Test {
 public:

 protected:
  static void SetUpTestSuite() {
    //    std::cout << "SetUpTestSuite" << std::endl;
    CoInitialize(nullptr);
    database_app = SmarteamProvider::GetInstance()
        .RightFlatMap([](const auto smarteam_provider_ptr) {
          return smarteam_provider_ptr->GetEngine();
        })
        .RightMap([](const auto engine_app) {
          return EngineProvider::GetInstance(engine_app);
        })
        .RightFlatMap([](const auto engine_provider_ptr) {
          return engine_provider_ptr->GetDatabase(0);
        })
        | nullptr;
    ASSERT_NE(database_app, nullptr);
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

TEST_F(DatabaseProviderTest, DatabaseProviderGetInstanceTest) {
  ASSERT_NE(database_app, nullptr);

  const auto database_provider_ptr_ = DatabaseProvider::GetInstance(database_app);

  ASSERT_NE(database_provider_ptr_, nullptr);

  ASSERT_EQ(typeid(database_provider_ptr_), typeid(DatabaseProvider *));
}

TEST_F(DatabaseProviderTest, DatabaseProviderGetAliasTest) {

  const auto database_provider_ptr_ = DatabaseProvider::GetInstance(database_app);

  const auto alias_either_ = database_provider_ptr_->GetAlias();

  ASSERT_TRUE(alias_either_);

  ASSERT_EQ(typeid(alias_either_), typeid(DatabaseProvider::BstrEither));

  const auto str_either_ = alias_either_.RightFlatMap([](const auto alias) {
    EXPECT_EQ(typeid(alias), typeid(_bstr_t));

    return helper::Utf16ToUtf8(alias);
  });

  ASSERT_TRUE(str_either_);

  ASSERT_EQ(typeid(str_either_), typeid(helper::CharPtrEtiher));

  str_either_.WhenRight([](const auto str) {
    ASSERT_EQ(typeid(str), typeid(const char *));
  });
}

TEST_F(DatabaseProviderTest, DatabaseProviderGetPassword) {
  const auto database_provider_ptr_ = DatabaseProvider::GetInstance(database_app);

  const auto alias_either_ = database_provider_ptr_->GetPassword();

  ASSERT_TRUE(alias_either_);

  ASSERT_EQ(typeid(alias_either_), typeid(DatabaseProvider::BstrEither));

  const auto str_either_ = alias_either_.RightFlatMap([](const auto alias) {
    EXPECT_EQ(typeid(alias), typeid(_bstr_t));

    return helper::Utf16ToUtf8(alias);
  });

  ASSERT_TRUE(str_either_);

  ASSERT_EQ(typeid(str_either_), typeid(helper::CharPtrEtiher));

  str_either_.WhenRight([](const auto str) {
    ASSERT_EQ(typeid(str), typeid(const char *));
  });
}