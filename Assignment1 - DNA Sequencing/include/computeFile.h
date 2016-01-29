#ifndef COMPUTEFILE_H // header guard to prevent multiple declarations
#define COMPUTEFILE_H

class computeFile{

public: // declare all used functions in computeFile.cpp
	static int checkArgs(int m_argc, char *argv[]);
	static int functionCaller();
	static void setSum();
	static void setMean();
	static void collectData();
	static void setVariance();
	static void setStdDeviation();
	static void setTotalBigrams();
	static void outputData();
	static float computeD();
	static void thousandStrings();
	static void runAgainCheck();
};

#endif
