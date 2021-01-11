// Licznik czestotliwosci

#include "BarChart.h"
#include "Csv.h"
#include "FreqCounter.h"
#include "Visualizer.h"
#include <cstdio>
#include <iostream>
#include <string>

//@TODO przyjmowanie_arg_z_konsoli
//@TODO --help
//@TODO simple_cli_interface

std::string char_to_string(char znak){
  return std::string(znak,1);
}

int main(int, char **) {

  FreqCounter<char> licznik_znaki;
  FreqCounter<std::string> licznik_slowa;

  licznik_znaki.create("../files/biblia-en.txt");
  licznik_slowa.create("../files/biblia-en.txt");

 // std::cout << licznik_znaki.get_count().size() << std::endl;
 // Csv csv_znaki = licznik_znaki.export_to_csv(char_to_string);

  std::cout << licznik_slowa.get_count().size() << std::endl;
  Csv csv_slowa = licznik_slowa.export_to_csv();

  csv_slowa.export_csv("csv_slowa");
  //csv_znaki.export_csv("csv_litery");

  BarChart chart_slowa(csv_slowa);
  //BarChart chart_znaki(csv_znaki);

  chart_slowa.export_to_ppm(csv_slowa.number_of_rows(), 720, "chart_slowa");
  std::cout << "slowa ready";
  //chart_znaki.export_to_ppm(1024, 720, "chart_znaki");

  return 0;
}
