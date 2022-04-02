#include "pch.h"
#include "CppUnitTest.h"
#include "../UnpackString/methods.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::string_literals;


namespace UnitTests
{
    /**
     * \brief class to test function Split_String_Limit
     */
    TEST_CLASS(SplitStringToLimitTests)
    {
    public:
        /**
         * \brief String less than the limit
         */
        TEST_METHOD(UnderLimit)
        {
            const std::string s = UnpackString("39A");
            const std::vector expected = { std::string(39, 'A') };

            const auto result = Split_String_Limit(s, 40);

            Assert::IsTrue(expected == result);
        }

        /**
         * \brief String length equals to limit
         */
        TEST_METHOD(ExactLimit)
        {
            const std::string s = UnpackString("40A");
            const std::vector expected = { std::string(40, 'A') };

            const auto result = Split_String_Limit(s, 40);

            Assert::IsTrue(expected == result);
        }

        /**
         * \brief Many limit eqivalent
         */
        TEST_METHOD(FewWithExactLimit)
        {
            const std::string s = UnpackString("40A40B40C");
            const std::vector expected = { std::string(40, 'A'), std::string(40, 'B'), std::string(40, 'C') };

            const auto result = Split_String_Limit(s, 40);

            Assert::IsTrue(expected == result);
        }

        /**
         * \brief Not all equivalent to limit max
         */
        TEST_METHOD(NotExactLimit)
        {
            const std::string s = UnpackString("40A40B40C23Z");
            const std::vector expected = {
                std::string(40, 'A'), std::string(40, 'B'), std::string(40, 'C'), std::string(23, 'Z')
            };

            const auto result = Split_String_Limit(s, 40);

            Assert::IsTrue(expected == result);
        }

        /**
         * \brief Wrong limit
         */
        TEST_METHOD(InvalidLimit)
        {
            const std::string s = UnpackString("39A");
            const std::vector<std::string> expected = {};

            const auto result = Split_String_Limit(s, -42);

            Assert::IsTrue(expected == result);
        }

        /**
         * \brief Пустая строка
         */
        TEST_METHOD(EmptyString)
        {
            const std::string s;
            const std::vector<std::string> expected = {};

            const auto result = Split_String_Limit(s, 40);

            Assert::IsTrue(expected == result);
        }
    };
}
