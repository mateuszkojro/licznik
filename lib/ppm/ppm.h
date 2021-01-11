#ifndef PPM_H
#define PPM_H

#include "debug.h"
#include "obraz.h"
#include "pgm_parser.h"
#include "pixelRGB.h"
#include "state_machine.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int liczkolory(obraz);

class ppm : public obraz {
public:
  ppm() : obraz(){};
  // TODO initialize vars
  ppm(std::string file);
  ppm(unsigned, unsigned, pixelRGB);

  // private:
  // TODO fix this name
  // file_type mode_;
  unsigned long count_colors();
  unsigned long count_pixels();
  void save_to_file(const std::string &);
  pixelRGB &operator()(unsigned, unsigned);
  std::vector<pixelRGB> get_pixels() { return pixels_; }
  ~ppm() {}
  friend class state_machine<ppm>;

protected:
  std::vector<pixelRGB> pixels_;
};

#endif // PPM_H
