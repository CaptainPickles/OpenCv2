#include "Header.hpp"
using namespace std;
#pragma warning(disable : 4996)


ofstream createLog() {
    ofstream log("log.txt");
    time_t _tm = time(NULL);
    struct tm* curtime = localtime(&_tm);
    log << "Create log file from : " << asctime(curtime) << "\n" << endl;;

    return log;
}

void addToLog(ofstream& log , int nbr )// , int nbr) 
{
    time_t _tm = time(NULL);
    struct tm* curtime = localtime(&_tm);
    log << "there is : " << nbr << " people on the cam at " << asctime(curtime);
    cout << "there is : " << nbr << " people on the cam at " << asctime(curtime);
}