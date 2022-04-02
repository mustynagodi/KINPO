#include "pch.h"
#include "CppUnitTest.h"
#include "../UnpackString/methods.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    /**
     * \brief Класс тестирования функции SplitStringToUnits
     */
    TEST_CLASS(SplitStringToUnitsTests)
    {
    public:
        /**
         * \brief Only one character
         */
        TEST_METHOD(OneChar)
        {
            // Arrange
            const std::string_view s = "A";
            const std::vector<Unit> expected = { {1, 'A'} };

            // Act
            const std::vector<Unit> result = Split_String_Units(s);

            // Assert
            Assert::IsTrue(expected == result);
        }

        /**
         * \brief One repeating character
         */
        TEST_METHOD(OneRepetitiveChar)
        {
            // Arrange
            const std::string_view s = "10A";
            const std::vector<Unit> expected = { {10, 'A'} };

            // Act
            const std::vector<Unit> result = Split_String_Units(s);

            // Assert
            Assert::IsTrue(expected == result);
        }

        /**
         * \brief Few same repeating characters
         */
        TEST_METHOD(FewSingleChars)
        {
            // Arrange
            const std::string_view s = "ABCD";
            const std::vector<Unit> expected = { {1, 'A'}, {1, 'B'}, {1, 'C'}, {1, 'D'} };

            // Act
            const std::vector<Unit> result = Split_String_Units(s);

            // Assert
            Assert::IsTrue(expected == result);
        }

        /**
         * \brief Few repeating characters
         */
        TEST_METHOD(FewRepetitiveChars)
        {
            // Arrange
            const std::string_view s = "10A20B30C40D";
            const std::vector<Unit> expected = { {10, 'A'}, {20, 'B'}, {30, 'C'}, {40, 'D'} };

            // Act
            const std::vector<Unit> result = Split_String_Units(s);

            // Assert
            Assert::IsTrue(expected == result);
        }

        /**
         * \brief Mixed charcter test
         */
        TEST_METHOD(Mixed)
        {
            // Arrange
            const std::string_view s = "A20BC40D";
            const std::vector<Unit> expected = { {1, 'A'}, {20, 'B'}, {1, 'C'}, {40, 'D'} };

            // Act
            const std::vector<Unit> result = Split_String_Units(s);

            // Assert
            Assert::IsTrue(expected == result);
        }
    };
}
