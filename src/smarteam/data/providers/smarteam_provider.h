//
// Created by nim on 05.07.2021.
//

#ifndef SMART_COM_SMARTEAM_DATA_PROVIDERS_SMARTEAM_PROVIDER_H_
#define SMART_COM_SMARTEAM_DATA_PROVIDERS_SMARTEAM_PROVIDER_H_

#include <iostream>
#include <smarteam/constatns.h>
#include <smarteam/data/data_helper.h>
#include <sstream>
#include <windows.h>

namespace smarteam {
class SmarteamProvider {
 public:
  static SmarteamProvider SmarteamCreate();

  static SmarteamProvider SmarteamFromActiveObject();

  virtual ~SmarteamProvider();

 private:
  IDispatch *smarteam_app{};
  explicit SmarteamProvider(IDispatch *smarteam_app);
};
}// namespace smarteam

#endif//SMART_COM_SMARTEAM_DATA_PROVIDERS_SMARTEAM_PROVIDER_H_
