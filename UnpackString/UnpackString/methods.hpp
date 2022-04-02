#pragma once
#include <string>
#include <vector>
#include <string_view>

/**
 * Unit structure containing information about character sequence
 */
struct Unit
{
    int RepeatNumber;
    char Char;
};

/**
  * \brief Unit struct equality comparison operator
  * \param[in] left_s Left comparison operand
  * \param[in] right_s Right comparison operand
  * \return boolean value on comparison
*/
inline bool operator==(const Unit left_s, const Unit right_s)
{
    if (left_s.RepeatNumber == right_s.RepeatNumber && left_s.Char == right_s.Char) {
        return true;
    }
    return false;
}

/**
 * \brief Different errors
 */
enum struct Code
{
    NoError,///< No error found
    IllegalCharacter,///< Use of forbidden symbol
    DigitAtTheEnd,///< A number at the end of the string
    StringSizeOutOfRange,///< Size of string is out of range
    RepeatNumberIsOutOfRange///< Number of repetitions of a single character outside the allowed range
};

/**
 * \brief Unpack string
 * \param[in] str string to unpack
 * \return unpacked string
 */
std::string UnpackString(std::string_view str);

/**
 * \brief split string into different units
 * \param[in] str Packed string
 * \return Array unit for each string
 */
std::vector<Unit> Split_String_Units(std::string_view str);

/**
  * \brief Check if the string is correct according to the conditions of the task
  * \param[in] str Packed string to check
  * \return Error code
 */
Code checkStringIsCorrect(std::string_view str);

/**
  * \brief Convert an array of units to an unpacked string
  * \param[in] units Array of units
  * \return Unpacked string
 */
std::string Unpack_String_InUnits(const std::vector<Unit>& units);

/**
  * \brief Split a string into an array of strings by the given limit
  * \param[in] str String to split
  * \param[in] limit Maximum number of characters in one line of the array
  * \return Array of strings split by limit
 */
std::vector<std::string> Split_String_Limit(std::string_view str, int limit);
