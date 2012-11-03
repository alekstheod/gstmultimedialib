/* 
 * File:   Mutex.h
 * Author: m1cRo
 *
 * Created on September 3, 2010, 8:20 PM
 */

#ifndef _MUTEX_H
#define	_MUTEX_H

#include <Utilities/AutoLock/OS_Specific/WinMutex.h>
#include <Utilities/AutoLock/OS_Specific/LMutex.h>

namespace utils {

#ifdef WIN32
typedef LMutex Mutex;
#elif linux
typedef LMutex Mutex;
#endif

}
#endif	/* _LOCKOBJECT_H */

