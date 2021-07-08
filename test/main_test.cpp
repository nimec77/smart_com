//
// Created by nim on 07.07.2021.
//

#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
  constexpr auto kInfo = R"(
Для корректной работы тестов необходимо устанновленый SmaTeam на компьюетере.
А так же учетные данны существующего пользователя SmarTeam в файле 'test_config.h'
)";
  system("chcp 65001");
  std::cout << kInfo << std::endl;
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}