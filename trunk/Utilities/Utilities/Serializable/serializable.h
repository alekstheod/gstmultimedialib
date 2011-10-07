#pragma once
#include <string>

namespace utils {

class serializable {
protected:
	std::wstring ToXmlString(const std::wstring& propertyName,
			const std::wstring& objectValue) const;

public:
	serializable(void);
	virtual std::wstring ToXml(const std::wstring& propertyName) const = 0;
	virtual ~serializable(void) throw ();
};

}

