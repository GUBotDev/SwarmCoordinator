#include "mmapGpio.h"
#include "stdio.h"

int main(void){
	unsigned int val = 10;
	mmapGpio rpiGpio;
	rpiGpio.setPinDir(0, mmapGpio::OUTPUT);
	rpiGpio.setPinDir(1, mmapGpio::OUTPUT);
	rpiGpio.setPinDir(2, mmapGpio::OUTPUT);
	rpiGpio.setPinDir(3, mmapGpio::OUTPUT);

	int step = 0;
	bool forward = true;

	while(true){

		switch (step){
			case 0:
				rpiGpio.writePinLow(0);
				rpiGpio.writePinLow(1);
				rpiGpio.writePinLow(2);
				rpiGpio.writePinHigh(3);
				break;
			case 1:
				rpiGpio.writePinLow(0);
				rpiGpio.writePinLow(1);
				rpiGpio.writePinHigh(2);
				rpiGpio.writePinHigh(3);
				break;
			case 2:
				rpiGpio.writePinLow(0);
				rpiGpio.writePinLow(1);
				rpiGpio.writePinHigh(2);
				rpiGpio.writePinLow(3);
				break;
			case 3:
				rpiGpio.writePinLow(0);
				rpiGpio.writePinHigh(1);
				rpiGpio.writePinHigh(2);
				rpiGpio.writePinLow(3);
				break;
			case 4:
				rpiGpio.writePinLow(0);
				rpiGpio.writePinHigh(1);
				rpiGpio.writePinLow(2);
				rpiGpio.writePinLow(3);
				break;
			case 5:
				rpiGpio.writePinHigh(0);
				rpiGpio.writePinHigh(1);
				rpiGpio.writePinLow(2);
				rpiGpio.writePinLow(3);
				break;
			case 6:
				rpiGpio.writePinHigh(0);
				rpiGpio.writePinLow(1);
				rpiGpio.writePinLow(2);
				rpiGpio.writePinLow(3);
				break;
			case 7:
				rpiGpio.writePinHigh(0);
				rpiGpio.writePinLow(1);
				rpiGpio.writePinLow(2);
				rpiGpio.writePinHigh(3);
				break;
		}

		if (forward){
			step++;
		}
		else{
			step--;
		}
		
		if (step > 7){
			step = 0;
		}
		else if (step < 0){
			step = 7;
		}

	}

	return 0;
}