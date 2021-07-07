//
// Created by nim on 07.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_DATA_EXCEPTIONS_GETCLASSIDEXCEPTION_H_
#define SMART_COM_SRC_SMARTEAM_DATA_EXCEPTIONS_GETCLASSIDEXCEPTION_H_

#include <iostream>
#include <utility>

namespace smarteam {
class ClassIdException : public std::exception {
 private:
  std::string message_;

 public:
  explicit ClassIdException(std::string message) : message_(std::move(message)){};

  ~ClassIdException() noexcept override = default;

  [[nodiscard]] const char *what() const noexcept override {
    return message_.c_str();
  }
};
}// namespace smarteam

#endif//SMART_COM_SRC_SMARTEAM_DATA_EXCEPTIONS_GETCLASSIDEXCEPTION_H_
