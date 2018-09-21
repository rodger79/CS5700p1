//============================================================================
// Project Name:		Project1.cpp
// Build instructions:	g++ -std=c++11 Project1.cpp -o project1
// Name: 				Rodger Byrd
// Function: 			Read in Machine files consecutively
//						Read in strings
//						update...
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

using namespace std;

//absolute directory locations
const string inputLocation = 	"/home/rodger/school/CS5700/pj1/src/PJ01_runfiles/input.txt";
const string mdfLocation = 		"/home/rodger/school/CS5700/pj1/src/PJ01_runfiles/";
const string logFileLocation = 	"/home/rodger/school/CS5700/pj1/src/outputfiles/";

struct transition{
	int start;
	string character;
	int end;
};

int main() {
	
	//define vector to hold test strings
	vector <string> testStringsList;
	testStringsList.clear();
	
	//define vector to hold accept states
	vector <int> acceptList;
	acceptList.clear();
	
	//define vector to hold accept states
	vector <transition> transitionList;
	transitionList.clear();
	
	//open input string file
	ifstream inputFile(inputLocation.c_str());

	//test inputfile opens correctly
	if (inputFile){
		cout << "input file opened" << endl;
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
	
	//close inputfile
	inputFile.close();
	
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
	
	//open Machine Description Files loop
	int mdfCount = 0;
	bool mdfValid = true; 
	cout<<"test1"<<"\n";
	while (true){
		cout<<"test2"<<"\n";
		string filename = "";
		string logfile = "";
		string fileNum = to_string(mdfCount);
		
		//clunky conversion to two digit filename
		if (mdfCount < 10){
			filename = mdfLocation + "m0" + fileNum + ".fa";
			logfile = logFileLocation + "m0" + fileNum + ".log";
		}
		else{
			filename = mdfLocation + "m" + fileNum + ".fa";
			logfile = logFileLocation + "m" + fileNum + ".log";
		}
		
		//create log file
		ofstream log(logfile.c_str());
		
		//log file test
		//cout << "log: " + logfile + " test" << endl;
		//log << "Test of log. \n";
		
	    //open current machine description file
		ifstream mdfFile(filename.c_str());
		
		//If valid open MDF 
		cout<<"test3"<<"\n";
		if (mdfFile){   									
			cout<<"test4"<<"\n";
			//cout << "mdf: " + filename + " opened" << endl;
			//Load MDF into memory
			cout << "mdf test: " + filename + " opened" << endl;
			int i = 0;
			string temp;
			//while(!mdfFile.eof()){
			
			while(mdfFile >> temp){
				
				//cout << temp  << endl;
				
				//convert accept list string to char array for tokenizing
				int n = temp.length();
				char tempCharAr[n+1];
				strcpy(tempCharAr, temp.c_str());
				
				//read in accept States to acceptList
				if (i == 0){
					char* nums;
					nums = strtok(tempCharAr,"{,}");
					while (nums != NULL){
						acceptList.push_back(atoi(nums));
						//printf ("%s\n",nums);
						nums = strtok (NULL, "{,}");
					}

				}
				//read in transitions
				else{
					
					//error here- uninitialized causing seg fault?
					char* nums;
					nums = strtok(tempCharAr,",");
					//char* tranStates[2]; 					
					int j = 0;
					while (nums != NULL){
						//printf ("%s\n",nums);
						//tranStates[j] = nums;
						nums = strtok (NULL, ",");
						j++;
					}
					/*
					transition tempTransition;
					tempTransition.start = atoi(tranStates[0]);
					tempTransition.character = tranStates[1];
					tempTransition.end = atoi(tranStates[2]);
					//cout<<"Add transition\n" ;
					transitionList.push_back(tempTransition);
					*/
				}
				i++;
				
			}
			/*
			//test accept list
			cout << "accept list"  << "\n";
			if (acceptList.empty()){
				cout << "accept list empty"  << "\n";		
			} else{
				for (int i = 0; i < acceptList.size(); i++){
						cout << acceptList[i] << "\n";
				}
			}	
			*/
			
			/*
			//test transition list
			cout << "transition list: start, char, end"  << "\n";
			if (acceptList.empty()){
				cout << "transition list empty"  << "\n";		
			} else{
				//cout << "transition list size: "  << transitionList.size() << "\n";		
				for (int k = 0; k < transitionList.size(); k++){
						cout << transitionList[k].start << " ";
						cout << transitionList[k].character << " ";
						cout << transitionList[k].end << " ";
						cout << "\n";
				}
				
			}
			 */
		
			//loop through test strings and test in current machine
			/*
			for (int i = 0; i < testStringsList.size(); i++){
				string currentString = testStringsList[i];

			}*/
			
			//close MDF & logfile & clear acceptlist
			log.close();
			mdfFile.close();
			acceptList.clear();
			transitionList.clear();
		
		}  
		else {
			break;
			//mdfValid = false;
		}

		cout << "test5"  << "\n";	

		//prevent infinite loop
		if (mdfCount == 2){ 
			//break;
			//mdfValid = false;
		}
		mdfCount++;
		cout << "test6"  << "\n";
	}
	
	return 0;
}

