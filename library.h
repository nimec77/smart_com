#ifndef SMART_COM_LIBRARY_H
#define SMART_COM_LIBRARY_H

#define SMART_COM_LIBRARY_API __declspec(dllexport)

#include <app_context.h>
#include <iostream>
#include <windows.h>

AppContext app_context {};

extern "C" SMART_COM_LIBRARY_API BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID);

extern "C" SMART_COM_LIBRARY_API EitherPod<bool>* RightTest() noexcept;

extern "C" SMART_COM_LIBRARY_API EitherPod<bool>* LeftTest() noexcept;

extern "C" SMART_COM_LIBRARY_API EitherPod<bool>* Init() noexcept;

extern "C" SMART_COM_LIBRARY_API EitherPod<bool>* Release() noexcept;

extern "C" SMART_COM_LIBRARY_API EitherPod<bool>* UserLogoff() noexcept;

extern "C" SMART_COM_LIBRARY_API EitherPod<bool>* UserLogin(const wchar_t* username, const wchar_t* password) noexcept;

extern "C" SMART_COM_LIBRARY_API EitherPod<const char *>* GetSid() noexcept;

extern "C" SMART_COM_LIBRARY_API EitherPod<const char *>* Encode(const wchar_t* text) noexcept;

extern "C" SMART_COM_LIBRARY_API EitherPod<const char *>* Decode(const wchar_t* hex_text) noexcept;

#endif //SMART_COM_LIBRARY_H
