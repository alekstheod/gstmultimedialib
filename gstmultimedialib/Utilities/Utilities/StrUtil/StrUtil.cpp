#include "StrUtil.h"
#include <sstream>

namespace utils {

using namespace std;

StrUtil::StrUtil(void) {
}

StrUtil::~StrUtil(void) {
}

std::wstring StrUtil::trim(const std::wstring& str) {
	std::wstring result;
	unsigned int pos = str.find_first_not_of(L" \r\n\t");
	if (pos != str.npos) {
		result = str.substr(pos, str.npos);
	}
	pos = result.find_last_not_of(L" \r\n\t") + 1;
	if (pos != result.npos) {
		result = result.erase(pos);
	}
	return result;
}

std::vector<std::wstring> StrUtil::parse(const std::wstring& source,
		const std::wstring& delimiter) {
	std::vector<std::wstring> result;
	std::wstring temp = source;
	unsigned int pos = 0;
	do {
		pos = temp.find(delimiter);
		if (pos != temp.npos) {
			if (pos != 0) {
				result.push_back(temp.substr(0, pos));
			}

			if (pos + delimiter.length() <= temp.length()) {
				temp = temp.substr(pos + delimiter.length());
			} else {
				result.push_back(temp.substr(0, pos));
				break;
			}
		} else if (!temp.empty()) {
			result.push_back(temp);
		}
	} while (pos != temp.npos);

	return result;
}

std::vector<std::string> StrUtil::parse(const std::string& source,
		const std::string& delimiter) {
	std::vector<std::string> result;
	std::string temp = source;
	unsigned int pos = 0;
	do {
		pos = temp.find(delimiter);
		if (pos != temp.npos) {
			if (pos != 0) {
				result.push_back(temp.substr(0, pos));
			}

			if (pos + delimiter.length() <= temp.length()) {
				temp = temp.substr(pos + delimiter.length());
			} else {
				result.push_back(temp.substr(0, pos));
				break;
			}
		} else if (!temp.empty()) {
			result.push_back(temp);
		}
	} while (pos != temp.npos);

	return result;
}

void StrUtil::trim(std::queue<wchar_t>& stream) {
	while (!stream.empty()
			&& (stream.front() == ' ' || stream.front() == '\r'
					|| stream.front() == '\n')) {
		stream.pop();
	}
}

void StrUtil::eatTrim(std::wstring& str, const std::wstring& lex) {
	if (str.empty()) {
		return;
	}
	unsigned int pos = str.find_first_not_of(lex);
	if (pos == str.npos) {
		str.clear();
	} else {
		str = str.substr(pos, str.npos);
	}
}

std::string StrUtil::toString(int inputValue) {
	std::stringstream stream;
	stream << dec << inputValue;
	return stream.str();
}

std::wstring StrUtil::toWideString(int inputValue) {
	std::stringstream stream;
	stream << dec << inputValue;
	string str = stream.str();
	return wstring(str.begin(), str.end());
}

std::wstring StrUtil::toWideString(float inputValue) {
	std::stringstream stream;
	stream << inputValue;
	string str = stream.str();
	return wstring(str.begin(), str.end());
}

}
