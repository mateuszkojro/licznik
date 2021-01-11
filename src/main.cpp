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
#include <string>

typedef pixelRGB color;

//@TODO przyjmowanie_arg_z_konsoli
//@TODO --help
//@TODO simple_cli_interface
namespace std {
std::wstring to_wstring(wchar_t znak) { return std::wstring(znak, 1); }
std::wstring to_wstring(pixelRGB pixel) {
  return (const wchar_t *)"R" + to_wstring(pixel.R()) + (const wchar_t *)"G" +
         to_wstring(pixel.G()) + (const wchar_t *)"B" + to_wstring(pixel.B());
}

} // namespace std

int main(int, char **) {

  FreqCounter<wchar_t> licznik_znaki;
  FreqCounter<std::wstring> licznik_slowa;

  FreqCounter<pixelRGB> licznik_color;

  licznik_znaki.create("../files/test.txt");
  licznik_slowa.create("../files/test.txt");
  ppm obraz("../files/lena.ppm");

  for (auto pixel : obraz.get_pixels()) {
    licznik_color.add_data(pixel);
  }

  std::cout << licznik_znaki.get_count().size() << std::endl;
  Csv csv_znaki = licznik_znaki.export_to_csv(std::to_wstring);

  std::cout << licznik_slowa.get_count().size() << std::endl;
  Csv csv_slowa = licznik_slowa.export_to_csv();

  std::cout << licznik_color.get_count().size() << std::endl;
  Csv csv_lena = licznik_color.export_to_csv(std::to_wstring);

  csv_slowa.export_csv("csv_slowa.csv");
  csv_znaki.export_csv("csv_litery.csv");
  //csv_lena.export_csv("csv_lena.csv");

  BarChart chart_slowa(csv_slowa);
  //BarChart chart_lena(csv_lena);
  BarChart chart_znaki(csv_znaki);

  chart_znaki.export_to_ppm(1024, 720, "chart_znaki.ppm");
  //chart_lena.export_to_ppm(csv_lena.number_of_rows(), 720, "chart_lena.ppm");
  chart_slowa.export_to_ppm(1024, 720, "chart_slowa.ppm");

  return 0;
}
