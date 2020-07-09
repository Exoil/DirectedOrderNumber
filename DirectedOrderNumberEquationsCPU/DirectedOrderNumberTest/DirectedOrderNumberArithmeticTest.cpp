#include "gtest/gtest.h"
#include "../DirectedOrderNumberEquationsCPU/DirectedEquation.cpp"
#include <math.h>

void FreeMemory(DirectedOrderNumber *first, DirectedOrderNumber *second, DirectedOrderNumber *result){
    delete first;
    delete second;
    delete result;
}

TEST(ArithmeticOperation, Add) {

    DirectedOrderNumber *firstNumber;
    DirectedOrderNumber *secondNumber;
    DirectedOrderNumber *result;

    firstNumber = new DirectedOrderNumber(1.0, 2.0);
    secondNumber = new DirectedOrderNumber(-1.0, -2.0);
    result = new DirectedOrderNumber(0.0, 0.0);

    DirectedOrderNumberArithmetic* operations;
    operations = new DirectedOrderNumberArithmetic();

    operations->AddDirectedOrderNumber(firstNumber, secondNumber, result);

    EXPECT_TRUE(result->infimum == 0.0 && result->supremum == 0.0);
    ASSERT_TRUE(result->infimum == 0.0 && result->supremum == 0.0);

    FreeMemory(firstNumber, secondNumber, result);
    delete operations;
}

TEST(ArithmeticOperation, AddOperator) {

    DirectedOrderNumber firstNumber(1.0, 2.0);
    DirectedOrderNumber secondNumber(-1.0, -2.0);
    
    firstNumber = firstNumber + secondNumber;

    EXPECT_TRUE(firstNumber.infimum == 0.0 && firstNumber.supremum == 0.0);
    ASSERT_TRUE(firstNumber.infimum == 0.0 && firstNumber.supremum == 0.0);

}



TEST(ArithmeticOperation, Substract) {

    DirectedOrderNumber* firstNumber;
    DirectedOrderNumber* secondNumber;
    DirectedOrderNumber* result;

    firstNumber = new DirectedOrderNumber(1.0, 2.0);
    secondNumber = new DirectedOrderNumber(1.0, 2.0);
    result = new DirectedOrderNumber(0.0, 0.0);

    DirectedOrderNumberArithmetic* operations;
    operations = new DirectedOrderNumberArithmetic();

    operations->SubstractDirectedOrderNumber(firstNumber, secondNumber, result);

    EXPECT_TRUE(result->infimum == 0.0 && result->supremum == 0.0);
    ASSERT_TRUE(result->infimum == 0.0 && result->supremum == 0.0);

    FreeMemory(firstNumber, secondNumber, result);
    delete operations;
}

TEST(ArithmeticOperation, SubstractOperator) {

    DirectedOrderNumber firstNumber(1.0, 2.0);
    DirectedOrderNumber secondNumber(1.0, 2.0);

    firstNumber = new DirectedOrderNumber(1.0, 2.0);
    secondNumber = new DirectedOrderNumber(1.0, 2.0);



    firstNumber = firstNumber - secondNumber;

    EXPECT_TRUE(firstNumber.infimum == 0.0 && firstNumber.supremum == 0.0);
    ASSERT_TRUE(firstNumber.infimum == 0.0 && firstNumber.supremum == 0.0);

 
}



TEST(ArithmeticOperation, MultiplePointer) {

    DirectedOrderNumber* firstNumber;
    DirectedOrderNumber* secondNumber;
    DirectedOrderNumber* result;

    firstNumber = new DirectedOrderNumber(1.0, 2.0);
    secondNumber = new DirectedOrderNumber(-1.0, -2.0);
    result = new DirectedOrderNumber(0.0, 0.0);

    DirectedOrderNumberArithmetic* operations;
    operations = new  DirectedOrderNumberArithmetic();

    operations->MultipleDirectedOrderNumber(firstNumber, secondNumber, result);


    ASSERT_TRUE(result->infimum == -4.0 && result->supremum == -1.0);

    FreeMemory(firstNumber, secondNumber, result);
    delete operations;
}


TEST(ArithmeticOperation, MultipleOperator) {

    DirectedOrderNumber firstNumber(1.0, 2.0);
    DirectedOrderNumber secondNumber(-1.0, -2.0);


    firstNumber = new DirectedOrderNumber(1.0, 2.0);
    secondNumber = new DirectedOrderNumber(-1.0, -2.0);


    firstNumber = firstNumber * secondNumber;
    ASSERT_TRUE(firstNumber.infimum == -4.0 && firstNumber.supremum == -1.0);

 
}

TEST(ArithmeticOperation, DivideTwoGreater) {

    DirectedOrderNumber* firstNumber;
    DirectedOrderNumber* secondNumber;
    DirectedOrderNumber* result;


    firstNumber = new DirectedOrderNumber(1.0, 2.0);
    secondNumber = new DirectedOrderNumber(0.5, 1.0);
    result = new DirectedOrderNumber(0.0, 0.0);

    DirectedOrderNumberArithmetic* operations;
    operations = new DirectedOrderNumberArithmetic();

    operations->DivideDirectedOrderNumber(firstNumber, secondNumber, result);

    ASSERT_TRUE(result->infimum == 2.0 && result->supremum == 2.0);

    FreeMemory(firstNumber, secondNumber, result);
    delete operations;
}

TEST(ArithmeticOperation, DivideTwoGreaterOpertor) {

    DirectedOrderNumber firstNumber(1.0, 2.0);
    DirectedOrderNumber secondNumber(0.5, 1.0);


    firstNumber = firstNumber / secondNumber;

    ASSERT_TRUE(firstNumber.infimum == 2.0 && firstNumber.supremum == 2.0);


}



TEST(ArithmeticOperation, DivideTwoLesser) {

    DirectedOrderNumber* firstNumber;
    DirectedOrderNumber* secondNumber;
    DirectedOrderNumber* result;



    firstNumber = new DirectedOrderNumber(-1.0, -2.0);
    secondNumber = new DirectedOrderNumber(-0.5, -1.0);
    result = new DirectedOrderNumber(0.0, 0.0);

    DirectedOrderNumberArithmetic* operations;
    operations = new DirectedOrderNumberArithmetic();

    operations->DivideDirectedOrderNumber(firstNumber, secondNumber, result);

    ASSERT_TRUE(result->infimum == 2.0 && result->supremum == 2.0);

    FreeMemory(firstNumber, secondNumber, result);
    delete operations;
}

TEST(ArithmeticOperation, DivideGreaterAndLesser) {

    DirectedOrderNumber* firstNumber;
    DirectedOrderNumber* secondNumber;
    DirectedOrderNumber* result;


    firstNumber = new DirectedOrderNumber(1.0, 2.0);
    secondNumber = new DirectedOrderNumber(-0.5, -1.0);
    result = new DirectedOrderNumber(0.0, 0.0);

    DirectedOrderNumberArithmetic* operations;
    operations = new DirectedOrderNumberArithmetic();

    operations->DivideDirectedOrderNumber(firstNumber, secondNumber, result);

    ASSERT_TRUE(result->infimum == -4.0 && result->supremum == -1.0);

    FreeMemory(firstNumber, secondNumber, result);
    delete operations;
}


TEST(ArithmeticOperation, DivideLesserAndGreater) {

    DirectedOrderNumber* firstNumber;
    DirectedOrderNumber* secondNumber;
    DirectedOrderNumber* result;


    firstNumber = new DirectedOrderNumber(-1.0, -2.0);
    secondNumber = new DirectedOrderNumber(0.5, 1.0);
    result = new DirectedOrderNumber(0.0, 0.0);

    DirectedOrderNumberArithmetic* operations;
    operations = new DirectedOrderNumberArithmetic();

    operations->DivideDirectedOrderNumber(firstNumber, secondNumber, result);

    ASSERT_TRUE(result->infimum == -1.0 && result->supremum == -4.0);

    FreeMemory(firstNumber, secondNumber, result);
    delete operations;
}


TEST(ArithmeticOperation, DivideHaveZeroAndGreater) {

    DirectedOrderNumber* firstNumber;
    DirectedOrderNumber* secondNumber;
    DirectedOrderNumber* result;


    firstNumber = new DirectedOrderNumber(-1.0, 2.0);
    secondNumber = new DirectedOrderNumber(0.5, 1.0);
    result = new DirectedOrderNumber(0.0, 0.0);

    DirectedOrderNumberArithmetic* operations;
    operations = new DirectedOrderNumberArithmetic();

    operations->DivideDirectedOrderNumber(firstNumber, secondNumber, result);

    ASSERT_TRUE(result->infimum == -1.0 && result->supremum == 2.0);

    FreeMemory(firstNumber, secondNumber, result);
    delete operations;
}

TEST(ArithmeticOperation, DivideHaveZeroAndLesser) {

    DirectedOrderNumber* firstNumber;
    DirectedOrderNumber* secondNumber;
    DirectedOrderNumber* result;

    firstNumber = new DirectedOrderNumber(-1.0, 2.0);
    secondNumber = new DirectedOrderNumber(-0.5, -1.0);
    result = new DirectedOrderNumber(0.0, 0.0);

    DirectedOrderNumberArithmetic* operations;
    operations = new DirectedOrderNumberArithmetic();

    operations->DivideDirectedOrderNumber(firstNumber, secondNumber, result);

    ASSERT_TRUE(result->infimum == -4.0 && result->supremum == 2.0);

    FreeMemory(firstNumber, secondNumber, result);
    delete operations;
}

TEST(ArithmeticOperation, DivideHaveGreaterAndZero) {

    DirectedOrderNumber* firstNumber;
    DirectedOrderNumber* secondNumber;
    DirectedOrderNumber* result;

    firstNumber = new DirectedOrderNumber(4.0, 12.0);
    secondNumber = new DirectedOrderNumber(-2.0, 6.0);
    result = new DirectedOrderNumber(0.0, 0.0);

    DirectedOrderNumberArithmetic* operations;
    operations = new DirectedOrderNumberArithmetic();

    operations->DivideDirectedOrderNumber(firstNumber, secondNumber, result);


    ASSERT_TRUE(result->infimum == 4.0 && result->supremum == 1.6);

    FreeMemory(firstNumber, secondNumber, result);
    delete operations;
}

TEST(ArithmeticOperation, DivideHaveLesserAndZero) {

    DirectedOrderNumber* firstNumber;
    DirectedOrderNumber* secondNumber;
    DirectedOrderNumber* result;

    firstNumber = new DirectedOrderNumber(-4.0, -12.0);
    secondNumber = new DirectedOrderNumber(-2.0, 6.0);
    result = new DirectedOrderNumber(0.0, 0.0);

    DirectedOrderNumberArithmetic* operations;
    operations = new DirectedOrderNumberArithmetic();

    operations->DivideDirectedOrderNumber(firstNumber, secondNumber, result);


    ASSERT_TRUE(result->infimum == 0.0 && result->supremum == -0.8);

    FreeMemory(firstNumber, secondNumber, result);
    delete operations;
}



TEST(ArithmeticOperation, DivideHaveHaveZeroAndZero) {

    DirectedOrderNumber* firstNumber;
    DirectedOrderNumber* secondNumber;
    DirectedOrderNumber* result;

    firstNumber = new DirectedOrderNumber(-4.0, 20.0);
    secondNumber = new DirectedOrderNumber(-2.0, 6.0);
    result = new DirectedOrderNumber(0.0, 0.0);

    DirectedOrderNumberArithmetic* operations;
    operations = new DirectedOrderNumberArithmetic();

    operations->DivideDirectedOrderNumber(firstNumber, secondNumber, result);


    ASSERT_TRUE(result->infimum == 0.0 && result->supremum == 2.4);

    FreeMemory(firstNumber, secondNumber, result);
    delete operations;
}


TEST(ArithmeticOperation, DivideOperatorDivideZero) {

    DirectedOrderNumber firstNumber(4.0,12);
    DirectedOrderNumber secondNumber(-2.0,4.0);
    
    firstNumber = firstNumber / secondNumber;

    ASSERT_TRUE(floor(firstNumber.infimum) == 8.0 && ceil(firstNumber.supremum)== 24);
    
}