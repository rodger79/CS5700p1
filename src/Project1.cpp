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
#include <vector>


using namespace std;

const char* srcFileLocation = "/home/rodger/school/CS5700/pj1/src/PJ01_runfiles/input.txt";

const char* dstFileLocation = "/home/rodger/school/cs5700/pj1/src/outputfiles/";

int main() {
	
	//define vector to hold test strings
	vector <string> testStringsList;
	testStringsList.clear();
	
    //open input string file
	ifstream inputFile(srcFileLocation);

	
	//test inputfile
	if (inputFile){
		cout << "file opened" << endl;
	}else{
		cout << "cannot open file" << endl;
		
	}
	
	string temp;
	//read inputfile
	while(!inputFile.eof()){
		inputFile>>temp; 
		testStringsList.push_back(temp);
	}
	
	//read out input strings
	for (int i = 0; i < testStringsList.size(); i++){
		cout << testStringsList[i] << "\n";
	}
	
	return 0;
}

