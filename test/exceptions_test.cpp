//
// Created by nim on 07.07.2021.
//

#include <gtest/gtest.h>
#include <smarteam/data/exceptions/class_id_exception.h>

TEST(ExceptionsTest, ClassIdExceptionTest) {
  constexpr auto kErrorMessage = "Error message!";
  const auto exception = smarteam::ClassIdException(kErrorMessage);
  ASSERT_EQ(typeid(exception), typeid(smarteam::ClassIdException));

  ASSERT_STREQ(exception.what(), kErrorMessage);
}

TEST(ExceptionsTest, CatchClassIdExceptoinTest) {
  constexpr auto kErrorMessage = "Error message!";
  try {
    throw smarteam::ClassIdException(kErrorMessage);
  } catch (const smarteam::ClassIdException &e) {
    ASSERT_EQ(typeid(e), typeid(smarteam::ClassIdException));

    ASSERT_STREQ(e.what(), kErrorMessage);
  }
}