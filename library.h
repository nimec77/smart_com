#ifndef SMART_COM_LIBRARY_H
#define SMART_COM_LIBRARY_H

#define SMART_COM_LIBRARY_API __declspec(dllexport)

#include <windows.h>
#include <smarteam/gateways/pods/either_pod.h>
#include <iostream>
#include <smarteam/data/repositories/smarteam_repository_imp.h>
#include <smarteam/use_cases/ports/repositories/smarteam_repository.h>
#include <smarteam/gateways/geteway_helper.h>

extern "C" SMART_COM_LIBRARY_API BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID);

extern "C" SMART_COM_LIBRARY_API EitherPod<bool>* RightTest();

extern "C" SMART_COM_LIBRARY_API EitherPod<bool>* LeftTest();

extern "C" SMART_COM_LIBRARY_API EitherPod<bool>* Init();

#endif //SMART_COM_LIBRARY_H
