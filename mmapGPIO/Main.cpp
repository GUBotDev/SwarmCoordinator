#include "mmapGpio.h"
#include "stdio.h"

int main(void){
    unsigned int val = 10;
    mmapGpio rpiGpio; // instantiate an instance of the mmapGpio class
    rpiGpio.setPinDir(4,mmapGpio::OUTPUT); // set GPIO4 to output

    while(true){
	    rpiGpio.writePinHigh(4); // write GPIO4 pin high
	    usleep(500000);
	    rpiGpio.writePinLow(4); // write GPIO4 pin low
	    usleep(500000);
    }

	return 0;
}