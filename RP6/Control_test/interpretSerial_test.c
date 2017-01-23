#include "unity.h"
#include "InterpretSerial.h"

#define RUN_MY_TEST(func) RUN_TEST(func, 0)

int baseSpeed = 0;
uint8_t rightSpeed = 0;
uint8_t leftSpeed = 0;

static void setUp(void)
{
	baseSpeed = 0;
	rightSpeed = 0;
	leftSpeed = 0;
}

static void tearDown(void)
{

}

//===========================interpretMessageForSpeedValues===========================
static void interpretMessageForSpeedValues_fail_cases(void)
{
	TEST_ASSERT_EQUAL(-1, interpretMessageForSpeedValues(NULL, "50,50", &baseSpeed, &rightSpeed, &leftSpeed));
	TEST_ASSERT_EQUAL(-1, interpretMessageForSpeedValues("CONTROLLER_VALUES", NULL, &baseSpeed, &rightSpeed, &leftSpeed));
	TEST_ASSERT_EQUAL(-1, interpretMessageForSpeedValues("CONTROLLER_VALUES", "50,50", NULL, &rightSpeed, &leftSpeed));
	TEST_ASSERT_EQUAL(-1, interpretMessageForSpeedValues("CONTROLLER_VALUES", "50,50", &baseSpeed, NULL, &leftSpeed));
	TEST_ASSERT_EQUAL(-1, interpretMessageForSpeedValues("CONTROLLER_VALUES", "50,50", &baseSpeed, &rightSpeed, NULL));
	TEST_ASSERT_EQUAL(-1, interpretMessageForSpeedValues("CONTROLLER", "50,50", &baseSpeed, &rightSpeed, NULL));
	TEST_ASSERT_EQUAL(-1, interpretMessageForSpeedValues("CONTROLLER_VALUES", "50;50", &baseSpeed, &rightSpeed, NULL));
}

static void test_if_speeds_are_adjusted_correctly_interal_no_rounding(void)
{
	TEST_ASSERT_EQUAL(0, interpretMessageForSpeedValues("CONTROLLER_VALUES", "50,50", &baseSpeed, &rightSpeed, &leftSpeed));
	TEST_ASSERT_EQUAL(50, baseSpeed);
	TEST_ASSERT_EQUAL(25, rightSpeed);
	TEST_ASSERT_EQUAL(50, leftSpeed);
}

static void test_if_speeds_are_adjusted_correctly_interal_rounding(void)
{
	TEST_ASSERT_EQUAL(0, interpretMessageForSpeedValues("CONTROLLER_VALUES", "50,25", &baseSpeed, &rightSpeed, &leftSpeed));
	TEST_ASSERT_EQUAL(50, baseSpeed);
	TEST_ASSERT_EQUAL(38, rightSpeed);
	TEST_ASSERT_EQUAL(50, leftSpeed);
}

static void test_both_negative_controller_values_are_handled_correctly(void)
{
	TEST_ASSERT_EQUAL(0, interpretMessageForSpeedValues("CONTROLLER_VALUES", "-50,-50", &baseSpeed, &rightSpeed, &leftSpeed));
	TEST_ASSERT_EQUAL(-50, baseSpeed);
	TEST_ASSERT_EQUAL(50, rightSpeed);
	TEST_ASSERT_EQUAL(25, leftSpeed);
}

static void test_basespeed_negative_controller_values_are_handled_correctly(void)
{
	TEST_ASSERT_EQUAL(0, interpretMessageForSpeedValues("CONTROLLER_VALUES", "-50,25", &baseSpeed, &rightSpeed, &leftSpeed));
	TEST_ASSERT_EQUAL(-50, baseSpeed);
	TEST_ASSERT_EQUAL(38, rightSpeed);
	TEST_ASSERT_EQUAL(50, leftSpeed);
}

//===========================indexOf===========================
static void indexOf_parameter_fail_cases(void)
{
	TEST_ASSERT_EQUAL(-1, indexOf(NULL, 'a', 1));
	TEST_ASSERT_EQUAL(-1, indexOf("test", NULL, 1));
	TEST_ASSERT_EQUAL(-1, indexOf("test", 'a', 0));
}

static void test_if_right_index_of_character_is_returned(void)
{
	TEST_ASSERT_EQUAL(2, indexOf("test", 's', 4));
}

static void test_if_minus1_is_returned_if_character_is_not_is_string(void)
{
	TEST_ASSERT_EQUAL(-1, indexOf("test", 'a', 4));
}

//===========================waitForConnectRequest===========================
static void waitForConnectRequest_parameter_fail_cases(void)
{
	TEST_ASSERT_EQUAL(-1, waitForConnectRequest(NULL, "CAR"));
	TEST_ASSERT_EQUAL(-1, waitForConnectRequest("CONNECT", NULL));
}

static void test_if_minus1_is_returned_if_messages_do_not_match_the_connect_protocol(void)
{
	TEST_ASSERT_EQUAL(-1, waitForConnectRequest("MAKE_CONNECTION", "CAR"));
	TEST_ASSERT_EQUAL(-1, waitForConnectRequest("CONNECT", "NAME_OF_DEVICE"));
}

static void test_if_zero_is_returned_if_message_matches_the_connect_protocol(void)
{
	TEST_ASSERT_EQUAL(0, waitForConnectRequest("CONNECT", "CAR"));
}

//===========================checkForHeartbeat===========================
static void checkForHeartbeat_parameter_fail_cases(void)
{
	TEST_ASSERT_EQUAL(-1, checkForHeartbeat(NULL));
}

static void test_if_minus1_is_returned_if_messages_do_not_match_the_heartbeat_protocol(void)
{
	TEST_ASSERT_EQUAL(-1, checkForHeartbeat("NOT_THE_HEARTBEAT_PROTOCOL"));
}

static void test_if_zero_is_returned_if_message_matches_the_heartbeat_protocol(void)
{
	TEST_ASSERT_EQUAL(0, checkForHeartbeat("HEARTBEAT"));
}

//===========================checkForRP6StateChange===========================
static void checkForRP6StateChange_parameter_fail_cases(void)
{
	TEST_ASSERT_EQUAL(-1, checkForRP6StateChange(NULL));
}

static void test_if_minus1_is_returned_if_messages_do_not_match_the_RP6StateChance_protocol(void)
{
	TEST_ASSERT_EQUAL(-1, checkForRP6StateChange("NOT_THE_RP6StateChance_PROTOCOL"));
}

static void test_if_zero_is_returned_if_message_matches_the_RP6StateChance_STOP_protocol(void)
{
	TEST_ASSERT_EQUAL(0, checkForRP6StateChange("STOP_RP6"));
}

static void test_if_one_is_returned_if_message_matches_the_RP6StateChance_START_protocol(void)
{
	TEST_ASSERT_EQUAL(1, checkForRP6StateChange("START_RP6"));
}

//===========================checkForACK===========================
static void checkForACK_parameter_fail_cases(void)
{
	TEST_ASSERT_EQUAL(-1, checkForACK(NULL));
}

static void test_if_minus1_is_returned_if_messages_do_not_match_the_ACK_protocol(void)
{
	TEST_ASSERT_EQUAL(-1, checkForACK("NOT_THE_ACK_PROTOCOL"));
}

static void test_if_zero_is_returned_if_message_matches_the_ACK_protocol(void)
{
	TEST_ASSERT_EQUAL(0, checkForACK("ACK"));
}

//===========================checkForNACK===========================
static void checkForNACK_parameter_fail_cases(void)
{
	TEST_ASSERT_EQUAL(-1, checkForNACK(NULL));
}

static void test_if_minus1_is_returned_if_messages_do_not_match_the_NACK_protocol(void)
{
	TEST_ASSERT_EQUAL(-1, checkForNACK("NOT_THE_NACK_PROTOCOL"));
}

static void test_if_zero_is_returned_if_message_matches_the_NACK_protocol(void)
{
	TEST_ASSERT_EQUAL(0, checkForNACK("NACK"));
}

void interpretSerial_RunTestcases(void)
{
	//===========================interpretMessageForSpeedValues===========================
	RUN_MY_TEST(interpretMessageForSpeedValues_fail_cases);
	RUN_MY_TEST(test_if_speeds_are_adjusted_correctly_interal_no_rounding);
	RUN_MY_TEST(test_if_speeds_are_adjusted_correctly_interal_rounding);
	RUN_MY_TEST(test_both_negative_controller_values_are_handled_correctly);
	RUN_MY_TEST(test_basespeed_negative_controller_values_are_handled_correctly);

	//===========================indexOf===========================
	RUN_MY_TEST(indexOf_parameter_fail_cases);
	RUN_MY_TEST(test_if_right_index_of_character_is_returned);
	RUN_MY_TEST(test_if_minus1_is_returned_if_character_is_not_is_string);

	//===========================waitForConnectRequest===========================
	RUN_MY_TEST(waitForConnectRequest_parameter_fail_cases);
	RUN_MY_TEST(test_if_minus1_is_returned_if_messages_do_not_match_the_connect_protocol);
	RUN_MY_TEST(test_if_zero_is_returned_if_message_matches_the_connect_protocol);

	//===========================checkForHeartbeat===========================
	RUN_MY_TEST(checkForHeartbeat_parameter_fail_cases);
	RUN_MY_TEST(test_if_minus1_is_returned_if_messages_do_not_match_the_heartbeat_protocol);
	RUN_MY_TEST(test_if_zero_is_returned_if_message_matches_the_heartbeat_protocol);

	//===========================checkForRP6StateChange===========================
	RUN_MY_TEST(checkForRP6StateChange_parameter_fail_cases);
	RUN_MY_TEST(test_if_minus1_is_returned_if_messages_do_not_match_the_RP6StateChance_protocol);
	RUN_MY_TEST(test_if_zero_is_returned_if_message_matches_the_RP6StateChance_STOP_protocol);
	RUN_MY_TEST(test_if_one_is_returned_if_message_matches_the_RP6StateChance_START_protocol);

	//===========================checkForACK===========================
	RUN_MY_TEST(checkForACK_parameter_fail_cases);
	RUN_MY_TEST(test_if_minus1_is_returned_if_messages_do_not_match_the_ACK_protocol);
	RUN_MY_TEST(test_if_zero_is_returned_if_message_matches_the_ACK_protocol);

	//===========================checkForACK===========================
	RUN_MY_TEST(checkForNACK_parameter_fail_cases);
	RUN_MY_TEST(test_if_minus1_is_returned_if_messages_do_not_match_the_NACK_protocol);
	RUN_MY_TEST(test_if_zero_is_returned_if_message_matches_the_NACK_protocol);
}