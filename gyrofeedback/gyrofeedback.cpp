#include <stdio.h>
#include <thread>
#include <chrono>
#include <iostream>

#include "utils.h"
#include "ev3dev.h"

using namespace ev3dev;
using namespace std;

int main(){
	large_motor _motor(OUTPUT_A);
	gyro_sensor _gyro(INPUT_1);
	
	_motor.set_duty_cycle_sp(10);
	_gyro.rate_and_angle();
	

	while(true){
		int angle = _gyro.angle();
		
		cout<<angle<<endl;
		
		float setpoint = 0;
		_motor.set_position_sp(setpoint-angle).run_to_rel_pos();

		//std::this_thread::sleep_for(std::chrono::milliseconds(500	));    	
	}

	
	return 0;
}