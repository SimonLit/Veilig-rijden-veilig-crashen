#include "unity.h"
#include "Tools.h"

#define RUN_MY_TEST(func) RUN_TEST(func, 0)

char* testMessage_base = "test";
char testMessage[5] = "test";

static void setUp(void)
{
	memset(protocolMessageToSend, 0, sizeof(protocolMessageToSend));
	for(int i = 0; i < sizeof(testMessage); i++)
	{
		testMessage[i] = testMessage_base[i];
	} 
}

static void tearDown(void)
{
}

//===========================makeProtocolMessage===========================
static void makeProtocolMessage_parameter_fail_cases(void)
{
	TEST_ASSERT_EQUAL(-1, makeProtocolMessage(NULL));
}

static void test_if_minus1_is_returned_when_message_length_goes_out_of_boundries(void)
{
	// The max message legth is 20. This includes the '\0'. Two characters are added 
	// and thus the max parameter message length can only be 17 characters long.
	TEST_ASSERT_EQUAL(-1, makeProtocolMessage("123456789123456789"));
}

static void test_is_protocol_characters_are_added_makeProtocolMessage(void)
{
	TEST_ASSERT_EQUAL(0, makeProtocolMessage(testMessage));
	TEST_ASSERT_EQUAL_STRING("#test@", protocolMessageToSend);
}

//===========================makeProtocolMessageWithValue===========================
static void makeProtocolMessageWithValue_parameter_fail_cases(void)
{
	TEST_ASSERT_EQUAL(-1, makeProtocolMessageWithValue(NULL, testMessage));
	TEST_ASSERT_EQUAL(-1, makeProtocolMessageWithValue(testMessage, NULL));
}

static void test_if_minus1_is_returned_when_message_plus_value_length_goes_out_of_boundries(void)
{
	// The max message legth is 20. This includes the '\0'. Two characters are added 
	// and thus the max parameter message length can only be 17 characters long.
	// 18 characters is out of boundries. For testing give 9 characters to each parameter.
	TEST_ASSERT_EQUAL(-1, makeProtocolMessageWithValue("123456789", "123456789"));
}

static void test_is_protocol_characters_are_added_makeProtocolMessageWithValue(void)
{
	TEST_ASSERT_EQUAL(0, makeProtocolMessageWithValue(testMessage, "value"));
	TEST_ASSERT_EQUAL_STRING("#test:value@", protocolMessageToSend);
}

//===========================map===========================
static void test_if_values_are_mapped_correctly(void)
{
	TEST_ASSERT_EQUAL_UINT16(10, map(5, 0, 10, 0, 20));
}

static void test_if_values_are_mapped_correctly_when_negative(void)
{
	TEST_ASSERT_EQUAL_UINT16(0, map(5, 0, 10, -20, 20));
}

static void test_if_values_are_mapped_correctly_when_rounding_is_needed(void)
{
	TEST_ASSERT_EQUAL_UINT16(2, map(5, 0, 10, 0, 5));
}

//===========================uint8_tToString===========================
static void uint8_tToString_parameter_fail_cases(void)
{
	TEST_ASSERT_EQUAL(-1, uint8_tToString(0, NULL, 5));
}

static void test_if_at_most_stringLength_minus_1_is_written_to_string(void)
{
	TEST_ASSERT_EQUAL(3, uint8_tToString(123, testMessage, 2));
	TEST_ASSERT_EQUAL_STRING("1", testMessage);

	TEST_ASSERT_EQUAL(3, uint8_tToString(123, testMessage, sizeof(testMessage)));
	TEST_ASSERT_EQUAL_STRING("123", testMessage);
}

//===========================uint16_tToString===========================
static void uint16_tToString_parameter_fail_cases(void)
{
	TEST_ASSERT_EQUAL(-1, uint16_tToString(0, NULL, 5));
}

static void test_if_at_most_stringLength_minus_1_is_written_to_string_uint16_tToString(void)
{
	TEST_ASSERT_EQUAL(3, uint16_tToString(123, testMessage, 2));
	TEST_ASSERT_EQUAL_STRING("1", testMessage);

	TEST_ASSERT_EQUAL(3, uint16_tToString(123, testMessage, sizeof(testMessage)));
	TEST_ASSERT_EQUAL_STRING("123", testMessage);

	TEST_ASSERT_EQUAL(5, uint16_tToString(12345, testMessage, sizeof(testMessage)));
	TEST_ASSERT_EQUAL_STRING("1234", testMessage);
}

void tools_RunTestcases(void)
{
	//===========================makeProtocolMessage===========================
	RUN_MY_TEST(makeProtocolMessage_parameter_fail_cases);
	RUN_MY_TEST(test_if_minus1_is_returned_when_message_length_goes_out_of_boundries);
	RUN_MY_TEST(test_is_protocol_characters_are_added_makeProtocolMessage);

	//===========================makeProtocolMessageWithValue===========================
	RUN_MY_TEST(makeProtocolMessageWithValue_parameter_fail_cases);
	RUN_MY_TEST(test_if_minus1_is_returned_when_message_plus_value_length_goes_out_of_boundries);
	RUN_MY_TEST(test_is_protocol_characters_are_added_makeProtocolMessageWithValue);

	//===========================map===========================
	RUN_MY_TEST(test_if_values_are_mapped_correctly);
	RUN_MY_TEST(test_if_values_are_mapped_correctly_when_negative);
	RUN_MY_TEST(test_if_values_are_mapped_correctly_when_rounding_is_needed);

	//===========================uint8_tToString===========================
	RUN_MY_TEST(uint8_tToString_parameter_fail_cases);
	RUN_MY_TEST(test_if_at_most_stringLength_minus_1_is_written_to_string);

	//===========================uint8_tToString===========================
	RUN_MY_TEST(uint16_tToString_parameter_fail_cases);
	RUN_MY_TEST(test_if_at_most_stringLength_minus_1_is_written_to_string_uint16_tToString);
}