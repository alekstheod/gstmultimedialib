/*
    Copyright (c) 2012, Alex Theodoridis <email>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the <organization> nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY Alex Theodoridis <email> ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL Alex Theodoridis <email> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "LMutex.h"
#include <Utilities/AutoLock/OS_Specific/LMutex.h>
#include <errno.h>

namespace utils {

const unsigned int LMutex::CONST_DEFAULT_LOCK_TIMEOUT = 0xFFFFFFFF;

LMutex::LMutex() {
    _errorCode = pthread_mutex_init(&_mutex, NULL);
}

bool LMutex::lock(unsigned int waitTime) const {
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

bool LMutex::unlock(void) const {
    if (_errorCode != 0) {
        return false;
    }

    int result = pthread_mutex_unlock(&_mutex);
    if (result == EINVAL || result == EFAULT || result == EPERM) {
        return false;
    }

    return true;
}

LMutex::~LMutex() throw () {
    if (_errorCode != 0) {
        pthread_mutex_destroy(&_mutex);
    }
}

}
