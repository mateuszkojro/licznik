#ifndef DEBUG_TOOLS_H
#define DEBUG_TOOLS_H

#include <chrono>
#include <iostream>
#include <exception>

class not_implemented_exception : std::exception {
  public:
    virtual const char * what() const throw() override {
      return "Function is not yet implemented";
    }
};
#ifdef DEBUG
#define ERR(message)                                                           \
  std::cerr << "!!!!!!!!!!!!!!!!!!" << message << "!!!!!!!!!!!!!!!!!!!"        \
            << std::endl;                                                      \
  exit(69)
#define DEBC(value, message)                                                   \
  (std::clog << value << " (int)" << (int)value << ": " << message << std::endl)
#define DEB(message) (std::clog << "___" << message << "___" << std::endl)


#else
#define TIME_START(name) auto name = std::chrono::high_resolution_clock::now()
#define TIME_STOP(name, desc)                                                  \
  auto stop = std::chrono::high_resolution_clock::now();                       \
  std::clog << desc << " took: "                                               \
            << std::chrono::duration_cast<std::chrono::microseconds>(stop -    \
                                                                     name)     \
                   .count()                                                    \
            << std::endl

#define DEBC(value, message) ""
#define DEB(message) ""
#define ERR(message) ""
#endif
#endif
