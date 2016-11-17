#include "RP6ControlLib.h"
#include "RP6I2CslaveTWI.h"

#define slaveAddress 12

int main(void)
{
	initRP6Control(); 	
	I2CTWI_initSlave(slaveAddress);

	uint8_t sideHit = 0;
	uint8_t timesPressed2 = 0;
	uint8_t timesPressed3 = 0;
	uint8_t timesPressed5 = 0;
	
	DDRC &= ~IO_PC2; 
	PORTC &= ~IO_PC2;

	DDRC &= ~IO_PC3; 
	PORTC &= ~IO_PC3; 

	DDRC &= ~IO_PC5; 
	PORTC &= ~IO_PC5;

	if(PINC & IO_PC2) 
		writeString_P("\n\nPC2 is HIGH!\n\n");
	else
		writeString_P("\n\nPC2 is LOW!\n\n");

	if(PINC & IO_PC3) 
		writeString_P("\n\nPC3 is HIGH!\n\n");
	else
		writeString_P("\n\nPC3 is LOW!\n\n");

	if(PINC & IO_PC5) 
		writeString_P("\n\nPC5 is HIGH!\n\n");
	else
		writeString_P("\n\nPC5 is LOW!\n\n");

	int lastButton2State = false;
	int lastButton3State = false;
	int lastButton5State = false;

	startStopwatch1();

	while(true)
	{
		if(getStopwatch1() > 50)
		{
			if((PINC & IO_PC2) !=  lastButton2State)
			{
				if(PINC & IO_PC2)
				{
					sideHit = 2;
					timesPressed2++;
					writeString("Button 2 pressed ");
					writeInteger(timesPressed2, DEC);
					writeString(" times.");
					writeString("\n");
				}
			}	

			lastButton2State = PINC & IO_PC2;


			if((PINC & IO_PC3) !=  lastButton3State)
			{
				if(PINC & IO_PC3)
				{
					sideHit = 3;
					timesPressed3++;
					writeString("Button 3 pressed ");
					writeInteger(timesPressed3, DEC);
					writeString(" times.");
					writeString("\n");
				}
			}	

			lastButton3State = PINC & IO_PC3;


			if((PINC & IO_PC5) !=  lastButton5State)
			{
				if(PINC & IO_PC5)
				{
					sideHit = 5;
					timesPressed5++;
					writeString("Button 5 pressed ");
					writeInteger(timesPressed5, DEC);
					writeString(" times.");
					writeString("\n");
				}
			}	

			lastButton5State = PINC & IO_PC5;

			setStopwatch1(0);
		}
	}	
}