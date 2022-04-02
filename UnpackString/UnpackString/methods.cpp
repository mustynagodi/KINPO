#include "methods.hpp"

#include <algorithm>
#include <charconv>
#include <stdexcept>
#include <functional>

/**
  * \brief The exception class for input errors. Able to turn the error code into a string.
*/
struct DataError final : std::invalid_argument
{
    using std::invalid_argument::invalid_argument;

    /**
      * \brief Parameterized constructor from ErrorCode
      * \param[in] code Error code
    */
    explicit DataError(const Code code) : DataError(ToString(code))
    {
    }

private:
    static std::string ToString(const Code code)
    {
        switch (code)
        {
        case Code::NoError:
            return "No Error";
        case Code::IllegalCharacter:
            return "String contains illegal character! Allowed only upper case Latin letters and digits!";
        case Code::DigitAtTheEnd:
            return "String must not contain digit at the end!";
        case Code::StringSizeOutOfRange:
            return "String must not exceed size in allowed range of [1; 80]";
        case Code::RepeatNumberIsOutOfRange:
            return "Character repeat is out of range! Its value must be in [2; 99]!";
        default:;
        }

        return "";
    }
};

std::string UnpackString(const std::string_view str)
{
    if (str.empty() || str.size() > 80)
        throw DataError{ Code::StringSizeOutOfRange };

    if (const auto error = checkStringIsCorrect(str);
        error != Code::NoError)
        throw DataError{ error };

    const std::vector<Unit> units = Split_String_Units(str);

    return Unpack_String_InUnits(units);
}

std::vector<Unit> Split_String_Units(const std::string_view str)
{
    std::vector<Unit> units;

    for (auto it = str.begin(); it != str.end(); ++it)
    {
        if (std::isalpha(*it))
        {
            units.push_back({ 1, *it });
            continue;
        }

        const auto numBegin = it;
        const auto numEnd = std::find_if(it, str.end(), std::not_fn(std::isdigit));
        const std::string_view numStr = str.substr(numBegin - str.begin(), numEnd - str.begin());
        int number = 0;
        std::from_chars(numStr.data(), numStr.data() + numStr.size(), number);

        if (number < 2 || number > 99)
            throw DataError{ Code::RepeatNumberIsOutOfRange };

        units.push_back({ number, *numEnd });
        it = numEnd;
    }

    return units;
}

Code checkStringIsCorrect(const std::string_view str)
{
    const auto isUpperCaseLetter = [](const char c) { return std::isalpha(c) && std::isupper(c); };
    const bool correctChars = std::all_of(
        str.begin(),
        str.end(),
        [=](const char c) { return isUpperCaseLetter(c) || std::isdigit(c); }
    );

    if (!correctChars)
        return Code::IllegalCharacter;

    if (const bool lastCharIsDigit = std::isdigit(str.back()); lastCharIsDigit)
        return Code::DigitAtTheEnd;

    return Code::NoError;
}

std::string Unpack_String_InUnits(const std::vector<Unit>& units)
{
    int totalCount = 0;
    for (const auto [RepeatNumber, _] : units)
        totalCount += RepeatNumber;

    std::string str;
    str.reserve(totalCount);

    for (const auto [RepeatNumber, Char] : units)
        str += std::string(RepeatNumber, Char);

    return str;
}

std::vector<std::string> Split_String_Limit(const std::string_view str, const int limit)
{
    if (limit <= 0)
    {
        return {};
    }

    const auto fullLimitSizeCount = str.size() / limit;
    const auto lastPartSize = str.size() % limit;

    std::vector<std::string> res;
    res.reserve(fullLimitSizeCount + 1);

    for (int i = 0; i < fullLimitSizeCount; ++i)
    {
        const auto part = str.substr(limit * i, limit);
        res.emplace_back(part);
    }

    if (lastPartSize > 0)
    {
        const auto lastPart = str.substr(str.size() - lastPartSize, lastPartSize);
        res.emplace_back(lastPart);
    }

    return res;
}
