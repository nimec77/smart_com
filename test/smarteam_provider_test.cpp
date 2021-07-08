//
// Created by nim on 05.07.2021.
//

#include <smarteam/data/providers/smarteam_provider.h>
#include <gtest/gtest.h>
#include <iostream>

using namespace smarteam;

class TestSmarteamProvider : public ::testing::Test {
 protected:
  void SetUp() override {
    CoInitialize(nullptr);
  }
  void TearDown() override {
    CoUninitialize();
  }
};

//TEST_F(TestSmarteamProvider, SmarteamCreateTest) {
//  auto smarteam_provider = SmarteamProvider::SmarteamCreate();
//  SUCCEED();
//}
//
//TEST_F(TestSmarteamProvider, DISABLED_SmarteamFromActiveObject) {
//  auto smarteam_provider = SmarteamProvider::SmarteamFromActiveObject();
//  SUCCEED();
//}