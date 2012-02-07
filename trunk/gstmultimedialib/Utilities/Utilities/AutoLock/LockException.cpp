#include <Utilities/AutoLock/LockException.h>

using namespace std;

namespace utils {

LockException::LockException(const string &message) :
		AException(message) {
}

LockException::~LockException(void) throw () {
}

}
