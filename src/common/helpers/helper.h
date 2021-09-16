//
// Created by nim on 09.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_DATA_HELPER_H_
#define SMART_COM_SRC_SMARTEAM_DATA_HELPER_H_

#include <comdef.h>
#include <iostream>
#include <smarteam/constatns.h>
#include <sstream>
#include <common/base_types.h>

namespace helper {

StringEither Utf16ToUtf8(const wchar_t *utf16_str) noexcept;

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

struct DestroyHeap {
  void operator()(PBYTE pointer) const {
    if (pointer) {
      HeapFree(GetProcessHeap(), 0, pointer);
    }
  }
};
using HeapUniquePtr = std::unique_ptr<BYTE, DestroyHeap>;
HeapUniquePtr MakeHeapUniquePtr(DWORD size) noexcept;

struct DestroyKey {
  void operator()(BCRYPT_KEY_HANDLE key_handle) const {
    if (key_handle) {
      BCryptDestroyKey(key_handle);
    }
  }
};
using KeyUniqueHandlePtr = std::unique_ptr<void, DestroyKey>;
KeyUniqueHandlePtr MakeKeyHandleUniquePtr(BCRYPT_KEY_HANDLE key_handle) noexcept;


}

#endif//SMART_COM_SRC_SMARTEAM_DATA_HELPER_H_
