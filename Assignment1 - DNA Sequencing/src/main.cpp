#include "computeFile.h"
#include <ctime>
#include <cstdlib>

int main(int argc, char *argv[]){

	srand(time(NULL)); // seed for unique random number generator
	computeFile::checkArgs(argc, argv); // main function call to begin computations
	return 0;
}
