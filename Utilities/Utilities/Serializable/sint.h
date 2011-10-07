#pragma once
#include "serializable.h"
#include "numeric.h"
#include <string>

namespace utils {

class sint: public numeric<int>, public serializable {
public:
	sint(void);
	sint(int value);
	sint(const sint& value);
	virtual std::wstring ToXml(const std::wstring& propertyName) const;
	virtual std::wstring GetValue(void) const;
	virtual bool SetValue(const std::wstring&);
	virtual ~sint(void) throw ();
};

}