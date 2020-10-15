#include "Header.hpp"
using namespace std;

void testAfficher(std::string s){
	cout << s;
}

ofstream createLog() {
	ofstream log("log.txt");

	time_t _tm = time(NULL);
	struct tm* curtime = localtime(&_tm);
	log << "Log of " << asctime(curtime);

	return log;
}

void addToLog(std::string txt) {

}