#include <Utilities/AutoLock/WinLockObject.h>
#ifdef _WIN32
namespace utils {

    WinLockObject::WinLockObject(void) {
        _mutex = CreateMutex(NULL, FALSE, NULL);
        if (_mutex != NULL) {
            ReleaseMutex(_mutex);
        }
    }

    WinLockObject::~WinLockObject(void)throw () {
        if (_mutex != NULL) {
            ReleaseMutex(_mutex);
            CloseHandle(_mutex);
        }
    }

    bool WinLockObject::unlock(void)const {
        if (_mutex != NULL) {
            ReleaseMutex(_mutex);
        }else{
            return false;
        }

        return true;
    }

    bool WinLockObject::lock(unsigned int waitTime)const {
        if(mutex==NULL){
            return false;
        }

        if (WaitForSingleObject(_mutex, waitTime) != WAIT_OBJECT_0) {
            return false;
        }

        return true;
    }
}
#endif
