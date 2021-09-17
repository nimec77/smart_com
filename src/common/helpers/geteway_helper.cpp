//
// Created by nim on 06.09.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_GATEWAYS_GATEWAY_HELPER_H_
#define SMART_COM_SRC_SMARTEAM_GATEWAYS_GATEWAY_HELPER_H_

#include "geteway_helper.h"

namespace gateway_helper {

helper::HeapUniquePtr message_ptr{nullptr};

const char* StringToCharPtr(const std::string &str) noexcept {
  if (message_ptr) {
    message_ptr.reset();
  }
  message_ptr = helper::MakeHeapUniquePtr(str.size() + 1);
  std::copy(str.begin(), str.end(), message_ptr.get());
  message_ptr.get()[str.size()] = '\0';

  return reinterpret_cast<const char *>(message_ptr.get());
}

ExceptionPod PodFromException(const std::exception &exception) noexcept {
  const auto exception_type_ = typeid(exception).name();

  const auto message_ = StringToCharPtr(exception.what());

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
#endif//SMART_COM_SRC_SMARTEAM_GATEWAYS_GATEWAY_HELPER_H_
