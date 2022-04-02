#include "pch.h"
#include "CppUnitTest.h"
#include "../UnpackString/methods.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::string_literals;

namespace UnitTest1
{
    /**
     * \brief Function test class UnitsToUnpackedString
     */
    TEST_CLASS(UnpackStringTests)
    {
    public:
        /**
         * \brief Single Character test
         */
        TEST_METHOD(SingleCharacter)
        {
            const std::string s = "A";

            const auto result = UnpackString(s);

            Assert::AreEqual(s, result);
        }

        /**
         * \brief few characters
         */
        TEST_METHOD(FewSingleCharacters)
        {
            const std::string s = "ABC";

            const auto result = UnpackString(s);

            Assert::AreEqual(s, result);
        }

        /**
         * \brief Repetative charcater test
         */
        TEST_METHOD(SingleRepetetiveCharacter)
        {
            const std::string s = "10A";

            const auto result = UnpackString(s);

            const std::string expected = "AAAAAAAAAA";
            Assert::AreEqual(expected, result);
        }

        /**
         * \brief Mutiple repetative charcater test
         */
        TEST_METHOD(FewRepetetiveCharacter)
        {
            const std::string s = "10A5B2C";

            const auto result = UnpackString(s);

            const std::string expected = "AAAAAAAAAABBBBBCC";
            Assert::AreEqual(expected, result);
        }


        /**
         * \brief Mixed string charcter test
         */
        TEST_METHOD(Mixed)
        {
            const std::string s = "10AS5BZY2CX";

            const auto result = UnpackString(s);

            const std::string expected = "AAAAAAAAAASBBBBBZYCCX";
            Assert::AreEqual(expected, result);
        }

        /**
         * \brief Empty string test
         */
        TEST_METHOD(StringIsEmpty)
        {
            const std::string_view s = "";

            try
            {
                UnpackString(s);
                Assert::Fail();
            }
            catch (std::exception& exception)
            {
                const auto expectedMessage = "String must not exceed size in allowed range of [1; 80]";
                Assert::AreEqual(expectedMessage, exception.what());
            }
        }

        /**
         * \brief Out of range string
         */
        TEST_METHOD(StringIsTooLong)
        {
            const std::string_view s =
                "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

            try
            {
                UnpackString(s);
                Assert::Fail();
            }
            catch (std::exception& exception)
            {
                const auto expectedMessage = "String must not exceed size in allowed range of [1; 80]";
                Assert::AreEqual(expectedMessage, exception.what());
            }
        }

        /**
         * \brief Illegal charcater test
         */
        TEST_METHOD(StringHasIlliegalChars)
        {
            const std::string_view s = "AbC";

            try
            {
                UnpackString(s);
                Assert::Fail();
            }
            catch (std::exception& exception)
            {
                const auto expectedMessage =
                    "String contains illegal character! Allowed only upper case Latin letters and digits!";
                Assert::AreEqual(expectedMessage, exception.what());
            }
        }

        /**
         * \brief Digit at end of string test
         */
        TEST_METHOD(StringHasDigitAtTheEnd)
        {
            const std::string_view s = "ABC10";

            try
            {
                UnpackString(s);
                Assert::Fail();
            }
            catch (std::exception& exception)
            {
                const auto expectedMessage = "String must not contain digit at the end!";
                Assert::AreEqual(expectedMessage, exception.what());
            }
        }

        /**
         * \brief 
         */
        TEST_METHOD(RepeatNumberIsTooLow)
        {
            const std::string_view s = "1A";

            try
            {
                UnpackString(s);
                Assert::Fail();
            }
            catch (std::exception& exception)
            {
                const auto expectedMessage = "Character repeat is out of range! Its value must be in [2; 99]!";
                Assert::AreEqual(expectedMessage, exception.what());
            }
        }

        /**
         * \brief 
         */
        TEST_METHOD(RepeatNumberIsTooHigh)
        {
            const std::string_view s = "100A";

            try
            {
                UnpackString(s);
                Assert::Fail();
            }
            catch (std::exception& exception)
            {
                const auto expectedMessage = "Character repeat is out of range! Its value must be in [2; 99]!";
                Assert::AreEqual(expectedMessage, exception.what());
            }
        }
    };
}
