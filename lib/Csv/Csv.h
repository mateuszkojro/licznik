#ifndef CSV_H
#define CSV_H
#include <deque>
#include <map>
#include <string>
#include <vector>

// Number of columns
// has_titles
// has_quotes

struct Config {
  char separator = ',';
  bool has_headers = false;
  bool has_quotes = false;
  unsigned number_of_columns = 0;
};

// Implementacja zgodna z https://tools.ietf.org/html/rfc4180
class Csv {

public:
  Csv() = delete;
  //@TODO konstruktor from file? Csv()
  Csv(std::vector<std::string>);

  //@TODO moze byc ciezko z wzgledu na rozny zapis roznych obiektow ale
  // moglibymsy brac func interpretujaca string do danego obiektu that would be
  // kinda cool labo wgl bez tego i nie towrzymy nigdy csv z pliku albo zwracamy
  // pary string - izi i ma sens
  void read_csv(const std::string &);
  void export_csv(const std::string &);

  std::vector<std::string> get_data();

  std::string &operator()(unsigned, unsigned);

private:
  Config config_;
  std::vector<std::string> data_;
};

#endif
