#pragma once
#include "serializable.h"

namespace utils {

class sprimitive: public serializable {
public:
	sprimitive(void);
	virtual std::wstring GetValue(void) const = 0;
	virtual bool SetValue(const std::wstring&) = 0;
	virtual ~sprimitive(void) throw ();
};

}

