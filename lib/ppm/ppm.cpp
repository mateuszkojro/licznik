#include "ppm.h"
#include "pixelRGB.h"
#include "ppm_parser.h"

ppm::ppm(std::string path) : obraz() {
  mode_ = file_type(none);

  std::fstream file;
  std::string all;
  all.reserve(512 * 512);
  file.open(path, std::ios::in);

  std::string input;
  // TODO make it allocate less
  while (std::getline(file, input)) {
    input += "\n";
    all += input;
  }
  ppm_parser p(all);
  *this = p.get();
}


unsigned long ppm::count_colors() {
  // uzywamy unordered_map zeby stwworzyc hash table - umozliwia szybkie i
  // proste liczenie roznych kolorow
  std::unordered_map<unsigned, bool> n_colors;
  for (unsigned i = 0; i < pixels_.size(); i++) {
    n_colors[pixels_[i].hash()] = true;
  }
  // zeby dowiedziec siue iel unikatowyc wystarczy poznac rozmiar naszej hash mapy
  return n_colors.size();
}

// kontrola czy na pewno rozmiar sie zgadza
unsigned long ppm::count_pixels() { return pixels_.size(); }

pixelRGB& ppm::operator()(unsigned x, unsigned y){
  return pixels_.at(x + y * size_y_);
}
