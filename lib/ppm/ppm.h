#ifndef PPM_H
#define PPM_H

#include "obraz.h"
#include <fstream>
#include <iostream>
#include <string>
#include "debug.h"
#include "pgm_parser.h"
#include "pixelRGB.h"

int liczkolory(obraz);

class ppm : public obraz {
public:
  ppm():obraz(){} 
  // TODO initialize vars
  ppm(std::string file);
  ppm(unsigned,unsigned, pixelRGB);

// private:
  //TODO fix this name 
  // file_type mode_;
  std::vector<pixelRGB> pixels_;
  unsigned long count_colors();
  unsigned long count_pixels();
  pixelRGB& operator()(unsigned,unsigned);
  ~ppm(){}
};

#endif // PPM_H
