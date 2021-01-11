#ifndef BAR_CHART_H
#define BAR_CHART_H

#include "Csv.h"
#include "Visualizer.h"
#include "debug.h"
#include <numeric>
#include <string>

class BarChart : public Visualizer {
public:
  BarChart() = delete;
  BarChart(Csv csv) : Visualizer(csv) {}
  virtual void export_to_ppm(unsigned size_x, unsigned size_y,
                             const std::string &) override;
  virtual void show() override { throw new not_implemented_exception; }
};

#endif
