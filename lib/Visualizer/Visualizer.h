#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "Csv.h"
#include <string>

//@TODO bar_graph
//@TODO line graph

class Visualizer {

public:
  Visualizer() = delete;
  Visualizer(Csv);
  // virtual void export_to_file() = 0;
  virtual void export_to_ppm(const std::string &) = 0;
  virtual void show() = 0;

private:
  Csv data_;
};

#endif
