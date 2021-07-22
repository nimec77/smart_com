//
// Created by nim on 22.07.2021.
//

#include <gtest/gtest.h>
#include <smarteam/gateways/geteway_helper.h>
#include <smarteam/gateways/enums/exception_type.h>
#include <smarteam/gateways/pods/exception_pod.h>

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

