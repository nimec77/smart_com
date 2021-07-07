//
// Created by nim on 05.07.2021.
//

#include "smarteam_provider.h"

SmarteamProvider::SmarteamProvider(IDispatch *smarteam_app) : smarteam_app(smarteam_app) {
  std::cout << "SmarteamProvider start" << std::endl;
}

SmarteamProvider::~SmarteamProvider() {
  std::cout << "~SmarteamProvider start" << std::endl;
  data_helper::SafeRelease(smarteam_app);
}

SmarteamProvider SmarteamProvider::SmarteamCreate() {
  std::cout << "SmartreamProvider::SmarteamCreate start" << std::endl;

  auto clsid = data_helper::GetClassId(kSmarTeamProdId);
  IDispatch *app{};
  auto hr = CoCreateInstance(clsid, nullptr, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void **) &app);
  if (FAILED(hr)) {
    data_helper::FailedException("SmarteamProvider::SmarteamCreate CoCreateInstance error:", hr);
  }

  return SmarteamProvider(app);
}
SmarteamProvider SmarteamProvider::SmarteamFromActiveObject() {
  std::cout << "SmartreamProvider::SmarteamFromActiveObject start" << std::endl;

  auto clsid = data_helper::GetClassId(kSmarTeamProdId);

  IUnknown *i_unknown{};
  auto hr = GetActiveObject(clsid, nullptr, &i_unknown);
  if (FAILED(hr)) {
    data_helper::FailedException("SmarteamProvider::SmarteamFromActiveObject GetActiveObject error:", hr);
  }
  IDispatch *app{};
  hr = i_unknown->QueryInterface(IID_IDispatch, (void **) &app);
  i_unknown->Release();
  if (FAILED(hr)) {
    data_helper::FailedException("SmarteamProvider::SmarteamFromActiveObject QueryInterface error:", hr);
  }

  return SmarteamProvider(app);
}
