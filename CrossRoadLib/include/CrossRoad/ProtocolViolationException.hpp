#ifndef PROTOCOLVIOLATIONEXCEPTION_H
#define PROTOCOLVIOLATIONEXCEPTION_H

#include <stdexcept>
#include <string>

class ProtocolViolationException : public std::logic_error {
public:
  explicit ProtocolViolationException(std::string const &message)
      : std::logic_error(message){};
  ProtocolViolationException(const ProtocolViolationException &e)
      : std::logic_error(e){};
};

#endif // PROTOCOLVIOLATIONEXCEPTION_H
