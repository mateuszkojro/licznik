#ifndef FREQ_COUNTER_H
#define FREQ_COUNTER_H
#include "Csv.h"
#include "debug.h"
#include "pixelRGB.h"
#include "ppm.h"
#include <fstream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

template <class Type> class Base_FreqCounter {
public:
  void add_data(Type);
  std::unordered_map<Type, unsigned> get_count() { return data_; }
  Csv export_to_csv();
  Csv export_to_csv(std::wstring (*transformer)(Type));

protected:
  std::unordered_map<Type, unsigned> data_;
};

template <class Type> class FreqCounter : public Base_FreqCounter<Type> {
public:
  void create(const std::string &path);
};

template <class Type> void Base_FreqCounter<Type>::add_data(Type new_data) {
  // powinienem sprawdzic czy pusty -> 0 jezeli nie ++ ale domyslnie
  // przy tworzeniu jest 0
  ++data_[new_data];
}

template <class Type> Csv Base_FreqCounter<Type>::export_to_csv() {
  Config config;
  config.number_of_columns = 2;
  config.has_quotes = true;

  std::vector<std::wstring> converted;

  for (auto &field : data_) {
    converted.push_back(field.first);
    converted.push_back(std::to_wstring(field.second));
  }
  return Csv(converted, config);
}

template <class Type>
Csv Base_FreqCounter<Type>::export_to_csv(std::wstring (*transformer)(Type)) {
  Config config;
  config.number_of_columns = 2;

  std::vector<std::wstring> converted;

  for (auto &field : data_) {
    converted.push_back(transformer(field.first));
    converted.push_back(std::to_wstring(field.second));
  }

  return Csv(converted, config);
}

//@FIXME what_should_create_do?
template <class Type> void FreqCounter<Type>::create(const std::string &path) {
  std::wfstream file;
  file.open(path, std::ios::in);

  while (file.good()) {
    Type temp;
    file >> temp;
    this->add_data(temp);
  }
}

template <> class FreqCounter<pixelRGB> : public Base_FreqCounter<pixelRGB> {
public:
  FreqCounter<pixelRGB>() : Base_FreqCounter<pixelRGB>() {}
  void create(const std::string &path) {
    ppm obraz(path);
    for (auto pixel : obraz.get_pixels()) {
      this->add_data(pixel);
    }
  }
};

#endif
