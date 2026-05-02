#pragma once

#include <iostream>

#define ASSERT_IN(container, element, message)                                 \
  do {                                                                         \
    if (container.find(element) == container.end()) {                          \
      std::cerr << "[ASSERTION FAILED]\n"                                      \
                << message << "\nElemnt: " << (element)                        \
                << "\nFile: " << __FILE__ << "\nLine: " << __LINE__            \
                << std::endl;                                                  \
      std::exit(EXIT_FAILURE);                                                 \
    }                                                                          \
  } while (false);
