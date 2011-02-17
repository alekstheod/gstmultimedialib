#include <Utilities/Xml/XmlNode.h>
#include <Utilities/StrUtil/StrUtil.h>

namespace utils {

    using namespace std;

    const wchar_t XmlNode::CONST_TAG_BEGIN_SYMBOL = L'<';
    const wchar_t XmlNode::CONST_TAG_END_SYMBOL = L'>';
    const wchar_t XmlNode::CONST_TAG_CLOSE_SYMBOL = L'/';
    const wchar_t XmlNode::CONST_TEXT_START_SYMBOL = L'"';
    const wchar_t XmlNode::CONST_LEXICAL_DELIMITER_SYMBOL = L' ';
    const wchar_t XmlNode::CONST_TAG_ARGUMENT_SIGN_SYMBOL = L'=';
    const std::wstring XmlNode::CONST_TAG_ARGUMENT_VALUE_DELIMITERS = L"\"'";
    const std::wstring XmlNode::CONST_XML_DELIMITERS = L"\r\n ";

    XmlNode::XmlNode(std::wstring& stream)throw (XmlException) {
        StrUtil::EatTrim(stream, CONST_XML_DELIMITERS);
        if (!stream.empty() && stream[0] != CONST_TAG_BEGIN_SYMBOL) {
            throw XmlException("Wrong XML string");
        }
        stream = stream.substr(1, stream.npos);

        StrUtil::EatTrim(stream, CONST_XML_DELIMITERS);
        if (stream.empty()) {
            throw XmlException("Wrong XML string");
        }

        unsigned int pos = stream.find_first_of(L" /\r\n>");
        if (pos == stream.npos) {
            throw XmlException("Wrong XML string");
        }

        _objectName = stream.substr(0, pos);
        stream = stream.substr(pos, stream.npos);
        StrUtil::EatTrim(stream, CONST_XML_DELIMITERS);

        if (stream.empty()) {
            throw XmlException("Wrong XML string");
        }

        if (IsEndOfTag(stream)) {
            return;
        } else if (stream[0] != CONST_TAG_END_SYMBOL) {
            ReadAttributes(stream);
        } else {
            stream = stream.substr(1, stream.npos);
        }

        if (IsEndOfTag(stream)) {
            return;
        } else {
            ReadBody(stream);
        }

        ReadCloseTag(stream);
    }

    XmlNode::~XmlNode(void) {
    }

    void utils::XmlNode::ReadAttributes(std::wstring& stream) throw (XmlException) {
        StrUtil::EatTrim(stream, CONST_XML_DELIMITERS);
        while (!stream.empty() && !IsEndOfTag(stream) && stream[0] != CONST_TAG_END_SYMBOL) {
            std::wstring attributeName = ReadAttributeName(stream);
            std::wstring attributeValue = ReadAttributeValue(stream);
            std::pair<std::wstring, std::wstring> newEntry(attributeName, attributeValue);
            if (_attributes.insert(newEntry).second == false) {
                throw XmlException("Wrong XML string");
            }
            StrUtil::EatTrim(stream, CONST_XML_DELIMITERS);
            if (stream.empty()) {
                throw XmlException("Wrong XML string");
            }
        }
        if (stream.empty()) {
            throw XmlException("Wrong XML string");
        }
        if (stream[0] == CONST_TAG_END_SYMBOL) {
            stream = stream.substr(1, stream.npos);
        }
    }

    void utils::XmlNode::ReadBody(std::wstring& stream) throw (XmlException) {
        StrUtil::EatTrim(stream, CONST_XML_DELIMITERS);
        if (stream.empty()) {
            throw XmlException("Wrong XML string");
        }
        if (stream[0] == CONST_TAG_BEGIN_SYMBOL) {
            while (!IsACloseTagSymbols(stream)) {
                if (IsComment(stream)) {
                    ReadComment(stream);
                } else {
                    XmlNode xmlObject(stream);
                    _childObjects.push_back(xmlObject);
                }
            }
        } else {
            if (!stream.empty()) {
                unsigned int pos = stream.find_first_of(CONST_TAG_BEGIN_SYMBOL);
                if (pos == stream.npos) {
                    throw XmlException("Wrong XML string");
                }
                _xmlValue = stream.substr(0, pos);
                stream = stream.substr(pos, stream.npos);
            } else {
                throw XmlException("Wrong XML string");
            }
        }
    }

    void utils::XmlNode::ReadCloseTag(std::wstring& stream) throw (XmlException) {
        StrUtil::EatTrim(stream, CONST_XML_DELIMITERS);
        if (stream.empty() || stream[0] != CONST_TAG_BEGIN_SYMBOL) {
            throw XmlException("Wrong XML string");
        }
        stream = stream.substr(1, stream.npos);
        StrUtil::EatTrim(stream, CONST_XML_DELIMITERS);
        if (stream.empty() || stream[0] != CONST_TAG_CLOSE_SYMBOL) {
            throw XmlException("Wrong XML string");
        }
        stream = stream.substr(1, stream.npos);
        StrUtil::EatTrim(stream, L" \r\n");
        std::wstring xmlTag;
        unsigned int pos = stream.find_first_of(CONST_TAG_END_SYMBOL);
        if (pos == stream.npos) {
            throw XmlException("Wrong XML string");
        }

        xmlTag = stream.substr(0, pos);
        stream = stream.substr(pos, stream.npos);

        if (stream.empty()) {
            throw XmlException("Wrong XML string");
        }
        if (xmlTag != _objectName) {
            throw XmlException("Wrong XML string");
        }
        if (stream[0] != CONST_TAG_END_SYMBOL) {
            throw XmlException("Wrong XML string");
        }
        stream = stream.substr(1, stream.npos);
    }

    bool utils::XmlNode::IsEndOfTag(std::wstring& stream) throw (XmlException) {
        StrUtil::EatTrim(stream, CONST_XML_DELIMITERS);
        if (stream.length() > 2 && stream[0] == CONST_TAG_CLOSE_SYMBOL && stream[1] == CONST_TAG_END_SYMBOL) {
            stream = stream.substr(2, stream.npos);
        }
        if (stream.empty()) {
            throw XmlException("Wrong XML string");
        }
        return false;
    }

    std::wstring utils::XmlNode::ReadAttributeName(std::wstring& stream) throw (XmlException) {
        StrUtil::EatTrim(stream, CONST_XML_DELIMITERS);
        std::wstring argName;
        unsigned int pos = stream.find_first_of(L" \r\n><'=");
        if (pos == stream.npos) {
            throw XmlException("Wrong XML string");
        }

        argName = stream.substr(0, pos);
        stream = stream.substr(pos, stream.npos);
        StrUtil::EatTrim(stream, CONST_XML_DELIMITERS);
        if (stream.empty()) {
            throw XmlException("Wrong XML string");
        }
        if (stream[0] != CONST_TAG_ARGUMENT_SIGN_SYMBOL) {
            throw XmlException("Wrong XML string");
        }
        stream = stream.substr(1, stream.npos);
        return argName;
    }

    std::wstring utils::XmlNode::ReadAttributeValue(std::wstring& stream) throw (XmlException) {
        StrUtil::EatTrim(stream, CONST_XML_DELIMITERS);
        if (stream.empty()) {
            throw XmlException("Wrong XML string");
        }
        std::wstring argValue;
        if (CONST_TAG_ARGUMENT_VALUE_DELIMITERS.find(stream[0]) != CONST_TAG_ARGUMENT_VALUE_DELIMITERS.npos) {
            wchar_t delimiter = stream[0];
            stream = stream.substr(1, stream.npos);

            unsigned int pos = stream.find_first_of(delimiter);
            if (pos == stream.npos) {
                throw XmlException("Wrong XML string");
            }

            argValue = stream.substr(0, pos);
            if (argValue.empty()) {
                throw XmlException("Wrong XML string");
            }
            stream = stream.substr(pos + 1, stream.npos);
        } else {
            unsigned int pos = stream.find_first_of(L" \r\n>/");
            if (pos == stream.npos) {
                throw XmlException("Wrong XML string");
            }

            argValue = stream.substr(0, pos);
            if (argValue.empty()) {
                throw XmlException("Wrong XML string");
            }

            stream = stream.substr(pos + 1, stream.npos);
        }
        return argValue;
    }

    bool utils::XmlNode::IsACloseTagSymbols(std::wstring& stream) {
        if (stream.length() < 2 || stream[0] != CONST_TAG_BEGIN_SYMBOL || stream[1] != CONST_TAG_CLOSE_SYMBOL) {
            return false;
        }
        return true;
    }

    bool utils::XmlNode::IsComment(const std::wstring& stream) throw (XmlException) {
        if (stream.empty()) {
            throw XmlException("Wrong XML string");
        }
        if (stream.length() < 4) {
            return false;
        }
        if (stream[0] != CONST_TAG_BEGIN_SYMBOL) {
            return false;
        }
        std::wstring temp = stream.substr(1, stream.npos);
        StrUtil::EatTrim(temp, CONST_XML_DELIMITERS);
        if (temp.length() < 3) {
            throw XmlException("Wrong XML string");
        }
        if (temp[0] != L'!' || temp[1] != L'-' || temp[2] != L'-') {
            return false;
        }
        return true;
    }

    void utils::XmlNode::ReadComment(std::wstring& stream) throw (XmlException) {
        if (stream.empty() || !IsComment(stream)) {
            throw XmlException("Wrong XML string");
        }
        if (stream.length() < 7) {
            throw XmlException("Wrong XML string");
        }
        unsigned int pos = stream.find(L"-->");
        if (pos == stream.npos) {
            throw XmlException("Wrong XML string");
        }
        stream = stream.substr(pos + 3, stream.npos);
    }

}
