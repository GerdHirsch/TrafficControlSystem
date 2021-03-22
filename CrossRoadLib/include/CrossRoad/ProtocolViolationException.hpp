#ifndef PROTOCOLVIOLATIONEXCEPTION_H
#define PROTOCOLVIOLATIONEXCEPTION_H

#include <string>
#include<stdexcept>

class ProtocolViolationException : public std::logic_error {
public:

	explicit ProtocolViolationException(std::string const& message);
	ProtocolViolationException(const ProtocolViolationException& e);

};
inline
ProtocolViolationException::ProtocolViolationException(std::string const& message)
:std::logic_error(message)
{}
inline
ProtocolViolationException::ProtocolViolationException(ProtocolViolationException const& e)
:std::logic_error(e)
{}


#endif //PROTOCOLVIOLATIONEXCEPTION_H
