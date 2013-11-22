#include <Utilities/AException.h>

namespace utils {

using namespace std;

AException::AException(const string &message, bool sysMessage) {
	m_message = message;
	if (sysMessage) {
		m_message.append(" : ");
		m_message.append("System error");
	}
}

AException::~AException(void) {
}

const char* AException::what(void) const throw () {
	return m_message.c_str();
}

}
