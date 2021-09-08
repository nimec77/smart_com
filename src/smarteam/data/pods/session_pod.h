//
// Created by nim on 15.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_DATA_PODS_SESSION_POD_H_
#define SMART_COM_SRC_SMARTEAM_DATA_PODS_SESSION_POD_H_

#include <smarteam/data/providers/smarteam_provider.h>
#include <smarteam/data/providers/engine_provider.h>
#include <smarteam/data/providers/database_provider.h>
#include <smarteam/data/providers/session_provider.h>

using namespace smarteam;
using EngineProviderPtr = std::shared_ptr<EngineProvider>;

struct SessionPod {
  EngineProviderPtr engine_provider_ptr;
  DatabaseProvider* database_provider_ptr;
  SessionProvider* session_provider_ptr;
  _bstr_t alias;
  _bstr_t database_password;
};

#endif//SMART_COM_SRC_SMARTEAM_DATA_PODS_SESSION_POD_H_
