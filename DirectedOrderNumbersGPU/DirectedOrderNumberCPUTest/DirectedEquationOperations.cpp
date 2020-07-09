#include "pch.h"
#include "../CPUDirectedOrderNumberEquations/DirectedOrderNumberOperation.cpp"

namespace CPU_DirectedOrderNumber {
    TEST(Operation, AddStack) {

        DirectedOrderNumber firstNumber(1.0, 2.0);
        DirectedOrderNumber secondNumber(-1.0, -2.0);
        DirectedOrderNumberOperation* operations;
        operations = new DirectedOrderNumberOperation();

        DirectedOrderNumber reslut = operations->AddDirectedOrderNumber(firstNumber, secondNumber);

        EXPECT_TRUE(reslut.infimum == 0.0 && reslut.supremum == 0.0);
        ASSERT_TRUE((reslut.infimum == 0.0 && reslut.supremum == 0.0));

        delete(operations);
    }

    TEST(Operation, OverrideOperatorPlus) {

        DirectedOrderNumber firstNumber(1.0, 2.0);
        DirectedOrderNumber secondNumber(-1.0, -2.0);
        DirectedOrderNumberOperation* operations;
        operations = new DirectedOrderNumberOperation();

        DirectedOrderNumber reslut = firstNumber+secondNumber;

        EXPECT_TRUE(reslut.infimum == 0.0 && reslut.supremum == 0.0);
        ASSERT_TRUE((reslut.infimum == 0.0 && reslut.supremum == 0.0));

        delete(operations);
    }

 



    TEST(Operation, AddPointer) {

        DirectedOrderNumber firstNumber(1.0, 2.0);
        DirectedOrderNumber secondNumber(-1.0, -2.0);
        DirectedOrderNumberOperation* operations;
        operations = new DirectedOrderNumberOperation();

        operations->AddDirectedOrderNumber(&firstNumber, &secondNumber,&firstNumber);

        EXPECT_TRUE(firstNumber.infimum == 0.0 && firstNumber.supremum == 0.0);
        ASSERT_TRUE((firstNumber.infimum == 0.0 && firstNumber.supremum == 0.0));

        delete(operations);
    }
    TEST(Operation, SubstractStack) {

        DirectedOrderNumber firstNumber(1.0, 2.0);
        DirectedOrderNumber secondNumber(1.0, 2.0);
        DirectedOrderNumberOperation* operations;
        operations = new DirectedOrderNumberOperation();

        DirectedOrderNumber reslut = operations->SubstractDirectedOrderNumber(firstNumber, secondNumber);

        EXPECT_TRUE(reslut.infimum == 0.0 && reslut.supremum == 0.0);
        ASSERT_TRUE((reslut.infimum == 0.0 && reslut.supremum == 0.0));
        delete(operations);
    }

    TEST(Operation, SubstractPointer) {

        DirectedOrderNumber firstNumber(1.0, 2.0);
        DirectedOrderNumber secondNumber(1.0, 2.0);
        DirectedOrderNumberOperation* operations;
        operations = new DirectedOrderNumberOperation();

        operations->SubstractDirectedOrderNumber(&firstNumber, &secondNumber,&firstNumber);

        EXPECT_TRUE(firstNumber.infimum == 0.0 && firstNumber.supremum == 0.0);
        ASSERT_TRUE((firstNumber.infimum == 0.0 && firstNumber.supremum == 0.0));
        delete(operations);
    }

    TEST(Operation, MultipleStack) {

        DirectedOrderNumber firstNumber(1.0, 2.0);
        DirectedOrderNumber secondNumber(-1.0, -2.0);
        DirectedOrderNumberOperation* operations;
        operations = new DirectedOrderNumberOperation();

        DirectedOrderNumber reslut = operations->MultipleDirectedOrderNumber(firstNumber, secondNumber);

        EXPECT_TRUE(reslut.infimum == -4.0 && reslut.supremum == -1.0);
        ASSERT_TRUE(reslut.infimum == -4.0 && reslut.supremum == -1.0);
        delete(operations);
    }

    TEST(Operation, MultiplePointer) {

        DirectedOrderNumber firstNumber(1.0, 2.0);
        DirectedOrderNumber secondNumber(-1.0, -2.0);
        DirectedOrderNumberOperation* operations;
        operations = new DirectedOrderNumberOperation();

        operations->MultipleDirectedOrderNumber(&firstNumber, &secondNumber,&firstNumber);

        EXPECT_TRUE(firstNumber.infimum == -4.0 && firstNumber.supremum == -1.0);
        ASSERT_TRUE(firstNumber.infimum == -4.0 && firstNumber.supremum == -1.0);
        delete(operations);
    }

    TEST(Operation, DivideTwoGreater) {

        DirectedOrderNumber firstNumber(1.0, 2.0);
        DirectedOrderNumber secondNumber(0.5, 1.0);
        DirectedOrderNumberOperation* operations;
        operations = new DirectedOrderNumberOperation();

        DirectedOrderNumber reslut = operations->DivideDirectedOrderNumber(firstNumber, secondNumber);

        EXPECT_TRUE(reslut.infimum == 2.0 && reslut.supremum == 2.0);
        ASSERT_TRUE(reslut.infimum == 2.0 && reslut.supremum == 2.0);
        delete(operations);
    }


    TEST(Operation, DivideTwoLesser) {

        DirectedOrderNumber firstNumber(-1.0, -2.0);
        DirectedOrderNumber secondNumber(-0.5, -1.0);
        DirectedOrderNumberOperation* operations;
        operations = new DirectedOrderNumberOperation();

        DirectedOrderNumber reslut = operations->DivideDirectedOrderNumber(firstNumber, secondNumber);

        EXPECT_TRUE(reslut.infimum == 2.0 && reslut.supremum == 2.0);
        ASSERT_TRUE(reslut.infimum == 2.0 && reslut.supremum == 2.0);
        delete(operations);
    }

    TEST(Operation, DivideGreaterAndLesser) {

        DirectedOrderNumber firstNumber(1.0, 2.0);
        DirectedOrderNumber secondNumber(-0.5, -1.0);
        DirectedOrderNumberOperation* operations;
        operations = new DirectedOrderNumberOperation();

        DirectedOrderNumber reslut = operations->DivideDirectedOrderNumber(firstNumber, secondNumber);

        EXPECT_TRUE(reslut.infimum == -4.0 && reslut.supremum == -1.0);
        ASSERT_TRUE(reslut.infimum == -4.0 && reslut.supremum == -1.0);
        delete(operations);
    }
    TEST(Operation, DivideLesserAndGreater) {

        DirectedOrderNumber firstNumber(-1.0, -2.0);
        DirectedOrderNumber secondNumber(0.5, 1.0);
        DirectedOrderNumberOperation* operations;
        operations = new DirectedOrderNumberOperation();

        DirectedOrderNumber reslut = operations->DivideDirectedOrderNumber(firstNumber, secondNumber);

        EXPECT_TRUE(reslut.infimum == -1.0 && reslut.supremum == -4.0);
        ASSERT_TRUE(reslut.infimum == -1.0 && reslut.supremum == -4.0);
        delete(operations);
    }


    TEST(Operation, DivideHaveZeroAndGreater) {

        DirectedOrderNumber firstNumber(-1.0, 2.0);
        DirectedOrderNumber secondNumber(0.5, 1.0);
        DirectedOrderNumberOperation* operations;
        operations = new DirectedOrderNumberOperation();

        DirectedOrderNumber reslut = operations->DivideDirectedOrderNumber(firstNumber, secondNumber);

        EXPECT_TRUE(reslut.infimum == -1.0 && reslut.supremum == 2.0);
        ASSERT_TRUE(reslut.infimum == -1.0 && reslut.supremum == 2.0);
        delete(operations);
    }

    TEST(Operation, DivideHaveZeroAndLesser) {

        DirectedOrderNumber firstNumber(-1.0, 2.0);
        DirectedOrderNumber secondNumber(-0.5, -1.0);
        DirectedOrderNumberOperation* operations;
        operations = new DirectedOrderNumberOperation();

        DirectedOrderNumber reslut = operations->DivideDirectedOrderNumber(firstNumber, secondNumber);

        EXPECT_TRUE(reslut.infimum == -4.0 && reslut.supremum == 2.0);
        ASSERT_TRUE(reslut.infimum == -4.0 && reslut.supremum == 2.0);
        delete(operations);
    }


    /*

    TEST(Operation, GetTargetRealNumber) {

        
        DirectedOrderNumberOperation* operations;
        operations = new DirectedOrderNumberOperation();
        double result = operations->FindDistanceToMove(-2.0,)

        EXPECT_TRUE(reslut.infimum == -4.0 && reslut.supremum == 2.0);
        ASSERT_TRUE(reslut.infimum == -4.0 && reslut.supremum == 2.0);
        delete(operations);
    }
    */
}
