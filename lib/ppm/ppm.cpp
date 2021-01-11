#include "ppm.h"
#include "obraz.h"
#include "pixelRGB.h"
#include "ppm_parser.h"
#include <fstream>
#include <string>

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

ppm::ppm(unsigned size_x, unsigned size_y, pixelRGB background_color)
    : obraz() {
  size_x_ = size_x;
  size_y_ = size_y;
  color_depth_ = 255;
  mode_ = file_type::ascii;
  // wypelniamy obrazek o podanych wymiarach kolorem tla
  for (unsigned i = 0; i < size_x_ * size_y; i++) {
    pixels_.push_back(background_color);
  }
}

void ppm::save_to_file(const std::string &path) {
  std::fstream file;
  file.open(path, std::ios::out);

  file << "P3" << '\n';
  file << size_x_ << '\t' << size_y_ << '\n';
  file << color_depth_ << '\n';

  for (auto &pixel : pixels_) {
    file << std::to_string(pixel.R()) << '\t';
    file << std::to_string(pixel.G()) << '\t';
    file << std::to_string(pixel.B()) << '\t';
  }
}

unsigned long ppm::count_colors() {
  // uzywamy unordered_map zeby stwworzyc hash table - umozliwia szybkie i
  // proste liczenie roznych kolorow
  std::unordered_map<unsigned, bool> n_colors;
  for (unsigned i = 0; i < pixels_.size(); i++) {
    n_colors[pixels_[i].hash()] = true;
  }
  // zeby dowiedziec siue iel unikatowyc wystarczy poznac rozmiar naszej hash
  // mapy
  return n_colors.size();
}

// kontrola czy na pewno rozmiar sie zgadza
unsigned long ppm::count_pixels() { return pixels_.size(); }

pixelRGB &ppm::operator()(unsigned x, unsigned y) {
  return pixels_.at(x + y * size_x_);
}
