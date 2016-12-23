#include "../libs/datastruct/datastruct.h"
#include "../libs/message/message.h"
#include <string.h>
#include "unity.h"

#define MY_RUN_TEST(func) RUN_TEST(func, 0)

const char* ms = "#CONNECT:CAR@";
char buffer[256];
int rv, tmp;

void setUp(void)
{
	for(int i = 0; i < 256; i++)
	{
		buffer[i] = 0;
	}
	rv = -10;
	tmp = 0;
}

void tearDown(void)
{
	for(int i = 0; i < 256; i++)
	{
		buffer[i] = 0;
	}    
	rv = 0;
	tmp = 0;
}

////////////////////////////////////////////////////
///                                              ///
///               MESSAGE TESTS                  ///
///                                              ///
////////////////////////////////////////////////////

void message_Start_Test(void)
{
	rv = findStartOfMessage(ms);
	TEST_ASSERT_EQUAL(0, rv);
}

void message_End_Test(void)
{
	rv = findEndOfMessage(ms);
	TEST_ASSERT_EQUAL(12, rv);
}

void message_Lenght_Test(void)
{
	rv = lengthOfMessage(ms);
	TEST_ASSERT_EQUAL(12, rv);
}

void message_Correct_Format_Check_Test(void)
{
	char array[] = "#CONNECT:CAR@";
	rv = correctFormatCheckRemoveBitshift(array);
	TEST_ASSERT_EQUAL_STRING("CONNECT:CAR", array);
}

void message_Split_Test(void)
{
	char** ar = NULL;
	char array[] = "#CONNECT:CAR@";
	rv = correctFormatCheckRemoveBitshift(array);
	rv = split(array, ':', &ar);
	TEST_ASSERT_EQUAL(2, rv);
	TEST_ASSERT_EQUAL_STRING("CONNECT",ar[0]);
	TEST_ASSERT_EQUAL_STRING( "CAR", ar[1]);
}

void check_Sender_Test(void)
{
	DATAPACKET connection;
	char** ar = NULL;
	char array[] = "#CONNECT:CAR@";
	rv = correctFormatCheckRemoveBitshift(array);
	rv = split(array, ':', &ar);
	rv = checkSender(&connection, ar[1]);
	TEST_ASSERT_EQUAL(CAR, connection.Sender);
}

void verification_Test(void)
{
	DATAPACKET connection;
	rv = verificationStringCut(&connection, ms);
	TEST_ASSERT_EQUAL(0, rv);
	TEST_ASSERT_EQUAL(CAR, connection.Sender);
}

////////////////////////////////////////////////////
///                                              ///
///              RESPONSE TESTS                  ///
///                                              ///
////////////////////////////////////////////////////


////////////////////////////////////////////////////
///                                              ///
///            FILE HANDELING TESTS              ///
///                                              ///
////////////////////////////////////////////////////


int main (int argc, char * argv[])
{
    UnityBegin();
    setUp();
    MY_RUN_TEST(message_Start_Test);
    tearDown();
    setUp();
    MY_RUN_TEST(message_End_Test);
    tearDown();
    setUp();
    MY_RUN_TEST(message_Lenght_Test);
    tearDown();
    setUp();
    MY_RUN_TEST(message_Correct_Format_Check_Test);
    tearDown();
    setUp();
    MY_RUN_TEST(message_Split_Test);
    tearDown();
    setUp();
    MY_RUN_TEST(check_Sender_Test);
    tearDown();
    setUp();
    MY_RUN_TEST(verification_Test);
    tearDown();
    return UnityEnd();
}

