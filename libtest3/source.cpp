#include "Header.hpp"
using namespace std;

void testAfficher(std::string s){
	cout << s;
}

ofstream createLog() {
	ofstream log("log.txt");


	log << "Creation du fichier log \n";
	return log;
}

void addToLog(ofstream log ,int nbr) {

}