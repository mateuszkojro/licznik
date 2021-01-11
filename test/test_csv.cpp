#include "Csv.h"
#include <catch2/catch.hpp>
#include <string>
#include <vector>

bool compare_vec(std::vector<std::wstring> a, std::vector<std::wstring> b) {
  if (a.size() != b.size())
    return false;
  for (unsigned i = 0; i < a.size(); i++) {
    if (a[i] != b[i])
      return false;
  }
  return true;
}

TEST_CASE("Save to then read it are the same", "[Csv]") {

  std::vector<std::wstring> values = {
      (const wchar_t *)"Hello", (const wchar_t *)"world",
      (const wchar_t *)"jeden", (const wchar_t *)"dwa"};

  Config config;

  config.number_of_columns = 2;

  Csv plik(values, config);

  auto file_path = "../test/tmp/test.txt";

  plik.export_csv(file_path);

  Csv plik2({}, config);

  plik.read_csv(file_path);

  auto result = plik2.get_data();

  REQUIRE(compare_vec(values, result));
}
