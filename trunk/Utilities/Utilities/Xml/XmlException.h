#pragma once
#include <Utilities/AException.h>

namespace utils {

    class XmlException : public AException {
    public:
        XmlException(const std::string& message);
        virtual ~XmlException(void)throw ();
    };

}

