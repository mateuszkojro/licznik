// Licznik czestotliwosci

#include "BarChart.h"
#include "Csv.h"
#include "FreqCounter.h"
#include "Visualizer.h"
#include "pixel.h"
#include "pixelRGB.h"
#include "ppm.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <ostream>
#include <random>
#include <string>

typedef pixelRGB color;

//@TODO przyjmowanie_arg_z_konsoli
//@TODO --help
//@TODO simple_cli_interface
namespace std {
std::wstring to_wstring(wchar_t znak) { return std::wstring(znak, 1); }
std::wstring to_wstring(pixelRGB pixel) {
  return L"R" + to_wstring(pixel.R()) + L"G" + to_wstring(pixel.G()) + L"B" +
         to_wstring(pixel.B());
}
std::wstring to_wstring(std::wstring text) { return text; }

} // namespace std

bool operator==(std::string a, std::string b) {
  std::clog << "my ==" << std::endl;
  if (a.size() != b.size())
    return false;
  for (unsigned i = 0; i < a.size(); i++) {
    if (a[i] != b[i])
      return false;
  }
  return true;
}

template <class Type> void maybe_export_csv(bool flag, Type data) {
  if (flag) {
    std::clog << "Genearting csv please wait" << std::endl;
    Csv csv = data.export_to_csv(std::to_wstring);
    csv.export_csv("out.csv");
    std::clog << "Done" << std::endl;
  }
}

template <class Type> void maybe_export_ppm(bool flag, Type data) {
  if (flag) {
    std::clog << "Genearting ppm please wait" << std::endl;
    Csv csv = data.export_to_csv(std::to_wstring);
    BarChart chart(csv);
    chart.export_to_ppm(2000, 2000,
                        "out.ppm");
    std::clog << "Done" << std::endl;
  }
}

int main(int argc, char **argv) {

  bool bar_flag = false;
  bool csv_flag = false;
  // bool show_flag;

  for (int i = 1; i < argc + 1; i++) {

    bar_flag = (argv[i] == (std::string) "--bar" ? true : bar_flag);
    csv_flag = (argv[i] == (std::string) "--csv" ? true : csv_flag);
    // sho_flag = (argv[i] == (std::string) "--bar");

    if (argv[i] == (std::string) "--chars") {
      FreqCounter<wchar_t> licznik;
      licznik.create(argv[i + 1]);
      maybe_export_csv(csv_flag, licznik);
      maybe_export_ppm(bar_flag, licznik);
      return 0;
    }
    if (argv[i] == (std::string) "--colors") {
      FreqCounter<pixelRGB> licznik;
      licznik.create(argv[i + 1]);
      maybe_export_csv(csv_flag, licznik);
      maybe_export_ppm(bar_flag, licznik);
      return 0;
    }
    if (argv[i] == (std::string) "--numbers") {
      FreqCounter<int> licznik;
      licznik.create(argv[i + 1]);
      maybe_export_csv(csv_flag, licznik);
      maybe_export_ppm(bar_flag, licznik);
      return 0;
    }
    if (argv[i] == (std::string) "--words") {
      FreqCounter<std::wstring> licznik;
      licznik.create(argv[i + 1]);
      maybe_export_csv(csv_flag, licznik);
      maybe_export_ppm(bar_flag, licznik);
      return 0;
    }
    if (argv[i] == (std::string) "--random") {
      FreqCounter<int> licznik;
      std::default_random_engine generator;
      std::uniform_int_distribution<int> distribution(1, 1000);
      for (int i = 0; i < 1000000; i++) {
        licznik.add_data(distribution(generator));
      }
      maybe_export_csv(csv_flag, licznik);
      maybe_export_ppm(bar_flag, licznik);
      return 0;
    }
  }

  std::cout << "To jest help" << std::endl;

  return 0;
}
