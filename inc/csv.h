#ifndef CSV_H
#define CSV_H
#include <deque>
#include <map>
#include <string>
#include <vector>


class Csv {

public:
  Csv() = delete;
  //TODO konstruktor from file? Csv()
  Csv(std::vector<std::string>);

  // TODO moze byc ciezko z wzgledu na rozny zapis roznych obiektow ale
  // moglibymsy brac func interpretujaca string do danego obiektu that would be
  // kinda cool labo wgl bez tego i nie towrzymy nigdy csv z pliku albo zwracamy
  // pary string - izi i ma sens
  void read_csv();
  void export_csv();

  std::vector<std::string> get_data();

private:
  std::vector<std::string> data;
};

#endif
