//
// Created by nim on 05.07.2021.
//

#ifndef SMART_COM_SMARTEAM_DATA_DATA_HELPER_H_
#define SMART_COM_SMARTEAM_DATA_DATA_HELPER_H_

#include <comdef.h>
#include <iostream>
#include <monad/either.h>
#include <smarteam/data/exceptions/class_id_exception.h>
#include <sstream>
#include <windows.h>
#include <smarteam/helper.h>

namespace data_helper {

std::string MakeErrorMessage(const std::string& error, long code);

void SafeRelease(IDispatch& dispatch);

using ClassIdEither = monad::Either<std::exception, CLSID>;
using NamesEither = monad::Either<std::exception, DISPID>;

ClassIdEither GetClassId(const wchar_t *prod_id);

NamesEither GetNames(IDispatch& dispatch, const wchar_t *name);

}// namespace data_helper

#endif//SMART_COM_SMARTEAM_DATA_DATA_HELPER_H_
