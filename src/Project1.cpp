//============================================================================
// Project Name:		Project1.cpp
// Build instructions:	g++ -std=c++11 Project1.cpp -o project1
// Name: 				Rodger Byrd
// Function: 			Read in Machine files consecutively
//						Read in strings
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>


using namespace std;

//const char* inputLocation = "/home/rodger/school/CS5700/pj1/src/PJ01_runfiles/input.txt";
const string inputLocation = "/home/rodger/school/CS5700/pj1/src/PJ01_runfiles/input.txt";
const string mdfLocation = "/home/rodger/school/CS5700/pj1/src/PJ01_runfiles/";
const string dstFileLocation = "/home/rodger/school/cs5700/pj1/src/outputfiles/";

int main() {
	
	//define vector to hold test strings
	vector <string> testStringsList;
	testStringsList.clear();
	
    //open input string file
	ifstream inputFile(inputLocation.c_str());

	
	//test inputfile opens correctly
	if (inputFile){
		cout << "file opened" << endl;
	}else{
		cout << "cannot open file" << endl;
		throw exception();
	}
	
	//read inputfile
	string temp;
	while(!inputFile.eof()){
		inputFile>>temp; 
		testStringsList.push_back(temp);
	}
	
	//read out input strings
	for (int i = 0; i < testStringsList.size(); i++){
		//output test strings for debugging
		//cout << testStringsList[i] << "\n";
		//check to make sure no strings are reduced by char limit - 256 chars
		if (testStringsList[i].size() >= 255)
		{
			cout << "size limit warning" << "\n";
		}
	}
	
	//open Machine Description Files
	int mdfCount = 0;
	bool mdfValid = true;
	while (mdfValid){
		string filename = "";
		string fileNum = to_string(mdfCount);
		if (mdfCount < 10){
			filename = mdfLocation + "m0" + fileNum + ".fa";
		}
		else{
			filename = mdfLocation + "m" + fileNum + ".fa";
		}
		cout << filename << "\n";
		
	    //open input string file
		//ifstream inputFile();
		
		//If valid open MDF and create logfile
		if (true){
			
		} 
		//no more mdfs exist break loop
		else {
			mdfValid = false;
			
		}
		
		//prevent infinite loop
		if (mdfCount == 99){ mdfValid = false;}
		mdfCount++;
	}
	
	
	return 0;
}

