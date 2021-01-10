#include "BarChart.h"
#include "obraz.h"
#include "pixelRGB.h"
#include "ppm.h"
#include <string>

//@FIXME gdzie w sumie wsadzic ta fuinc
void draw_rect(ppm obraz, unsigned start_x, unsigned start_y, unsigned size_x,
               unsigned size_y, pixelRGB color) {

  for (unsigned x = start_x; x < start_x + size_x; x++) {
    for (unsigned y = start_y; y < start_y + size_y; y++) {
      obraz(x, y) = color;
    }
  }
}

void BarChart::export_to_ppm(const std::string &path) {
  ppm obraz(1024, 720, pixelRGB(255, 255, 255));

  unsigned skala_x = (unsigned)1024 / (unsigned)data_.number_of_columns(); 
  unsigned skala_y = (unsigned)1024 / (unsigned)data_.number_of_rows(); 

  for (unsigned col = 0; col < data_.number_of_columns(); col++) {
    for (unsigned row = 0; row < data_.number_of_rows(); row++) {
      draw_rect(obraz, col * skala_x, row * skala_y , skala_x , skala_y , pixelRGB(255,0,0));
    }
  }

  obraz.save_to_file(path);
}
