//
// Created by nim on 22.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_GATEWAYS_GETEWAY_HELPER_H_
#define SMART_COM_SRC_SMARTEAM_GATEWAYS_GETEWAY_HELPER_H_

#include "enums/exception_type.h"
#include "pods/exception_pod.h"
#include <iostream>

namespace gateway_helper {
ExceptionPod PodFromException(const std::exception &exception) {
  const auto exception_type_ = typeid(exception).name();
  const auto str = std::string{exception.what()};
  auto message_ = new char[str.size() + 1];
  std::copy(str.begin(), str.end(), message_);
  message_[str.size()] = '\0';

  if (exception_type_ == typeid(std::invalid_argument).name()) {
    return ExceptionPod{ExceptionType::kInvalidArgument, message_};
  } else if (exception_type_ == typeid(std::runtime_error).name()) {
    return ExceptionPod{ExceptionType::kRuntimeError, message_};
  } else if (exception_type_ == typeid(std::length_error).name()) {
    return ExceptionPod{ExceptionType::kLengthError, message_};
  }

  return ExceptionPod{ExceptionType::kException, message_};
}
}// namespace gateway_helper

#endif//SMART_COM_SRC_SMARTEAM_GATEWAYS_GETEWAY_HELPER_H_
