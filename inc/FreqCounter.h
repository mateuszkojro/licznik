#ifndef FREQ_COUNTER_H
#define FREQ_COUNTER_H
#include <map>

template <class Type> class FreqCounter {

public:
  void add_data(Type);
  void create();
  unsigned get_count();
  std::map<Type, int> get_data();

private:
  std::map<Type, int> data;
};

#endif
