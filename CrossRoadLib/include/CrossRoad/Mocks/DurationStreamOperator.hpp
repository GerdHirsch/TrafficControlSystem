#ifndef DURATIONSTREAMOPERATOR_HPP_
#define DURATIONSTREAMOPERATOR_HPP_

#include <chrono>
#include <iostream>

template <class Rep, class Period>
std::ostream &operator<<(std::ostream &out,
                         std::chrono::duration<Rep, Period> duration) {
  out << duration.count();
  return out;
}

#endif // DURATIONSTREAMOPERATOR_HPP_
