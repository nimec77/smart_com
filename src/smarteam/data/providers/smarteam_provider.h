//
// Created by nim on 05.07.2021.
//

#ifndef SMART_COM_SMARTEAM_DATA_PROVIDERS_SMARTEAM_PROVIDER_H_
#define SMART_COM_SMARTEAM_DATA_PROVIDERS_SMARTEAM_PROVIDER_H_

#include <smarteam/constatns.h>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <smarteam/data/data_helper.h>

class SmarteamProvider {
 public:
  static SmarteamProvider SmarteamCreate();

  static SmarteamProvider SmarteamFromActiveObject();

  virtual ~SmarteamProvider();

 private:
  IDispatch *smarteam_app{};
  explicit SmarteamProvider(IDispatch *smarteam_app);
};

#endif//SMART_COM_SMARTEAM_DATA_PROVIDERS_SMARTEAM_PROVIDER_H_
