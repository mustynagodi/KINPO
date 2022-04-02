#include "CppUnitTest.h"
#include "../UnpackString/methods.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    /**
     * \brief Class to test function checkStringIsCorrect
     */
    TEST_CLASS(IsStringCorrectTests)
    {
    public:
        /**
         * \brief No error
         */
        TEST_METHOD(AllCorrect)
        {
            // Arrange
            const std::string_view s = "A10B";
            const auto expected = Code::NoError;

            // Act
            const auto result = checkStringIsCorrect(s);

            // Assert
            Assert::IsTrue(expected == result);
        }

        /**
         * \brief Last symbol is a digit
         */
        TEST_METHOD(LastIsDigit)
        {
            // Arrange
            const std::string_view s = "A10B5";
            const auto expected = Code::DigitAtTheEnd;

            // Act
            const auto result = checkStringIsCorrect(s);

            // Assert
            Assert::IsTrue(expected == result);
        }

        /**
         * \brief Содержит строчные буквы
         */
        TEST_METHOD(LowerCaseLetters)
        {
            // Arrange
            const std::string_view s = "A10B5ab";
            const auto expected = Code::IllegalCharacter;

            // Act
            const auto result = checkStringIsCorrect(s);

            // Assert
            Assert::IsTrue(expected == result);
        }

        /**
         * \brief COntain illegal symbols
         */
        TEST_METHOD(CompletelyIllegalChars)
        {
            // Arrange
            const std::string_view s = "A10B5;.";
            const auto expected = Code::IllegalCharacter;

            // Act
            const auto result = checkStringIsCorrect(s);

            // Assert
            Assert::IsTrue(expected == result);
        }
    };
}
