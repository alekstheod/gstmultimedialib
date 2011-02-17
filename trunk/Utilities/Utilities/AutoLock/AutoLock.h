/*
 * AutoLock.h
 *
 *  Created on: May 2, 2010
 *      Author: m1cro
 */
#include "LockObject.h"

#ifndef UTILS_AUTOLOCK_H
#define UTILS_AUTOLOCK_H

namespace utils {

    class AutoLock {
    public:
        static const unsigned int CONST_DEFAULT_LOCK_TIMEOUT;

    private:
        const LockObject& _lockObject;

    public:
        AutoLock(const LockObject& lockObject, unsigned int waitTime = CONST_DEFAULT_LOCK_TIMEOUT);
        ~AutoLock(void)throw ();
    };

}

#endif
