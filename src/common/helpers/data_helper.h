//
// Created by nim on 05.07.2021.
//

#ifndef SMART_COM_SMARTEAM_DATA_DATA_HELPER_H_
#define SMART_COM_SMARTEAM_DATA_DATA_HELPER_H_

#include <comdef.h>
#include <common/base_types.h>
#include <common/helpers/helper.h>
#include <iostream>
#include <sstream>

namespace data_helper {

std::string MakeErrorMessage(const std::string &error, unsigned long code) noexcept;

void SafeRelease(IDispatch *dispatch) noexcept;

ClassIdEither GetClassId(const wchar_t *prod_id) noexcept;

NamesEither GetNames(IDispatch &dispatch, const wchar_t *name) noexcept;

struct HandleDeleter {
  void operator()(HANDLE handle) const {
    if (handle != INVALID_HANDLE_VALUE) {
      CloseHandle(handle);
    }
  }
};
SharedPtr MakeHandleSharedPtr(HANDLE handle) noexcept;

struct CloseAlgorithm {
  void operator()(BCRYPT_ALG_HANDLE alg_handle) const {
    if (alg_handle) {
      BCryptCloseAlgorithmProvider(alg_handle, 0);
    }
  }
};
SharedPtr MakeAlgorithmSharedPtr(BCRYPT_ALG_HANDLE alg_handle) noexcept;

}// namespace data_helper

#endif//SMART_COM_SMARTEAM_DATA_DATA_HELPER_H_
