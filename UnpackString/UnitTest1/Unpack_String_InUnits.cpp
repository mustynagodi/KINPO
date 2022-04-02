#include "pch.h"
#include "CppUnitTest.h"
#include "../UnpackString/methods.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    /**
     * \brief Class to test function Unpack_String_InUnits
     */
    TEST_CLASS(UnitsToUnpackedStringTests)
    {
    public:
        /**
         * \brief Empty array of units
         */
        TEST_METHOD(EmptyUnits)
        {
            // Arrange
            const std::vector<Unit> units = {};
            const std::string expected;

            // Act
            const std::string result = Unpack_String_InUnits(units);

            // Assert
            Assert::AreEqual(expected, result);
        }

        /**
         * \brief Only single unit
         */
        TEST_METHOD(OnlySingleUnits)
        {
            // Arrange
            const std::vector<Unit> units = { {1, 'A'}, {1, 'B'}, {1, 'C'} };
            const std::string expected = "ABC";

            // Act
            const std::string result = Unpack_String_InUnits(units);

            // Assert
            Assert::AreEqual(expected, result);
        }

        /**
         * \brief Repeating unit
         */
        TEST_METHOD(OnlyMultipleUnits)
        {
            // Arrange
            const std::vector<Unit> units = { {2, 'A'}, {3, 'B'}, {4, 'C'} };
            const std::string expected = "AABBBCCCC";

            // Act
            const std::string result = Unpack_String_InUnits(units);

            // Assert
            Assert::AreEqual(expected, result);
        }

        /**
         * \brief Mixed unit
         */
        TEST_METHOD(AllKindsOfUnits)
        {
            // Arrange
            const std::vector<Unit> units = { {2, 'A'}, {1, 'B'}, {4, 'C'} };
            const std::string expected = "AABCCCC";

            // Act
            const std::string result = Unpack_String_InUnits(units);

            // Assert
            Assert::AreEqual(expected, result);
        }
    };
}
