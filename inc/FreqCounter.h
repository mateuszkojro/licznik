#ifndef FREQ_COUNTER_H
#define FREQ_COUNTER_H
#include "Csv.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

template <class Type> class FreqCounter {

public:
  void add_data(Type);
  void create(const std::string &);
  std::unordered_map<Type, unsigned> get_count();
  Csv export_to_csv();
  Csv export_to_csv(std::string (*transformer)(Type));

private:
  std::unordered_map<Type, unsigned> data_;
};

//@FIXME what_should_create_do?
template <class Type> void FreqCounter<Type>::create(const std::string &path) {
  std::fstream file;
  file.open(path, std::ios::in);

  while (file.good()) {
    Type temp;
    this->add_data(temp);
  }
}

template <class Type> void FreqCounter<Type>::add_data(Type new_data) {
  data_.get(new_data);
  // powinienem sprawdzic czy pusty -> 0 jezeli nie ++ ale domyslnie
  // przy tworzeniu jest 0
  ++data_[new_data];
}

template <class Type> Csv FreqCounter<Type>::export_to_csv() {
  Config config;
  config.number_of_columns = 2;

  std::vector<std::string> converted;

  for (auto &field : data_) {
    converted.push_back(std::to_string(field.first));
    converted.push_back(field.second);
  }
}

template <class Type>
Csv FreqCounter<Type>::export_to_csv(std::string (*transformer)(Type)) {
  Config config;
  config.number_of_columns = 2;

  std::vector<std::string> converted;

  for (auto &field : data_) {
    converted.push_back(transformer(field.first));
    converted.push_back(field.second);
  }
}

#endif
