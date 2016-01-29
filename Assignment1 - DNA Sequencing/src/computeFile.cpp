#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include "computeFile.h"

using namespace std;

string line; // declaration of all variables to be used in the program
int totalChars = 0;
int totalBigrams = 0;
int numLines = 0;
float mean = 0.0;
int charsInLine = 0;
int varDiff = 0;
int varSquared = 0;
float variance = 0.0;
float stdDeviation = 0.0;
int repeatCount = 0;

int aCount = 0;
int tCount = 0;
int cCount = 0;
int gCount = 0;

float aProb = 0.0;
float tProb = 0.0;
float cProb = 0.0;
float gProb = 0.0;

int aaCount = 0;
int atCount = 0;
int acCount = 0;
int agCount = 0;

int taCount = 0;
int ttCount = 0;
int tcCount = 0;
int tgCount = 0;

int caCount = 0;
int ctCount = 0;
int ccCount = 0;
int cgCount = 0;

int gaCount = 0;
int gtCount = 0;
int gcCount = 0;
int ggCount = 0;

float a = 0.0;
float b = 0.0;
float C = 0.0;
float D = 0.0;

int tempRand = 0;
float myD;

ifstream ifs; // input and output file streams created
ofstream ofs;

int computeFile::checkArgs(int m_argc, char *m_argv[]){ // grabs user cmd arg and opens the file
	if (m_argc == 2){
		char *sampleDNA = m_argv[1];
		ifs.open(sampleDNA);
		computeFile::functionCaller();
	}else if (m_argc < 2){
		cout << "No file name entered. Exiting..." << endl;
	}else if (m_argc > 2){
		cout << "Too many parameters entered. Exiting..." << endl;
	}else{
		cout << "Unknown error. Exiting..." << endl;
	}
	return 0;
}

int computeFile::functionCaller(){ // calls all computational, print, and run-again functions
	
	computeFile::setSum();
	computeFile::setMean();

	ifs.clear();
	ifs.seekg(0, ios::beg); // set file back to the beginning for next iteration
	
	computeFile::collectData();
	
	computeFile::setVariance();
	computeFile::setStdDeviation();
	computeFile::setTotalBigrams();
	
	computeFile::outputData();
	
	computeFile::thousandStrings();
	
	computeFile::runAgainCheck();
	
	return 0;
}

void computeFile::setSum(){ // grab sum of all characters in the file
	if (ifs.is_open()){
		while (getline(ifs, line)){
			totalChars += line.size();
			numLines++;
		}
	}
}

void computeFile::setMean(){ // grabs average line length in the file
	mean = (float)totalChars/numLines;
}

void computeFile::collectData(){ // count all individual characters and bigrams
	if (ifs.is_open()){
		while(getline(ifs, line)){ // iterate through lines
			for(int i = 0; i < line.size(); ++i){ // iterate through chars in line
				line[i] = toupper(line[i]); // convert all chars to uppercase
				if (line[i] == 'A'){
					aCount++;
					if (line[i+1] == 'A'){ // bigram handler
						aaCount++;
					}else if (line[i+1] == 'T'){
						atCount++;
					}else if (line[i+1] == 'C'){
						acCount++;
					}else if (line[i+1] == 'G'){
						agCount++;
					}
				}else if (line[i] == 'T'){
					tCount++;
					if (line[i+1] == 'A'){
						taCount++;
					}else if (line[i+1] == 'T'){
						ttCount++;
					}else if (line[i+1] == 'C'){
						tcCount++;
					}else if (line[i+1] == 'G'){
						tgCount++;
					}
				}else if (line[i] == 'C'){
					cCount++;
					if (line[i+1] == 'A'){
						caCount++;
					}else if (line[i+1] == 'T'){
						ctCount++;
					}else if (line[i+1] == 'C'){
						ccCount++;
					}else if (line[i+1] == 'G'){
						cgCount++;
					}
				}else if (line[i] == 'G'){
					gCount++;
					if (line[i+1] == 'A'){
						gaCount++;
					}else if (line[i+1] == 'T'){
						gtCount++;
					}else if (line[i+1] == 'C'){
						gcCount++;
					}else if (line[i+1] == 'G'){
						ggCount++;
					}
				}else{ // if there is anything except A, T, C, or G, exit
					cout << "Invalid characters in file. Exiting..." << endl;
					exit(1);
				}
			}
		}
		varSquared += pow((line.size() - mean), 2.0);
		ifs.close();
	}
}

void computeFile::setVariance(){
	variance = varSquared / numLines;
}

void computeFile::setStdDeviation(){
	stdDeviation = sqrt(variance);
}

void computeFile::setTotalBigrams(){ // total # of bigrams in line are 1 less than total # of chars
	totalBigrams = totalChars-numLines;
}

void computeFile::outputData(){ // output all computations to another file
	ofs.open("AustinThiel.out", ofstream::out | ofstream::app); // open, or create, and append
	
	if(ofs.is_open()){
		if (repeatCount == 0){
		ofs << "Student Name: Austin Thiel" << endl;
		ofs << "Student ID#: 1780959" << endl;
		ofs << "File Name: " << "AustinThiel.out" << "\n" << endl;
		repeatCount++;
		}
		
		ofs << "Sum: " << totalChars << endl;
		ofs << "Mean: " << mean << endl;
		ofs << "Variance: " << variance << endl;
		ofs << "Standard Deviation: " << stdDeviation << "\n" << endl;
		
		aProb = ((float)aCount/totalChars)*100; // set probability vars for gaussian use
		tProb = ((float)tCount/totalChars)*100;
		cProb = ((float)cCount/totalChars)*100;
		gProb = ((float)gCount/totalChars)*100;
		
		ofs << "Probability of A: " << aProb << "%" << endl;
		ofs << "Probability of T: " << tProb << "%" << endl;
		ofs << "Probability of C: " << cProb << "%" << endl;
		ofs << "Probability of G: " << gProb << "%\n" << endl;
		
		ofs << "Probability of AA " << ((float)aaCount/totalBigrams)*100 << "%" << endl;
		ofs << "Probability of AT " << ((float)atCount/totalBigrams)*100 << "%" << endl;
		ofs << "Probability of AC " << ((float)acCount/totalBigrams)*100 << "%" << endl;
		ofs << "Probability of AG " << ((float)agCount/totalBigrams)*100 << "%\n" << endl;
		
		ofs << "Probability of TA " << ((float)taCount/totalBigrams)*100 << "%" << endl;
		ofs << "Probability of TT " << ((float)ttCount/totalBigrams)*100 << "%" << endl;
		ofs << "Probability of TC " << ((float)tcCount/totalBigrams)*100 << "%" << endl;
		ofs << "Probability of TG " << ((float)tgCount/totalBigrams)*100 << "%\n" << endl;
		
		ofs << "Probability of CA " << ((float)caCount/totalBigrams)*100 << "%" << endl;
		ofs << "Probability of CT " << ((float)atCount/totalBigrams)*100 << "%" << endl;
		ofs << "Probability of CC " << ((float)ccCount/totalBigrams)*100 << "%" << endl;
		ofs << "Probability of CG " << ((float)cgCount/totalBigrams)*100 << "%\n" << endl;
		
		ofs << "Probability of GA " << ((float)gaCount/totalBigrams)*100 << "%" << endl;
		ofs << "Probability of GT " << ((float)gtCount/totalBigrams)*100 << "%" << endl;
		ofs << "Probability of GC " << ((float)gcCount/totalBigrams)*100 << "%" << endl;
		ofs << "Probability of GG " << ((float)ggCount/totalBigrams)*100 << "%\n" << endl;
	}
}

float computeFile::computeD(){ // get the length of a string via gaussian distribution formula
	a = rand() / (RAND_MAX + 1.0);
	b = rand() / (RAND_MAX + 1.0);
	C = (sqrt(-2*(log(a)))) * cos(2*M_PI*b);
	D = (stdDeviation * C) + mean;
	return D;
}

void computeFile::thousandStrings(){ // print 1000 DNA sequences according to computed probabilities

	string tempStr = "";
	
	if(ofs.is_open()){
		for(int tempLines = 0; tempLines <= 1000; tempLines++){
			tempStr = "";
			myD = computeD(); // grab a new line length
			while(tempStr.length() <= myD){ // generate the line 
				tempRand = rand() % 100 + 1; // game of chance generator
				if (tempRand > 0 && tempRand < aProb){ // if its between 0 and the probability of A being generated (in a perfect world, around 25%)
					tempStr.append("A");
				}else if (tempRand > aProb && tempRand < aProb + tProb){ // if its between 0 and ~50%, etc
					tempStr.append("T");
				}else if (tempRand > aProb + tProb && tempRand < aProb + tProb + cProb){
					tempStr.append("C");
				}else if (tempRand > aProb + tProb + cProb && tempRand <= 100){
					tempStr.append("G");
				}
			}ofs << tempStr << endl; // print the string to the file
		}
		ofs << endl; // file formatting
		ofs << "================================================================" << endl;
		ofs << endl;
	}ofs.close();
	
}

void computeFile::runAgainCheck(){ // prompt the user to run again or exit
	ifs.close();
	cout << "Generate another list? (y/n): ";
	string userInput;
	cin >> userInput;
	
	if (userInput == "y"){
		aCount = 0; // zero out all the "count" variables for re-use
		tCount = 0;
		cCount = 0;
		gCount = 0;
		aaCount = 0;
		atCount = 0;
		acCount = 0;
		agCount = 0;
		taCount = 0;
		ttCount = 0;
		tcCount = 0;
		tgCount = 0;
		caCount = 0;
		ctCount = 0;
		ccCount = 0;
		cgCount = 0;
		gaCount = 0;
		gtCount = 0;
		gcCount = 0;
		ggCount = 0;
		totalChars = 0;
		varSquared = 0;
		mean = 0;
		numLines = 0;
		
		
		cout << "File Name: "; // grab new DNA sequence file to compute
		string userFile;
		cin >> userFile;
		ifs.open(userFile.c_str()); // open new file
		computeFile::functionCaller(); // start the process over again at functionCaller() with the new file
	}else if (userInput == "n"){
		cout << "Program Success. Exiting..." << endl;
		exit(1);
	
	}else{
		cout << "Invalid input. Exiting..." << endl;
	}
	 
}
