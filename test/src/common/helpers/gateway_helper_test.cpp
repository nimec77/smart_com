//
// Created by nim on 22.07.2021.
//

#include <common/helpers/geteway_helper.h>
#include <gtest/gtest.h>

TEST(GatewayHelperTest, TypeFromInvalidArgumentTest) {
  const auto message = "Invalid argument";
  const auto exception_pod_ = gateway_helper::PodFromException(std::invalid_argument{message});

  ASSERT_EQ(typeid(exception_pod_), typeid(ExceptionPod));

  ASSERT_EQ(exception_pod_.exception_type, ExceptionType::kInvalidArgument);
  ASSERT_STREQ(exception_pod_.message, message);
}

TEST(GatewayHelperTest, TypeFromRuntimeErrorTest) {
  const auto message = "Runtime Error";
  const auto exception_pod_ = gateway_helper::PodFromException(std::runtime_error{message});

  ASSERT_EQ(typeid(exception_pod_), typeid(ExceptionPod));

  ASSERT_EQ(exception_pod_.exception_type, ExceptionType::kRuntimeError);
  ASSERT_STREQ(exception_pod_.message, message);
}

TEST(GatewayHelperTest, TypeFromLengthErrorTest) {
  const auto message = "Length Error";
  const auto exception_pod_ = gateway_helper::PodFromException(std::length_error{message});

  ASSERT_EQ(typeid(exception_pod_), typeid(ExceptionPod));

  ASSERT_EQ(exception_pod_.exception_type, ExceptionType::kLengthError);
  ASSERT_STREQ(exception_pod_.message, message);
}

TEST(GatewayHelperTest, TypeFromExceptionTest) {
  const auto exception_pod_ = gateway_helper::PodFromException(std::exception{});

  ASSERT_EQ(typeid(exception_pod_), typeid(ExceptionPod));

  ASSERT_EQ(exception_pod_.exception_type, ExceptionType::kException);
  std::cout << exception_pod_.message << std::endl;
  ASSERT_STREQ(exception_pod_.message, "Unknown exception");
}

TEST(GatewayHelperTest, StringToCharPtrTest) {
  const auto str_ = std::string{"Test string"};
  const auto result_ = gateway_helper::StringToCharPtr(str_);

  ASSERT_EQ(typeid(result_), typeid(const char *));

  ASSERT_STREQ(result_, str_.c_str());
}
