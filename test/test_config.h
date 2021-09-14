//
// Created by nim on 08.07.2021.
//

#ifndef SMART_COM_TEST_TEST_CONFIG_H_
#define SMART_COM_TEST_TEST_CONFIG_H_

#include <common/base_types.h>

namespace test_config {

constexpr auto kFakeProdId = L"FakeProdId";
constexpr auto kUserName = L"����";
constexpr auto kUserPassword = L"123456";
constexpr auto kUserFakePassword = L"1234567";
constexpr auto kTestUtf16Str = L"Test string, �������� ������";
constexpr auto kTestUtf16RuStr = L"�������� ������";
constexpr auto kEncodedTestStr = L"Encode test string ��� �����������";
constexpr auto kDecodedTestStr = L"Decode test string ��� �������������";
constexpr BYTE kKey[] = {
    0xe1, 0x0a, 0xdc, 0x39, 0x49, 0xba, 0x59, 0xab,
    0xbe, 0x56, 0xe0, 0x57, 0xf2, 0x0f, 0x88, 0x3e};
constexpr BYTE kEncodedData[] = {
    0x0d, 0x30, 0x7f, 0xcf, 0x1e, 0xf3, 0x0d, 0x2b,
    0x12, 0xec, 0x57, 0xed, 0xf2, 0x55, 0x8c, 0x00,
    0xee, 0xb0, 0xd3, 0x15, 0x76, 0xe4, 0xcc, 0xf1,
    0x95, 0x5a, 0x25, 0xcf, 0xea, 0xce, 0x77, 0xcb,
    0x8d, 0xef, 0x5d, 0xd0, 0x0c, 0xfd, 0x5a, 0x7e,
    0x71, 0xc4, 0x66, 0xc3, 0x5a, 0x81, 0x0e, 0xe2};

}// namespace test_config

#endif//SMART_COM_TEST_TEST_CONFIG_H_
