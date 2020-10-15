#include "Header.hpp"
using namespace std;
#pragma warning(disable : 4996);


ofstream createLog() {
	ofstream log("log.txt");
	time_t _tm = time(NULL);
	struct tm* curtime = localtime(&_tm);
	log << "Create log file from : " << asctime(curtime) << "\n";

	return log;
}

void addStringLog(ofstream log, string txt) {
	log << "Create log file from :  \n";
}

void addToLog(ofstream log ,int nbr) {
	time_t _tm = time(NULL);
	struct tm* curtime = localtime(&_tm);
	log << "there is : " << nbr << " people on the cam at " << asctime(curtime) << "\n";
}