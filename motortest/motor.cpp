#include "ev3dev.h"

#include <stdio.h>
#include <unistd.h>

using namespace ev3dev;


large_motor  left(OUTPUT_B);
large_motor  right(OUTPUT_C);
	
void drive(int speed, int t) {

	right.set_duty_cycle_sp(speed);
	left.set_duty_cycle_sp(speed);
		
	right.run_forever();
	left.run_forever();

	printf("Start\n");

	usleep(t);
	
	printf("Stop\n");
}

int main() {

	drive(50, 100000);
	
	printf("Done\n");
	usleep(2000);
	return 0;
}


