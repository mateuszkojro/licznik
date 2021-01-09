#include "Csv.h"
#include <cstddef>
#include <fstream>
#include <string>
#include <vector>

void Csv::export_csv(const std::string &path) {

  std::fstream file;
  file.open(path, std::ios::in);

  // pozwala nam uniknac wielokrotnego sprawdzania w petli ustawien
  std::string maybe_quote = (config_.has_quotes) ? "\"" : "";

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

  std::fstream file;
  file.open(path, std::ios::out);

  std::string value;
  while (!file.eof()) {
    // getline przyjmuje ',' jako separator kolejnych pol
    getline(file, value, config_.separator);
    data_.push_back(value);
  }
}

std::string &Csv::operator()(unsigned row, unsigned column) {
  return data_.at(column + row * config_.number_of_columns);
}
