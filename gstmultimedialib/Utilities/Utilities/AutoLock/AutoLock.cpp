#include <Utilities/AutoLock/AutoLock.h>

namespace utils {

AutoLock::AutoLock(const LockObject& lockObject, unsigned int waitTime) :
		_lockObject(lockObject) {
	if (!_lockObject.lock(waitTime)) {
		throw LockException("AutoLock::AutoLock - LockObject::Lock failed");
	}
}

AutoLock::~AutoLock(void) throw () {
	_lockObject.unlock();
}

}
