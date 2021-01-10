#ifndef PPM_H
#define PPM_H

#include "debug.h"
#include "obraz.h"
#include "pgm_parser.h"
#include "pixelRGB.h"
#include <fstream>
#include <iostream>
#include <string>

int liczkolory(obraz);

class ppm : public obraz {
public:
  ppm() : obraz() {};
  // TODO initialize vars
  ppm(std::string file);
  ppm(unsigned, unsigned, pixelRGB);

  // private:
  // TODO fix this name
  // file_type mode_;
  std::vector<pixelRGB> pixels_;
  unsigned long count_colors();
  unsigned long count_pixels();
  void save_to_file(const std::string&);
  pixelRGB &operator()(unsigned, unsigned);
  ~ppm() {}

};

#endif // PPM_H
