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
	_motor.set_position_sp(0).run_to_abs_pos();
	while (!_motor.state().count("running"))
    	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	while (_motor.state().count("running"))
    	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	
	_motor.reset();
	_gyro.rate_and_angle();
	
	_motor.set_duty_cycle_sp(10);
	_motor.set_position_sp(90).run_to_rel_pos();
	while (!_motor.state().count("running"))
    	std::this_thread::sleep_for(std::chrono::milliseconds(10));
    	
	while (_motor.state().count("running")){
    	std::this_thread::sleep_for(std::chrono::milliseconds(1));
    	
    	int gAngle = _gyro.angle();
    	int mAngle = _motor.position();
    	
    	cout << "gyro angle=" << gAngle << ", motor angle=" << mAngle << endl;
	}

	return 0;
}