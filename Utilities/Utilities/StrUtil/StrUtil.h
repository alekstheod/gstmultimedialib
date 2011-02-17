#pragma once
#include <string>
#include <vector>
#include <queue>
#include <Utilities/AException.h>
#include <sstream>

namespace utils {

    class bad_cast : public AException {
    public:

        bad_cast(const std::string& message) : AException(message) {
        }

        virtual ~bad_cast(void)throw () {
        }
    };

    class StrUtil {
    private:
        StrUtil(void);
        ~StrUtil(void);

    public:
        static std::wstring Trim(const std::wstring& str);
        static void EatTrim(std::wstring& str, const std::wstring& lex);
        static std::vector<std::wstring> Parse(const std::wstring& source, const std::wstring& delimiter);
        static void Trim(std::queue<wchar_t>& stream);
        static std::string ToString(int inputValue);
        static std::wstring ToWideString(int inputValue);
        static std::wstring ToWideString(float inputValue);

        template<class T>
        static T lexical_cast(const std::wstring& inputValue)throw (bad_cast) {
            T result;
            std::stringstream stream(std::string(inputValue.begin(), inputValue.end()));
            stream >> result;
            if (stream.fail() || !stream.eof()) {
                throw bad_cast("Cast failed");
            }
            return result;
        }

        template<class T>
        static T lexical_cast(const std::string& inputValue)throw (bad_cast) {
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

