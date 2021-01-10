#include "Csv.h"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Csv::Csv(std::vector<std::string> data, Config config) {
  config_ = config;
  data_ = data;
  config_ = config;
}

void Csv::export_csv(const std::string &path) {

  std::fstream file;
  file.open(path, std::ios::out);

  // pozwala nam uniknac wielokrotnego sprawdzania w petli ustawien
  std::string maybe_quote = (config_.has_quotes) ? "\"" : "";

  for (unsigned i = 0; i < data_.size(); i++) {

    std::clog << data_[i] << "\n";
    // zapisujemy pole do pliku
    file << maybe_quote << data_[i] << maybe_quote;

    // w standardowym pliku CSV nie powinno byc przecinka po ostatnim elemencie
    bool is_last_element = i == data_.size() - 1;
    if (!is_last_element) {
      file << ',';
    }

    // standard pliow CSV wymaga braku znaku konca lini po ostatnim rzedzie
    bool is_end_of_row =
        i % config_.number_of_columns == config_.number_of_columns - 1;
    if (!is_last_element && is_end_of_row) {
      file << '\n';
    }
  }
}

void Csv::read_csv(const std::string &path) {

  std::fstream file;
  file.open(path, std::ios::in);

  std::string value;
  while (file.good()) {
    // getline przyjmuje ',' jako separator kolejnych pol
    getline(file, value, config_.separator);
    std::clog <<"reading: " <<  value << "\n";
    data_.push_back(value);
  }
}

std::string &Csv::operator()(unsigned row, unsigned column) {
  // @vstd::vector.at() sprawdza za nas czy adres jest w zakresie jezeli
  // nie wyrzuca std::out_of_range rownanie dostepu pozwala nam symulowac
  // istnienie tablicy 2 wymiarowej
  return data_.at(column + row * config_.number_of_columns);
}

std::vector<std::string> Csv::get_data() { return data_; }
