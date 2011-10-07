/*
 * LinLockObject.cpp
 *
 *  Created on: May 2, 2010
 *      Author: m1cro
 */
#ifdef linux
#include <Utilities/AutoLock/LLockObject.h>
#include <errno.h>

namespace utils {

const unsigned int LLockObject::CONST_DEFAULT_LOCK_TIMEOUT = 0xFFFFFFFF;

LLockObject::LLockObject() {
	_errorCode = pthread_mutex_init(&_mutex, NULL);
}

bool LLockObject::lock(unsigned int waitTime) const {
	if (_errorCode != 0) {
		return false;
	}

	if (CONST_DEFAULT_LOCK_TIMEOUT == waitTime) {
		if (pthread_mutex_lock(&_mutex) != 0) {
			return false;
		}
	} else {
		timespec timeOut = { 0, waitTime };
		if (pthread_mutex_timedlock(&_mutex, &timeOut) != 0) {
			return false;
		}
	}

	return true;
}

bool LLockObject::unlock(void) const {
	if (_errorCode != 0) {
		return false;
	}

	int result = pthread_mutex_unlock(&_mutex);
	if (result == EINVAL || result == EFAULT || result == EPERM) {
		return false;
	}

	return true;
}

LLockObject::~LLockObject() throw () {
	if (_errorCode != 0) {
		pthread_mutex_destroy(&_mutex);
	}
}

}
#endif
