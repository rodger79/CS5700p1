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
#include <algorithm>

using namespace std;

//absolute directory locations
//const string inputLocation = 	"/home/rodger/school/CS5700/pj1/src/PJ01_runfiles/input.txt";
const string inputLocation = 	"/home/rodger/school/CS5700/pj1/src/PJ01_runfiles/inputtoy.txt";
const string mdfLocation = 		"/home/rodger/school/CS5700/pj1/src/PJ01_runfiles/";
const string outputFileLocation = 	"/home/rodger/school/CS5700/pj1/src/outputfiles1/";
const string logFileLocation = 	"/home/rodger/school/CS5700/pj1/src/logfiles1/";
const string asciiSymbols = " !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_abcdefghijklmnopqrstuvwxyz{|}~";

//data structure to hold transition
struct transition{
	int start;
	string character;
	int end;
};

//data structure to hold NFA branches
struct machineState{
	int state;
	string testString;
};

//remove duplicates from string
string remove_duplicates(std::string s) {
    if (s.begin() == s.end()) return s;
    auto no_duplicates = s.begin(); 
    for (auto current = no_duplicates; current != s.end();) {
        current = std::find_if(std::next(current), s.end(), [no_duplicates](const char c) { return c != *no_duplicates; });
        *++no_duplicates = std::move(*current);;
    }
    s.erase(++no_duplicates, s.end());
    return s;
}

//DFA accept test
bool accept_string(string curString, vector<int>& accList, vector<transition>& TransList){
	bool retval = false;
	//start state
	int state = 0;

	//step through string characters
	for (int i = 0; i < curString.size(); i++){
		
		//If in trap state end looking through string
		if(state == 255){break;}
	
		string s; s.push_back(curString[i]);
		for (int j = 0; j < TransList.size(); j++){
			if ((TransList[j].start == state) && (TransList[j].character == s)){
				
				//found matching state, go to next symbol
				state = TransList[j].end;
				break;
			}
		}
		
	}
	for (int j = 0; j < accList.size(); j++){
		if(accList[j] == state){
			retval = true;
		}
	}
	

	return retval;
} 
//NFA accept test
bool accept_stringNFA(string curString, vector<int>& accList, vector<transition>& TransList){
	

	
	bool retval = false;
	//start state
	int state = 0;
	vector <machineState> branchList;
	
	machineState mainBranch;
	mainBranch.state = state;
	mainBranch.testString = curString;
	
	branchList.push_back(mainBranch);
	
	string E; E.push_back('`');
	
	
	/*
	if (!branchList.empty()){
		cout<< "branchlist not empty\n";
	} else
	{
		cout<< "branchlist empty\n";
	}
	
	cout<< "erase branch.begin\n";
	branchList.erase(branchList.begin());
	
	if (!branchList.empty()){
		cout<< "branchlist not empty\n";
	} else
	{
		cout<< "branchlist empty\n";
	}
	branchList.push_back(mainBranch);
	branchList.erase(branchList.begin());
	if (!branchList.empty()){
		cout<< "branchlist not empty\n";
	} else
	{
		cout<< "branchlist empty\n";
	}
	*/
	
	while (!branchList.empty()){
		
		//clear out working state from branch list
		machineState m = branchList[0];
		branchList.erase(branchList.begin());
		cout<< "branchlist erase new size: " << branchList.size() << "\n";
		
		if (m.state == 255){
			//stop processing this string
			cout<< "dead state detected\n";
			break;
		}

		cout<< "string:  " << m.testString << "\n";
		//step through string characters
		for (int i = 0; i < m.testString.size(); i++){
			
			cout<< "current symbol: " << m.testString[i] << "\n";
		    int tranCount = 0; //if >0 spawn new branch
		    
		    int mainBranchState = m.state; //placeholder to hold new state until 
			//cout << "current state & testString\n" << m.state << " "<< m.testString[i] << "\n\n";
		    

			for (int j = 0; j < TransList.size(); j++){
				//cout << "current transition list char: " << TransList[j].character << "\n\n";
				//look for epsilon transitions

				//look for transitions matching current symbol
				string s; s.push_back(m.testString[i]);

				//first see if there is an Epsilon transiiton, if there is one, create branch
				//		with current test string
				if ((TransList[j].start == m.state) && (TransList[j].character == E)){
					cout<<"found parallel E branch, new state: "<<TransList[j].end << "\n";
					machineState newEBranch;
					newEBranch.state = TransList[j].end;
					newEBranch.testString = m.testString;
					branchList.push_back(newEBranch);
					
				//Next to check for defined transitions
				} else if ((TransList[j].start == m.state) && (TransList[j].character == s)){
					//cout<< "found transition match: ";
					if (tranCount == 0){
						//if transition count 0, main branch continue
						mainBranchState = TransList[j].end;
						cout<< "main branch new state: " << TransList[j].end << "\n";
						
					} else{
						//else transition count > 0 create fork
						cout<< "creating multiple path branch: "; 
						cout<< "new state: " << TransList[j].end << "\n";
						
						string branchString;
						for (int k = i + 1; k <  m.testString.size(); k++){
							branchString += m.testString[j];
						}
						machineState newBranch;
						newBranch.state = TransList[j].end;
						newBranch.testString = branchString;
						branchList.push_back(newBranch);

					}
					tranCount++;
				}
			}
			m.state= mainBranchState;
			
			//look for epsilon transitions from current state and create fork

			//cout<< "test string E: " << E << "\n";
//			for (int j = 0; j < TransList.size(); j++){
//				if ((TransList[j].start == m.state) && (TransList[j].character == E)){
//					cout<< "E branch new state: " << TransList[j].end << "\n";
//
//					//string branchString= m.testString;
//					string branchString;
//					for (int k = i + 1; k <  m.testString.size(); k++){
//						branchString += m.testString[j];
//					}
//					machineState newEBranch;
//					newEBranch.state = TransList[j].end;
//					newEBranch.testString = branchString;
//					branchList.push_back(newEBranch);
//				}
//			}

			
		}
		
		//if string is empty still need to look for epsilon transition
		if (m.testString.size() == 0)
		{
			//cout<< "teststring empty, no loop, last check for epsilon\n";
			for (int j = 0; j < TransList.size(); j++){
				if ((TransList[j].start == m.state) && (TransList[j].character == E)){
				cout<< "E after string, new state: " << TransList[j].end << "\n";
					//string branchString= m.testString;
					string branchString = "";
					machineState newEBranch;
					newEBranch.state = TransList[j].end;
					newEBranch.testString = branchString;
					branchList.push_back(newEBranch);
				}
			}
		}
		

		
		for (int j = 0; j < accList.size(); j++){
			if(accList[j] == m.state){
				retval = true;
			}
		}
		
	}
	
	return retval;
}

int main() {
	
	//open Machine Description Files loop
	int mdfCount = 6;
	
	//define vector to hold test strings
	vector <string> testStringsList;
	testStringsList.clear();
	
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
	while(inputFile>>temp){
		testStringsList.push_back(temp);
	}

	//close inputfile
	inputFile.close();
	
	//read out input strings
	for (int i = 0; i < testStringsList.size(); i++){
		
		//check to make sure no strings are reduced by char limit - 256 chars
		if (testStringsList[i].size() >= 255)
		{
			cout << "size limit warning" << "\n";
		}
	}
	//output test strings for debugging
	cout << "teststrings size: "<< testStringsList.size() << "\n";

	//cout<<"test1"<<"\n";
	while (true){
		//define vector to hold accept states
		vector <int> acceptList;
		acceptList.clear();
		
		//define vector to hold all transitions
		vector <transition> transitionList;
		transitionList.clear();
		
		//create transition list for explicit definitions
		vector <transition> explicitTransitionList;
		explicitTransitionList.clear();
		
		//cout<<"test2"<<"\n";
		string filename = "";
		string logfile = "";
		string outfile = "";
		string fileNum = to_string(mdfCount);
		
		//clunky conversion to two digit filename
		if (mdfCount < 10){
			filename = mdfLocation + "m0" + fileNum + ".fa";
			logfile = logFileLocation + "m0" + fileNum + ".log";
			outfile = outputFileLocation + "m0" + fileNum + ".txt";
		}
		else{
			filename = mdfLocation + "m" + fileNum + ".fa";
			logfile = logFileLocation + "m" + fileNum + ".log";
			outfile = outputFileLocation + "m" + fileNum + ".txt";
		}
		
		//create log file
		ofstream log(logfile.c_str());
		
		//create output file
		ofstream output(outfile.c_str());
		
	    //open current machine description file
		ifstream mdfFile(filename.c_str());
		
		//If valid open MDF 
		if (mdfFile){   									

			//Load MDF into memory
			cout << "mdf test: " + filename + " opened" << endl;
			int i = 0;
			string temp;
			
			while(mdfFile >> temp){
				
				
				//convert accept list string to char array for tokenizing
				int n = temp.length();
				char tempCharAr[n+1];
				strcpy(tempCharAr, temp.c_str());
				
				//read in accept States to acceptList
				if (i == 0){
					char* nums;
					nums = strtok(tempCharAr,"{}");
					while (nums != NULL){
						acceptList.push_back(atoi(nums));
						//printf ("%s\n",nums);
						nums = strtok (NULL, "{}");
					}

				}
				//read in transitions
				else{
					
					//error here- uninitialized causing seg fault?
					char* nums;
					nums = strtok(tempCharAr,",");
					char tranStates[2]; 					
					int j = 0;
					while (nums != NULL){
						//printf ("%s\n",nums);
						tranStates[j] = *nums;
						//cout<<nums<< "\n";
						nums = strtok (NULL, ",");
						j++;
					}
					
					transition tempTransition;
					
					char tempStart[2]= {tranStates[0], '\0'};
					tempTransition.start = atoi(tempStart);
					
					tempTransition.character = tranStates[1];
					
					char tempEnd[2]= {tranStates[2], '\0'};
					tempTransition.end = atoi(tempEnd);
					
					//cout<<"Add transition.start: " <<tempTransition.start <<"\n" ;
					transitionList.push_back(tempTransition);
					explicitTransitionList.push_back(tempTransition);
				}
				i++;
				
			}

			//determine if machine is DFA/NFA/INVALID
			//look for epsilon transitions
			bool hasEpsilon = false;
			string epsilon = "`";
			for (int i = 0; i < transitionList.size(); i++){
				if (transitionList[i].character == epsilon){
					//cout<< "hasEpsilon" << "\n";
					hasEpsilon = true;
					//cout<< "has E trans" << "\n";
				}
			}
			//else look for multiple transitions rules for same state/symbol
			bool hasMatch = false;
			for (int i = 0; i < explicitTransitionList.size(); i++){
				string currentSymbol;
				int currentState;
				currentSymbol = explicitTransitionList[i].character;
				currentState = explicitTransitionList[i].start;
				//look for repeats of state/symbol combination
				int count = 0;
				for (int j = 0; j < explicitTransitionList.size(); j++){
					if ((explicitTransitionList[j].character == currentSymbol) 
							&& (explicitTransitionList[j].start == currentState)){
						count++;
						
					}
				}
				//if count > 1 multiple staty/symbols identified
				if (count > 1){
					//cout<< "symbol/state repeat" << "\n";
					hasMatch = true;
				}
			}
			

			bool NFA = false;
			//if Epsilon or matching symbol/stated identified NFA
			if (hasEpsilon || hasMatch){
				log << "Valid: NFA" << "\n";
				cout << "NFA\n";
				NFA = true;
			}else{
				log << "Valid: DFA" << "\n";
			}
			//else invalid, tokenizer should handle missing tokens
			
			//identify machine alphabet
			string Alphabet;
			for (int i = 0; i < transitionList.size(); i++){
				if (transitionList[i].character == "`"){
					//don't add epsilon character to alphabet
				}else{
					Alphabet += transitionList[i].character;
				}
					
				
			}

			sort(Alphabet.begin(), Alphabet.end());
			string finalAlphabet = remove_duplicates(Alphabet);
		
			//cout<< finalAlphabet<< "\n";
			log << "Alphabet: " << finalAlphabet.c_str() <<  "\n";
			
			/*
			//test explicit transition list
			cout << "exp transition list: start, char, end"  << "\n";
			for (int k = 0; k < explicitTransitionList.size(); k++){
					cout << explicitTransitionList[k].start << " ";
					cout << explicitTransitionList[k].character << " ";
					cout << explicitTransitionList[k].end << " ";
					cout << "\n";
			}
			
			//test transition list
			cout << "full transition list: start, char, end"  << "\n";
			for (int k = 0; k < transitionList.size(); k++){
					cout << transitionList[k].start << " ";
					cout << transitionList[k].character << " ";
					cout << transitionList[k].end << " ";
					cout << "\n";
			}
			//test transition list
			cout << "transition list: start, char, end"  << "\n";
			if (acceptList.empty()){
				cout << "transition list empty"  << "\n";		
			} else{
				//cout << "transition list size: "  << transitionList.size() << "\n";		
				for (int k = 0; k < transitionList.size(); k++){
					
					if (transitionList[k].start == 1 && transitionList[k].character == "1"){
						cout << transitionList[k].start << " ";
						cout << transitionList[k].character << " ";
						cout << transitionList[k].end << " ";
						cout << "\n";
					}
				}
				
			}
			//test transition list
			cout << "test of specific mapping list: start, char, end"  << "\n";
			if (acceptList.empty()){
				cout << "transition list empty"  << "\n";		
			} else{
				//cout << "transition list size: "  << transitionList.size() << "\n";		
				for (int k = 0; k < transitionList.size(); k++){
					
					if (transitionList[k].start == 1 && transitionList[k].character == "1"){
						cout << transitionList[k].start << " ";
						cout << transitionList[k].character << " ";
						cout << transitionList[k].end << " ";
						cout << "\n";
					}
				}
				
			}*/

			//loop through all states and add traps for anything not in language
			for (int i=0; i< 256; i++){
				for (int j = 0; j < asciiSymbols.length(); j++){
					transition trapTransition;
					trapTransition.start = i;
					trapTransition.character = asciiSymbols[j];
					trapTransition.end = 255;
					
					bool addFlag = true;
					//check here to see if explicitly defined already
					// 		then don't add 
					for (int k = 0; k < explicitTransitionList.size(); k++){

						if ((explicitTransitionList[k].start == trapTransition.start) &&
								(explicitTransitionList[k].character == trapTransition.character)){
							//already explicitly defined so don't add
							addFlag = false;
						}else{
							//not explicitly defined, map to trap state
							
						}
					}
					if (addFlag){
						transitionList.push_back(trapTransition);
					}
				}
			}
			
			//print size
			cout << "Transition list size: " <<  transitionList.size() << " ";
			cout << "Exp list size: " <<  explicitTransitionList.size() << "\n";

			/* error, need all symbols remove this section
			 *
			 * remove current alphabet from asciiSymbols
			 * create transitions from delta list to state 255 for 
			 * every symbol
			 * asciiSymbols
			 */
			
			/*
			string trapSymbols;
			//cout << asciiSymbols<< "\n";
			//cout << trapSymbols<< "\n";
			

			//build list of trap symbols not in alphabet
			for (int j = 0; j < asciiSymbols.length(); j++){
				bool add = true;
				for (int i = 0; i < finalAlphabet.length(); i++){
					if (asciiSymbols[j]==finalAlphabet[i]){
						//don't add
						add = false;
					}
				}
			
				if (add) {trapSymbols+=asciiSymbols[j];} 	            //temporarily remove for testing
			}
	
*/

				
			int acceptedStringCount = 0;
			//loop through test strings and test in current machine
			for (int i = 0; i < testStringsList.size(); i++){
				string currentString = testStringsList[i];
				bool stringPasses;
				cout<<"string index: " <<i<< "\n\n\n";
				
				if (NFA){
					//ignore NFA for now
					stringPasses = accept_stringNFA(currentString, acceptList,transitionList);
					
					
				} 
				else{
					//DFA: should be able to remove once NFA function working
					stringPasses = accept_string(currentString, acceptList,transitionList);
				
				}
				
				if (stringPasses){
					//cout<<"accept string: "<< currentString << "\n";
					acceptedStringCount++;
					output<<currentString<< "\n";
				} else{
					//cout<<"fail string: "<< currentString << "\n";
				}
			}
			
			//add number of accepted
			log<< "Accepted Strings: "<< acceptedStringCount << " / " << testStringsList.size() < "\n";
			log<<"\n";
			//close MDF & logfile & clear acceptlist
			output.close();
			log.close();
			mdfFile.close();
			acceptList.clear();
			transitionList.clear();
		
			
			//clear lists for next machine
			transitionList.clear();
			explicitTransitionList.clear();
			acceptList.clear();
		}  
		else {
			break;
		}

		//prevent infinite loop
		if (mdfCount ==6){ 
			break;
		}
		mdfCount++;
		acceptList.clear();
		
	}
	
	return 0;
}

