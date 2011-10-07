#include "serializable.h"
#include <typeinfo>

using namespace std;
using namespace utils;

serializable::serializable(void) {
}

serializable::~serializable(void) throw () {
}

std::wstring serializable::ToXmlString(const std::wstring& propertyName,
		const std::wstring& objectValue) const {
	string objectType = typeid (*this).name();
	wstring objValue;
	for (unsigned int i = 0; i < objectValue.length(); i++) {
		switch (objectValue[i]) {
		case '>':
			objValue += L"&gt";
			break;

		case '<':
			objValue += L"&lt";
			break;

		case '\'':
			objValue += L"&apos";
			break;

		case '"':
			objValue += L"&quot";
			break;

		case '&':
			objValue += L"&amp";
			break;

		default:
			objValue += objectValue[i];
			break;
		}
	}
	return L"<" + propertyName + L" type='"
			+ wstring(objectType.begin(), objectType.end()) + L"'>" + objValue
			+ L"</" + propertyName + L">";
}
