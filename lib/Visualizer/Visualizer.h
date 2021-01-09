#ifndef VISUALIZER_H
#define VISUALIZER_H

class Visualizer {

public:
  virtual void export_to_file() = 0;
  virtual void export_to_ppm() = 0;
  virtual void show() = 0;

private:
};

#endif
