#include "unity.h"
#include "InterpretSerial.h"
#include "Tools.h"

#define RUN_MY_TEST(func) RUN_TEST(func, 0)

int baseSpeed = 0;
uint8_t rightSpeed = 0;
uint8_t leftSpeed = 0;

void setUp(void)
{
	baseSpeed = 0;
	rightSpeed = 0;
	leftSpeed = 0;
}

void tearDown(void)
{

}

//===========================interpretMessageForSpeedValues===========================
static void test_if_speeds_are_adjusted_correctly_interal_no_rounding(void)
{
	setUp();

	TEST_ASSERT_EQUAL(0, interpretMessageForSpeedValues("CONTROLLER_VALUES", "50,50", &baseSpeed, &rightSpeed, &leftSpeed));
	TEST_ASSERT_EQUAL(50, baseSpeed);
	TEST_ASSERT_EQUAL(25, rightSpeed);
	TEST_ASSERT_EQUAL(50, leftSpeed);
}

static void test_if_speeds_are_adjusted_correctly_interal_rounding(void)
{
	setUp();

	TEST_ASSERT_EQUAL(0, interpretMessageForSpeedValues("CONTROLLER_VALUES", "50,25", &baseSpeed, &rightSpeed, &leftSpeed));
	TEST_ASSERT_EQUAL(50, baseSpeed);
	TEST_ASSERT_EQUAL(38, rightSpeed);
	TEST_ASSERT_EQUAL(50, leftSpeed);
}
//!!!
// TODO: MAKE MORE TEST CASES FOR SUCCES AND FAIL CASES
//!!!

void interpretSerial_RunTestcases(void)
{
	RUN_MY_TEST(test_if_speeds_are_adjusted_correctly_interal_no_rounding);
	RUN_MY_TEST(test_if_speeds_are_adjusted_correctly_interal_rounding);
}