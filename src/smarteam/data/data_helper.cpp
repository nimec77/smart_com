//
// Created by nim on 05.07.2021.
//

#include "data_helper.h"
namespace data_helper {

void FailedException(const std::string &error, long code) {
  std::stringstream str_stream;
  str_stream << error << std::hex << code;
  auto message = str_stream.str();
  std::cerr << message << std::endl;
  throw std::exception(message.c_str());
}
void SafeRelease(IDispatch *dispatch) {
  if (dispatch != nullptr) {
    dispatch->Release();
    dispatch = nullptr;
  }
}

CLSID GetClassId(const wchar_t* prog_id) {
  CLSID clsid;

  auto hr = CLSIDFromProgID(prog_id, &clsid);
  if (FAILED(hr)) {
    FailedException("::get_class_id CLSIDFromProgID error", hr);
  }

  return clsid;
}
}// namespace data_helper
