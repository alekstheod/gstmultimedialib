#pragma once
#include <string>
#include <vector>
#include <queue>
#include <Utilities/AException.h>
#include <sstream>

namespace utils {

class bad_cast: public AException {
public:

	bad_cast(const std::string& message) :
			AException(message) {
	}

	virtual ~bad_cast(void) throw () {
	}
};

class StrUtil {
private:
	StrUtil(void);
	~StrUtil(void);

public:
	static std::wstring trim(const std::wstring& str);
	static void eatTrim(std::wstring& str, const std::wstring& lex);
	static std::vector<std::wstring> parse(const std::wstring& source,
			const std::wstring& delimiter);
	static std::vector<std::string> parse(const std::string& source,
			const std::string& delimiter);
	static void trim(std::queue<wchar_t>& stream);
	static std::string toString(int inputValue);
	static std::wstring toWideString(int inputValue);
	static std::wstring toWideString(float inputValue);

	template<class T>
	static T lexical_cast(const std::wstring& inputValue) throw (bad_cast) {
		T result;
		std::stringstream stream(
				std::string(inputValue.begin(), inputValue.end()));
		stream >> result;
		if (stream.fail() || !stream.eof()) {
			throw bad_cast("Cast failed");
		}
		return result;
	}

	template<class T>
	static T lexical_cast(const std::string& inputValue) throw (bad_cast) {
		T result;

		std::stringstream stream(inputValue);
		stream >> result;
		if (stream.fail() || !stream.eof()) {
			throw bad_cast("Cast failed");
		}
		return result;
	}
};
}
