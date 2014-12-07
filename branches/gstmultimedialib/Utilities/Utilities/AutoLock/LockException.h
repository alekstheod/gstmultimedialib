#ifndef UTILS_LOCKEXCEPTION_H
#define UTILS_LOCKEXCEPTION_H

#include <Utilities/AException.h>

namespace utils {

class LockException: public AException {
public:
	LockException(const std::string &message);
	virtual ~LockException(void) throw ();
};

}

#endif
