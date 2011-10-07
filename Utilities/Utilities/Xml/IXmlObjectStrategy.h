#pragma once
#include <string>
#include <map>

namespace utils {
/// <summary>
///
/// </summary>

class IXmlObjectStrategy {
public:
	IXmlObjectStrategy(void);
	virtual void runXmlObject(const std::wstring& objectLabel,
			const std::map<std::wstring, std::wstring>& arguments
			, const std::wstring& xmlValue) = 0;
	virtual ~IXmlObjectStrategy(void);
};
}
