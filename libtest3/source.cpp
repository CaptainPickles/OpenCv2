#include "Header.hpp"
using namespace std;
#pragma warning(disable : 4996)

float totalDetection = 0;
float sumNbr = 0;
float totalPeopleSeen = 0;
float mostPeopleView = 0;
float variance = 0;
float ecartType = 0;
float avg = 0;
float S2;

string date = "ef";

ofstream createLog() {
	ofstream log("log.txt");
	time_t _tm = time(NULL);
	struct tm* curtime = localtime(&_tm);
	date = asctime(curtime);
	log << "Create log file from : " << date << "\n" << endl;

	return log;
}

void addToLog(ofstream& log, int nbr)// , int nbr) 
{
	time_t _tm = time(NULL);
	struct tm* curtime = localtime(&_tm);
	log << "there is : " << nbr << " people on the cam at " << asctime(curtime);
	cout << "there is : " << nbr << " people on the cam at " << asctime(curtime);

	totalDetection += 1;
	sumNbr += nbr;
	totalPeopleSeen += nbr;
	if (nbr > mostPeopleView)
		mostPeopleView = nbr;
	avg = sumNbr / totalDetection;
	S2 = S2 + nbr * nbr;
	variance = S2 / totalDetection - avg * avg;
	ecartType = sqrt(variance);
}

string average(string dateBegin) {
	string x = "d";
	if (sumNbr == 0) {
		x = "pas de probleme juste flememe";
	}
	else {
		time_t _tm = time(NULL);
		struct tm* curtime = localtime(&_tm);
		string dateEnd = asctime(curtime);
		dateEnd = asctime(curtime);
		
		
		x = " average : " + to_string(avg) + " ecart type : " + to_string(ecartType) + " maximun face at a time : " + to_string(mostPeopleView) + " face detected : " + to_string(totalPeopleSeen) + " between " + dateBegin + " and " + dateEnd;
	}
	return x;
}