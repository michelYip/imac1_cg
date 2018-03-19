#include <stdio.h>
#include <stdlib.h>
#include "../include/geometry.h"
#include "../include/colors.h"

int main(int argc, char ** argv){
	printPoint3D(pointPlusVector(pointXYZ(0,0,0),vectorXYZ(1,2,0)));
	printVector3D(addVectors(vectorXYZ(0.5,1.0,-2.0),vectorXYZ(0.2,-1.0,0)));
	printVector3D(subVectors(vectorXYZ(0.5,1.0,-2.0),vectorXYZ(0.2,-1.0,0)));
	return EXIT_SUCCESS;
}