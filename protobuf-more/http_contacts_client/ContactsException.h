#include <string>
class ContactsException
{
private:
  std::string message;
public:
  ContactsException(std::string str = "A problem") : message(str) {}
  std::string what() const {
      return message;
  }
};
