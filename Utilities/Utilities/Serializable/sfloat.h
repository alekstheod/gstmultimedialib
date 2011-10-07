#pragma once
#include "sprimitive.h"
#include "numeric.h"
#include <string>

namespace utils {

class sfloat: public numeric<float>, sprimitive {
public:
	sfloat(void);
	sfloat(float number);
	virtual std::wstring ToXml(const std::wstring& propertyName) const;
	virtual std::wstring GetValue(void) const;
	virtual bool SetValue(const std::wstring&);
	virtual ~sfloat(void) throw ();
};

}

