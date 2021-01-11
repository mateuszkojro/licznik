#ifndef CSV_H
#define CSV_H
#include <deque>
#include <map>
#include <string>
#include <vector>

// Number of columns
// has_titles
// has_quotes

//@TODO zajac sie headerami 
struct Config {
  wchar_t separator = (wchar_t)',';
  bool has_headers = false;
  bool has_quotes = false;
  unsigned number_of_columns = 0;
};

// Implementacja zgodna z https://tools.ietf.org/html/rfc4180
class Csv {

public:
  Csv() {} ;
  //@TODO konstruktor from file? Csv()
  Csv(std::vector<std::wstring>, Config);

  //@TODO moze byc ciezko z wzgledu na rozny zapis roznych obiektow ale
  // moglibymsy brac func interpretujaca string do danego obiektu that would be
  // kinda cool labo wgl bez tego i nie towrzymy nigdy csv z pliku albo zwracamy
  // pary string - izi i ma sens
  //@FIXME co_jezeli_nie_ma_pliku
  void read_csv(const std::string &);
  void export_csv(const std::string &);

  unsigned number_of_columns();
  unsigned number_of_rows();

  std::vector<std::wstring> get_data();

  std::wstring &operator()(unsigned, unsigned);

private:
  Config config_;
  std::vector<std::wstring> data_;
};

#endif
