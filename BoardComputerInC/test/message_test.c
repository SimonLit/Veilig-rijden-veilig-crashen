#include "../libs/datastruct/datastruct.h"
#include "../libs/message/message.h"
#include "unity.h"

#define MY_RUN_TEST(func) RUN_TEST(func, 0)

const char* ms = "#CONNECTED:CAR@";
char buffer[256];
int rv, tmp;

void setUp(void)
{
	for(int i = 0; i < 256; i++)
	{
		buffer[i] = 0;
	}
	rv = 0;
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

void message_Start_Test(void)
{
	rv = findStartOfMessage(ms);
	TEST_ASSERT_EQUAL(0, rv);
}

void message_End_Test(void)
{
	rv = findEndOfMessage(ms);
	TEST_ASSERT_EQUAL(14, rv);
}

int main (int argc, char * argv[])
{
    UnityBegin();
    setUp();
    MY_RUN_TEST(message_Start_Test);
    tearDown();
    setUp();
    MY_RUN_TEST(message_End_Test);
    tearDown();
    return UnityEnd();
}
