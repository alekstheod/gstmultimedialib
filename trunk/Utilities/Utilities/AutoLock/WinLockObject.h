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
    public:
        static const unsigned int CONST_DEFAULT_LOCK_TIMEOUT;

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
        bool lock(unsigned int waitTime = CONST_DEFAULT_LOCK_TIMEOUT)const;
        bool unlock(void)const;
        virtual ~WinLockObject(void)throw ();
    };

}
#endif

#endif
