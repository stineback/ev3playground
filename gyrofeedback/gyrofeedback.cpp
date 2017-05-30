#include <time.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>

#include "utils.h"
#include "ev3dev.h"

using namespace ev3dev;
using namespace std;
using namespace std::chrono;

float dutyCycle = 40;

float setpoint = 0;
float kp = 0.16;
float ki = 1;
float kd = 1.3;

bool drawGraph = false;
int graphRange = 100;

large_motor _motor(OUTPUT_A);
gyro_sensor _gyro(INPUT_1);



void parseArguments(int argc, char* argv[]){
	for(int i = 1; i<argc; ++i){
		string arg(argv[i]);
		
		if(arg.length() >= 3){
			string prefix = arg.substr(0,2);
			string postfix = arg.substr(2,arg.length()-2);
			
			if(prefix == "-P"){
				kp = stof(postfix);
			}else if(prefix == "-I"){
				ki = stof(postfix);
			}else if(prefix == "-D"){
				kd = stof(postfix);
			}else if(prefix == "-S"){
				setpoint = stof(postfix);
			}else if(prefix == "-C"){
				dutyCycle = stof(postfix);
			}else if(prefix == "-G"){
				drawGraph = true;
				graphRange = stoi(postfix);
			}
		}
	}
	cerr << "kp=" << kp << ", ki=" << ki << ", kd=" << kd << ", setpoint=" << setpoint << ", dutyCycle=" << dutyCycle<<endl << ", drawGraph=" << (drawGraph ? "YES" : "NO") << endl;
}

void setup(){
	_motor.set_duty_cycle_sp(dutyCycle);
	_gyro.rate_and_angle();
}

float error(float angle){
	return setpoint-angle;
}

float derivedError(float prevError, float error, float time){
	return (error-prevError)/time;
}

float controlVariable(float error, float derivedError){
	return kp*error + kd*derivedError;
}

void plotGraph(int value){
	// draw value-axis
	static bool first = true;
	if(first){
		first = false;
		
		string axis(graphRange*2 + 1, '-');
		axis[axis.size()-1] = '>';
		axis[graphRange + 1] = '+';
		cout << axis << endl;
	}


	string line(graphRange*2 + 1, '.');
	
	// Plot axis
	line[graphRange + 1] = '|';
	
	// Plot value
	int plotValue = graphRange + value + 1;
	plotValue = max(0, min(graphRange*2 + 1, plotValue));
	
	line[plotValue] = 'x'; 
	
	cout << line << endl;
}

void controlLoop(){
	int angle = _gyro.angle();
	
	float e = error(angle);
	float prevE = e;
	
//	time_t t = time(NULL); //get current time
//	time_t prevT = t;
	
	milliseconds t = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
	milliseconds prevT = t;
	milliseconds zeroT = t;
	while(true){
		angle = _gyro.angle();
		
		prevE = e;
		e = error(angle);
		
		prevT = t;
		t = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
		int diffT = duration_cast<milliseconds>(t-prevT).count();
		float deltaT = max(1,diffT);
		
		float dE = derivedError(prevE, e, deltaT);
		
		float u = controlVariable(e, dE);

		int duration = duration_cast<milliseconds>(t-zeroT).count();
		if(drawGraph){
			plotGraph(e);
		}else{
			cerr << "angle=" << angle << ", deltaT=" << deltaT << ", controlVariable=" << u << endl;
			cout << duration << "," << e << endl;
		}

		_motor.set_position_sp(u).run_to_rel_pos();
	}
}



int main(int argc, char* argv[]){

	parseArguments(argc, argv);

	setup();
	
	controlLoop();
	
	return 0;
}

