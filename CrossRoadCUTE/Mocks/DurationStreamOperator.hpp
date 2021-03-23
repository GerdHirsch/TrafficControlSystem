#ifndef DURATIONSTREAMOPERATOR_HPP_
#define DURATIONSTREAMOPERATOR_HPP_

#include <chrono>
#include <iostream>

namespace std{

template<class Rep, class Period>
std::ostream& operator<<(std::ostream& out, std::chrono::duration<Rep, Period> duration){
	out << duration.count();
	return out;
}

} // namespace std



#endif /* DURATIONSTREAMOPERATOR_HPP_ */
