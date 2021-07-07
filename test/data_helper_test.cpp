//
// Created by nim on 07.07.2021.
//

#include <gtest/gtest.h>
#include <smarteam/data/data_helper.h>

TEST(DataHelperTest, MakeErrorMessageTest) {
  auto message = data_helper::MakeErrorMessage("Error message", -2147221021);
  std::cout << message << std::endl;

  ASSERT_STREQ(message.c_str(), "Error message 800401e3");
}

TEST(DataHelperTest, GetClassIdTest) {
  // 2147746291
  using Result = monad::Either<smarteam::ClassIdException, CLSID>;
  auto result = data_helper::GetClassId(L"EmptyClassId");

  ASSERT_EQ(typeid(result), typeid(Result));

  ASSERT_FALSE(result);

  result.WhenLeft([](auto const l) {
    EXPECT_EQ(typeid(l), typeid(smarteam::ClassIdException));
    auto message = l.what();
    EXPECT_STREQ(message, "::GetClassId CLSIDFromProgID error 800401f3");
    std::exit(0);
  });

  FAIL();
}