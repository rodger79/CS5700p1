//============================================================================
// Project Name:		Project1.cpp
// Build instructions:	g++ Project1.cpp -o project1
// Name: 				Rodger Byrd
// Function: 			Read in Machine files consecutively
//						Read in strings
//============================================================================

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const char* srcFileLocation = "/home/rodger/school/cs5700/pj1/src/PJ01_runfiles/";
const char* dstFileLocation = "/home/rodger/school/cs5700/pj1/src/outputfiles/";

int main() {

    //open input string file
	ifstream inputFile;
	inputFile.open(srcFileLocation + "input.txt");

	if (inputFile){
		cout << "file opened" << endl;
	}else{
		cout << "cannot open file" << endl;
	}

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
