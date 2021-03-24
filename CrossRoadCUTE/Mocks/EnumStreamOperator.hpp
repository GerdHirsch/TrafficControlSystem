/*
 * EnumStreamOperator.hpp
 *
 *  Created on: 24.03.2021
 *      Author: Gerd
 */

#ifndef MOCKS_ENUMSTREAMOPERATOR_HPP_
#define MOCKS_ENUMSTREAMOPERATOR_HPP_
namespace std{

template
<
	class Enum,
	class = typename std::enable_if< std::is_enum<Enum>::value >::type
>
std::ostream& operator<<(std::ostream& out, Enum value){
	using EnumType = typename std::underlying_type<Enum>::type;
	out << static_cast<EnumType>(value);
	return out;
}

} // end namespace
#endif /* MOCKS_ENUMSTREAMOPERATOR_HPP_ */
