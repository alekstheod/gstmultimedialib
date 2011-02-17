#ifndef UTILS_WINLOCKOBJECT_H
#define UTILS_WINLOCKOBJECT_H

#ifdef _WIN32
#include <windows.h>
#include "Utilities/AutoLock/LockException.h"


namespace utils {

    /// <summary>
    /// Lock object provide methods for thread synchronizing.
    /// Contain an MUTEX handle that can be used to lock and unlock the section of code with sharing the current object by different threads.
    /// </summary>

    class WinLockObject {
    private:
        /// <summary>
        /// Lockable mutex.
        /// </summary>
        HANDLE _mutex;

    public:
        /// <summary>
        /// Default constructor.
        /// </summary>
        WinLockObject(void);
        bool Lock(unsigned int waitTime = INFINITY)const;
        bool Unlock(void)const;
        virtual ~WinLockObject(void)throw ();
    };

}
#endif

#endif
