#include "Header.hpp"
using namespace std;
#pragma warning(disable : 4996)

float moy = 0;
float avg = 0;
float testredondance = -1;
float peopleSeen = 0;
float mostPeopleView = 0;

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
    if (testredondance != nbr) {
        moy += 1;
        avg += nbr;
        testredondance = nbr;
        peopleSeen += nbr;
        if (nbr > mostPeopleView)
            mostPeopleView = nbr;
    }
    else
    {
        peopleSeen += nbr;
    }
}

string average(string dateBegin) {
    string x = "d";
    if (avg == 0) {
        x = "pas de probleme juste flememe";
    }
    else {
        time_t _tm = time(NULL);
        struct tm* curtime = localtime(&_tm);
        string dateEnd = asctime(curtime);
        dateEnd = asctime(curtime);

        x = "average : " + to_string(avg / moy) + " maximun face at a time : " + to_string(mostPeopleView) + " face detected : " + to_string(peopleSeen) + " between " + dateBegin + " and " + dateEnd;
    }
    return x;
}