#include <unistd.h>


void sleep(int seconds){
	usleep(seconds * 1000000);
}
