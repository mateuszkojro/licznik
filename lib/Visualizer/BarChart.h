#ifndef BAR_CHART_H
#define BAR_CHART_H

#include "Visualizer.h"
#include <string>

class BarChart : Visualizer {
public:
  virtual void export_to_ppm(const std::string&) override;
private:
};

#endif
