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

    LLockObject::LLockObject() {
        _errorCode = pthread_mutex_init(&_mutex, NULL);
    }

    bool LLockObject::Lock(unsigned int waitTime)const {
        if (_errorCode != 0) {
            return false;
        }

        pthread_mutex_t mutex = _mutex;
        if (pthread_mutex_lock(&mutex) != 0) {
            return false;
        }

        return true;
    }

    bool LLockObject::Unlock(void)const {
        pthread_mutex_t mutex = _mutex;
        if (_errorCode != 0) {
            return false;
        }

        int result = pthread_mutex_unlock(&mutex);
        if (result == EINVAL || result == EFAULT || result == EPERM) {
            return false;
        }

        return true;
    }

    LLockObject::~LLockObject()throw () {
        if (_errorCode != 0) {
            pthread_mutex_destroy(&_mutex);
        }
    }

}
#endif
