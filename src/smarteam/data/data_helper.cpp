//
// Created by nim on 05.07.2021.
//

#include "data_helper.h"
namespace data_helper {

std::string MakeErrorMessage(const std::string& error, long code) {
  std::stringstream str_stream;
  str_stream << error << " " << std::hex << code;

  return str_stream.str();
}

void SafeRelease(IDispatch *dispatch) {
  if (dispatch != nullptr) {
    dispatch->Release();
    dispatch = nullptr;
  }
}

monad::Either<smarteam::ClassIdException, CLSID> GetClassId(const wchar_t* prog_id) {
  CLSID clsid;

  using Result = monad::Either<smarteam::ClassIdException, CLSID>;
  auto hr = CLSIDFromProgID(prog_id, &clsid);
  if (FAILED(hr)) {
    auto message = MakeErrorMessage("::GetClassId CLSIDFromProgID error", hr);
    return Result{monad::left(smarteam::ClassIdException(message))};
  }

  return Result::RightOf(clsid);
}
}// namespace data_helper
