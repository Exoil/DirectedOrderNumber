#include "pch.h"
#include "../CPUDirectedOrderNumberEquations/DirectedOrderNumber.cpp"

namespace CPU_DirectedOrderNumber {
TEST(DirectedNumber, GetRealNumber) {

    DirectedOrderNumber firstNumber(2.0, 2.0);

    firstNumber.GetRealNumber();

    EXPECT_TRUE(firstNumber.GetRealNumber() == 2.0);
    ASSERT_TRUE(firstNumber.GetRealNumber() == 2.0);
}


TEST(DirectedNumber, DivideGreaterThanZero) {

    DirectedOrderNumber firstNumber(2.0, 2.0);
    EXPECT_TRUE(firstNumber.GetDivideType() == GreaterThanZero);
    ASSERT_TRUE(firstNumber.GetDivideType() == GreaterThanZero);
}



TEST(DirectedNumber, DivideLesserThanZero) {

    DirectedOrderNumber firstNumber(-2.0, -2.0);
    EXPECT_TRUE(firstNumber.GetDivideType() == LesserThanZero);
    ASSERT_TRUE(firstNumber.GetDivideType() == LesserThanZero);
}

TEST(DirectedNumber, DivideHaveZeroFirstType) {

    DirectedOrderNumber firstNumber(-2.0, 2.0);
    EXPECT_TRUE(firstNumber.GetDivideType() == HaveZero);
    ASSERT_TRUE(firstNumber.GetDivideType() == HaveZero);
}

TEST(DirectedNumber, DivideHaveZeroSecondType) {

    DirectedOrderNumber firstNumber(2.0, -2.0);
    EXPECT_TRUE(firstNumber.GetDivideType() == HaveZero);
    ASSERT_TRUE(firstNumber.GetDivideType() == HaveZero);
}

}