#include <gtest/gtest.h>

#include <value_expression.h>

using namespace GradsToGrib;

namespace {

    class ValueExpressionTest : public ::testing::Test {
    protected:

        ValueExpressionTest() {}

        virtual ~ValueExpressionTest() {}

        virtual void SetUp() {}

        virtual void TearDown() {}
    };

    TEST_F(ValueExpressionTest, MethodApplyToArray)
    {
        auto value_expression = ValueExpression{"x + 273.15"};
        std::vector<double> values{0.0, 1.0};
        value_expression.applyToArray(values.begin(), values.end(), values.begin());

        EXPECT_DOUBLE_EQ(values[0], 0.0 + 273.15);
        EXPECT_DOUBLE_EQ(values[1], 1.0 + 273.15);
    }
}
