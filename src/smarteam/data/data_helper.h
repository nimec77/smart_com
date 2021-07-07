//
// Created by nim on 05.07.2021.
//

#ifndef SMART_COM_SMARTEAM_DATA_DATA_HELPER_H_
#define SMART_COM_SMARTEAM_DATA_DATA_HELPER_H_

#include <comdef.h>
#include <iostream>
#include <sstream>
#include <windows.h>

namespace data_helper {

void FailedException(const std::string &error, long code);

void SafeRelease(IDispatch *dispatch);

CLSID GetClassId(const wchar_t* prog_id);

}// namespace data_helper

#endif//SMART_COM_SMARTEAM_DATA_DATA_HELPER_H_
