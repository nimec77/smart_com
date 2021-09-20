//
// Created by nim on 22.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_GATEWAYS_PODS_EXCEPTION_POD_H_
#define SMART_COM_SRC_SMARTEAM_GATEWAYS_PODS_EXCEPTION_POD_H_

#include <common/pods/enums/exception_type.h>

struct ExceptionPod {
  const ExceptionType exception_type;
  const char *message;
};

#endif//SMART_COM_SRC_SMARTEAM_GATEWAYS_PODS_EXCEPTION_POD_H_
