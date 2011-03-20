#include <Utilities/AutoLock/AutoLock.h>

namespace utils {

    const unsigned int AutoLock::CONST_DEFAULT_LOCK_TIMEOUT = 0xFFFFFFFF;

    AutoLock::AutoLock(const LockObject& lockObject, unsigned int waitTime) : _lockObject(lockObject) {
        if(!_lockObject.lock(waitTime)){
            throw LockException("AutoLock::AutoLock - LockObject::Lock failed");
        }
    }

    AutoLock::~AutoLock(void)throw () {
        _lockObject.unlock();
    }

}
