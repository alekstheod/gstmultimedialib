#pragma once
#include "sprimitive.h"

namespace utils {

class sbool: public sprimitive {
private:
	bool _value;

public:
	static const std::wstring CONST_BOOL_TRUE_DESCRIPTION;
	static const std::wstring CONST_BOOL_FALSE_DESCRIPTION;

public:
	sbool(void);
	sbool(bool);
	sbool(const sbool&);
	virtual const sbool & operator =(const sbool& arg);
	virtual bool operator ==(const sbool& arg) const;
	virtual std::wstring GetValue(void) const;
	virtual bool SetValue(const std::wstring&);
	virtual std::wstring ToXml(const std::wstring& propertyName) const;
	virtual ~sbool(void) throw ();
};

}

