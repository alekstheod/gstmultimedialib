#include <Utilities/AutoLock/OS_Specific/WinMutex.h>
#ifdef _WIN32
namespace utils {

	const unsigned int WinMutex::CONST_DEFAULT_LOCK_TIMEOUT = INFINITY;

	WinMutex::WinMutex(void) {
		_mutex = CreateMutex(NULL, FALSE, NULL);
		if (_mutex != NULL) {
			ReleaseMutex(_mutex);
		}
	}

	WinMutex::~WinMutex(void)throw () {
		if (_mutex != NULL) {
			ReleaseMutex(_mutex);
			CloseHandle(_mutex);
		}
	}

	bool WinMutex::unlock(void)const {
		if (_mutex != NULL) {
			ReleaseMutex(_mutex);
		} else {
			return false;
		}

		return true;
	}

	bool WinMutex::lock(unsigned int waitTime)const {
		if(mutex==NULL) {
			return false;
		}

		if (WaitForSingleObject(_mutex, waitTime) != WAIT_OBJECT_0) {
			return false;
		}

		return true;
	}
}
#endif
