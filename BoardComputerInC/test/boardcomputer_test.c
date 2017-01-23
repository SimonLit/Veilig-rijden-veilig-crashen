#include "../libs/datastruct/datastruct.h"
#include "../libs/message/message.h"
#include "../libs/file_handeling/file_handeling.h"
#include <string.h>
#include <unistd.h>
#include "unity.h"

#define MY_RUN_TEST(func) RUN_TEST(func, 0)

#define outputFilePath "testWriteFile.bin"
#define fileWithDataStructs "testFileRead.bin"

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
	if(access(outputFilePath, F_OK) == 0)
	{
		remove(outputFilePath);
	}
	if(access(fileWithDataStructs, F_OK) == 0)
	{
		remove(fileWithDataStructs);
	}
	DATAPACKET test;
	DATAPACKET test1;
	test.sockFd = 22556688;
	test1.sockFd = 1122334455;
	writeDataStructToFile(fileWithDataStructs, &test);
	writeDataStructToFile(fileWithDataStructs, &test1);
}

void tearDown(void)
{
	for(int i = 0; i < 256; i++)
	{
		buffer[i] = 0;
	}    
	rv = 0;
	tmp = 0;
	if(access(outputFilePath, F_OK) == 0)
	{
		remove(outputFilePath);
	}
	if(access(fileWithDataStructs, F_OK) == 0)
	{
		remove(fileWithDataStructs);
	}
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

void message_Data_Split_Test(void)
{
	char ** ar = NULL;
	char arrry[] = "DAT|SPEED:0|SIDE_HIT:1|IMPACT:0|DIST_DRIVEN:0|ORIENTATION_YPR:-11,5,-1";
	rv = split(arrry, '|', &ar);
	for(int i = 0; i < rv; i++)
		printf("DEBUG %s\n", ar[i]);
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

void make_Send_Message_Test(void)
{
	DATAPACKET p;
	int lenght;
	strcpy(p.messageReceived, "BLA"); 
	makeMessageToSend(p.messageReceived, &p, &lenght);
	TEST_ASSERT_EQUAL(5, lenght);
	TEST_ASSERT_EQUAL_STRING("#BLA@", p.infoSend);
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

void write_Data_To_File_Test(void)
{
	DATAPACKET data;
	data.sockFd = 215202;
	rv = writeDataStructToFile(outputFilePath, &data);
	TEST_ASSERT_EQUAL(0, rv);
	DATAPACKET temp;
	FILE* fp = fopen(outputFilePath, "r");
	rv = fread(&temp, sizeof(DATAPACKET), 1, fp);
	fclose(fp);
	TEST_ASSERT_EQUAL(1, rv);
	TEST_ASSERT_EQUAL(215202, temp.sockFd);
}	

void read_All_Data_From_File_Test(void)
{
	DATAPACKET arrayTest[5];
	rv = readAllDataFromFile(fileWithDataStructs, arrayTest, 2);
	TEST_ASSERT_EQUAL(22556688 ,arrayTest[0].sockFd);
	TEST_ASSERT_EQUAL(1122334455 ,arrayTest[1].sockFd);
}

void read_Datapacket_On_Position_Test(void)
{
	DATAPACKET d;
	rv = readDataStructFromFile(fileWithDataStructs, &d, 0);
	TEST_ASSERT_EQUAL(0, rv);
	TEST_ASSERT_EQUAL(22556688 ,d.sockFd);
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
    MY_RUN_TEST(message_Data_Split_Test);
    tearDown();
    setUp();
    MY_RUN_TEST(check_Sender_Test);
    tearDown();
    setUp();
    MY_RUN_TEST(make_Send_Message_Test);
    tearDown();
    setUp();
    MY_RUN_TEST(verification_Test);
    tearDown();
    setUp();
    MY_RUN_TEST(write_Data_To_File_Test);
    tearDown();
    setUp();
    MY_RUN_TEST(read_All_Data_From_File_Test);
    tearDown();
    setUp();
    MY_RUN_TEST(read_Datapacket_On_Position_Test);
    tearDown();
    return UnityEnd();
}

