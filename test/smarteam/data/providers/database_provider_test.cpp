//
// Created by nim on 13.07.2021.
//

#include <gtest/gtest.h>
#include <smarteam/data/data_helper.h>
#include <smarteam/data/providers/database_provider.h>
#include <smarteam/data/providers/engine_provider.h>
#include <smarteam/data/providers/smarteam_provider.h>

using namespace smarteam;

class DatabaseProviderTest : public ::testing::Test {
 public:
  IDispatch *database_app{};

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
    if (database_app == nullptr) {
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
    }
  }

  void TearDown() override {
    //    std::cout << "TearDown" << std::endl;
  }
};

TEST_F(DatabaseProviderTest, DatabaseProviderGetInstanceTest) {
  ASSERT_NE(database_app, nullptr);

  auto database_provider_ptr = DatabaseProvider::GetInstance(database_app);

  ASSERT_NE(database_provider_ptr, nullptr);

  ASSERT_EQ(typeid(database_provider_ptr), typeid(DatabaseProvider *));
}

TEST_F(DatabaseProviderTest, DatabaseProviderGetAliasTest) {

  auto database_provider_ptr = DatabaseProvider::GetInstance(database_app);

  auto alias_either = database_provider_ptr->GetAlias();

  ASSERT_TRUE(alias_either);

  ASSERT_EQ(typeid(alias_either), typeid(DatabaseProvider::BstrEither));

  auto str_either = alias_either.RightFlatMap([](const auto alias) {
    EXPECT_EQ(typeid(alias), typeid(_bstr_t));

    return helper::Utf16ToUtf8(alias);
  });

  ASSERT_TRUE(str_either);

  ASSERT_EQ(typeid(str_either), typeid(helper::CharPtrEtiher));

  str_either.WhenRight([](const auto str) {
    ASSERT_EQ(typeid(str), typeid(const char *));
  });
}

TEST_F(DatabaseProviderTest, DatabaseProviderGetPassword) {
  auto database_provider_ptr = DatabaseProvider::GetInstance(database_app);

  auto alias_either = database_provider_ptr->GetPassword();

  ASSERT_TRUE(alias_either);

  ASSERT_EQ(typeid(alias_either), typeid(DatabaseProvider::BstrEither));

  auto str_either = alias_either.RightFlatMap([](const auto alias) {
    EXPECT_EQ(typeid(alias), typeid(_bstr_t));

    return helper::Utf16ToUtf8(alias);
  });

  ASSERT_TRUE(str_either);

  ASSERT_EQ(typeid(str_either), typeid(helper::CharPtrEtiher));

  str_either.WhenRight([](const auto str) {
    ASSERT_EQ(typeid(str), typeid(const char *));
  });
}