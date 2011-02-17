#include <Utilities/Xml/XmlException.h>

namespace utils {

    XmlException::XmlException(const std::string& message) : AException(message) {
    }

    XmlException::~XmlException(void)throw () {
    }

}
