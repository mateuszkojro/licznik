#ifndef FREQ_COUNTER_H
#define FREQ_COUNTER_H
#include <unordered_map>

template <class Type> class FreqCounter {

public:
  void add_data(Type);
  void create();
  unsigned get_count();
  std::unordered_map<Type, unsigned> get_data();

private:
  std::unordered_map<Type, unsigned> data_;
};

template<class Type>
void FreqCounter<Type>::add_data(Type new_data){
  data_.get(new_data);
  // powinienem sprawdzic czy pusty -> 0 jezeli nie ++ ale domyslnie 
  // przy tworzeniu jest 0 
  ++data_[new_data];
}

#endif
