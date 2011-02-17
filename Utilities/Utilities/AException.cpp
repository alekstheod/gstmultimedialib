#include <Utilities/AException.h>


namespace utils {

    using namespace std;

    AException::AException(const string &message, bool sysMessage) {
        _message = message;
        if (sysMessage) {
            _message.append(" : ");
            _message.append("System error");
        }
    }

    AException::~AException(void)throw () {
    }

    const char* AException::what(void) const throw () {
        return _message.c_str();
    }

}
