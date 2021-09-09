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

struct HandleDeleter {
  void operator()(HANDLE handle) const {
    if (handle != INVALID_HANDLE_VALUE) {
      CloseHandle(handle);
    }
  }
};

std::string MakeErrorMessage(const std::string &error, unsigned long code) noexcept;

void SafeRelease(IDispatch *dispatch) noexcept;

ClassIdEither GetClassId(const wchar_t *prod_id) noexcept;

NamesEither GetNames(IDispatch &dispatch, const wchar_t *name) noexcept;

HandlePtr MakeHandleSharedPtr(HANDLE handle) noexcept;

}// namespace data_helper

#endif//SMART_COM_SMARTEAM_DATA_DATA_HELPER_H_
