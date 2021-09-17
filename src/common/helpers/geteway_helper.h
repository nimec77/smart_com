//
// Created by nim on 22.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_GATEWAYS_GETEWAY_HELPER_H_
#define SMART_COM_SRC_SMARTEAM_GATEWAYS_GETEWAY_HELPER_H_

#include <common/helpers/helper.h>
#include <smarteam/gateways/enums/exception_type.h>
#include <common/pods/exception_pod.h>
#include <iostream>

namespace gateway_helper {
ExceptionPod PodFromException(const std::exception &exception) noexcept;

const char* StringToCharPtr(const std::string &str) noexcept;
}// namespace gateway_helper

#endif//SMART_COM_SRC_SMARTEAM_GATEWAYS_GETEWAY_HELPER_H_
