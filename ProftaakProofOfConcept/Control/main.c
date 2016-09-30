#include "RP6ControlLib.h"
#include "RP6I2CslaveTWI.h"

#define slaveAddress 12

int main(void)
{
	initRP6Control(); 	
	I2CTWI_initSlave(slaveAddress);

	uint8_t sideHit = 0;
	uint8_t timesPressed2 = 0;
	
	DDRC &= ~IO_PC3; 
	PORTC &= ~IO_PC3; 

	if(PINC & IO_PC3) // Check if PC6 is high
		writeString_P("\n\nPC3 is HIGH!\n\n");
	else
		writeString_P("\n\nPC3 is LOW!\n\n");

	int lastButton3State = false;

	while(true)
	{
		if((PINC & IO_PC3) !=  lastButton3State)
		{
			if(PINC & IO_PC3)
			{
				sideHit = 2;
				timesPressed2++;
				writeString("Button 2 pressed ");
				writeInteger(timesPressed2, DEC);
				writeString(" times.");
				writeString("\n");
			}
		}	

		lastButton3State = PINC & IO_PC3;
	}	
}