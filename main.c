
#include <lpc214x.h>


void setupPLL0(void);
void feedSeq(void);
void connectPLL0(void);


#define PLOCK 0x400 //10th bit = 1
		
int main(void)
{
	setupPLL0();
	feedSeq(); //sequence for locking PLL to desired freq.
	connectPLL0();
	feedSeq(); //sequence for connecting the PLL as system clock

	//SysClock is now ticking @ 60Mhz!
	   
	VPBDIV = 0x01; // PCLK is same as CCLK i.e 60Mhz

	while(1);

	//return 0;
	}

void setupPLL0(void)
{
	PLL0CON = 0x01; // PPLE=1 & PPLC=0 so it will be enabled 
					// but not connected after FEED sequence
	PLL0CFG = 0x24; // set the multipler to 5 (i.e actually 4) 
					// i.e 12x5 = 60 Mhz (M - 1 = 4)!!!
					// Set P=2 since we want FCCO in range!!!
					// So , Assign PSEL =01 in PLL0CFG as per the table.
}

void feedSeq(void)
{
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
}

void connectPLL0(void)
{
	// check whether PLL has locked on to the  desired freq by reading the lock bit
	// in the PPL0STAT register

	while( !( PLL0STAT & PLOCK ));

	// now enable(again) and connect
	PLL0CON = 0x03;
} 