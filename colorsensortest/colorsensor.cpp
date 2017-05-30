#include "ev3dev.h"

#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <string>


using namespace ev3dev;
using namespace std;

vector<string> COLOR_NAMES = {"No color","Black","Blue","Green","Yellow","Red","White","Brown"};

string getColorName(int value){
	if(value < 0 || value >= COLOR_NAMES.size()){
		return "Unknown color";
	}
	
	return COLOR_NAMES[value];
}


void sleep(int seconds){
	usleep(seconds * 1000000);
}


int main() {
	color_sensor cs(INPUT_3);
	while (!button::enter.pressed()) {
		int colorValue = cs.color();
		if(colorValue != 0){
			string color = getColorName(colorValue);

			sound::speak(color);
	    	sleep(2);
		}
	}
	
	sound::speak("I am done!");

	printf("Done\n");
	sleep(2);
	return 0;
}


