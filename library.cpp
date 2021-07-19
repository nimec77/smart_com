#include "library.h"

#include <iostream>

void hello() {
  std::cout << "Hello, World!" << std::endl;
}

BOOL DllMain(HINSTANCE, DWORD const reason, LPVOID) {
  switch (reason) {
    case DLL_PROCESS_ATTACH:
      CoInitialize(nullptr);
      break;

      //    case DLL_THREAD_ATTACH:
      //      break;

      //    case DLL_THREAD_DETACH:
      //      break;

    case DLL_PROCESS_DETACH:
      CoUninitialize();
      break;

    default:
      break;
  }
  return TRUE;
}
