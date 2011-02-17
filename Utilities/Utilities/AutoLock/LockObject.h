/* 
 * File:   LockObject.h
 * Author: m1cRo
 *
 * Created on September 3, 2010, 8:20 PM
 */

#ifndef _LOCKOBJECT_H
#define	_LOCKOBJECT_H

#include <Utilities/AutoLock/WinLockObject.h>
#include <Utilities/AutoLock/LLockObject.h>

namespace utils {

#ifdef WIN32
    typedef WinLockObject LockObject;
#elif linux
    typedef LLockObject LockObject;
#endif

}
#endif	/* _LOCKOBJECT_H */

