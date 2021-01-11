#include "Csv.h"
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Csv::Csv(std::vector<std::wstring> data, Config config) {
  config_ = config;
  data_ = data;
  config_ = config;
}

void Csv::export_csv(const std::string &path) {

  std::wfstream file;
  file.open(path, std::ios::out);

  // pozwala nam uniknac wielokrotnego sprawdzania w petli ustawien
  std::wstring maybe_quote = (config_.has_quotes) ? (const wchar_t*)"\"" : (const wchar_t*)"";

  for (unsigned i = 0; i < data_.size(); i++) {

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

  std::wfstream file;
  file.open(path, std::ios::in);

  std::wstring value;
  int i = 0;
  while (file.good()) {
    // getline przyjmuje ',' jako separator kolejnych pol
    std::getline(file, value, config_.separator);
    data_.push_back(value);
    bool is_last_element_on_line = i % config_.number_of_columns;
    if (is_last_element_on_line) {
      wchar_t trash;
      file >> trash;
      i = 0;
    }
    i++;
  }
}

std::wstring &Csv::operator()(unsigned column, unsigned row) {
  // @vstd::vector.at() sprawdza za nas czy adres jest w zakresie jezeli
  // nie wyrzuca std::out_of_range rownanie dostepu pozwala nam symulowac
  // istnienie tablicy 2 wymiarowej
  return data_.at(column + row * config_.number_of_columns);

}

std::vector<std::wstring> Csv::get_data() { return data_; }

unsigned Csv::number_of_columns() { return config_.number_of_columns; }

unsigned Csv::number_of_rows() {
  return (unsigned)data_.size() / (unsigned)config_.number_of_columns;
}
