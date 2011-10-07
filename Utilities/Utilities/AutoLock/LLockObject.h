/*
 * LinLockObject.h
 *
 *  Created on: May 2, 2010
 *      Author: m1cro
 */

#ifndef UTILS_LLOCKOBJECT_H
#define UTILS_LLOCKOBJECT_H

#ifdef linux
#include <Utilities/AutoLock/LockException.h>
#include <pthread.h>

namespace utils {

class LLockObject {
public:
	static const unsigned int CONST_DEFAULT_LOCK_TIMEOUT;

private:
	mutable pthread_mutex_t _mutex;
	int _errorCode;

public:
	LLockObject();
	bool lock(unsigned int waitTime = CONST_DEFAULT_LOCK_TIMEOUT) const;
	bool unlock(void) const;
	virtual ~LLockObject() throw ();
};

}
#endif

#endif
