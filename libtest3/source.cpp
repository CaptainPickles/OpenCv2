#include "Header.hpp"
using namespace std;

void testAfficher(std::string s){
	cout << s;
}

ofstream createLog() {
	ofstream log("log.txt");
	log << "Creation du fichier log \n";
    log << localtime_s;
	return log;
}

void addToLog(std::string txt) {

}