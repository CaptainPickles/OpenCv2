#include "Header.hpp"
using namespace std;
#pragma warning(disable : 4996)


ofstream createLog() {
    ofstream log("log.txt");
    time_t _tm = time(NULL);
    struct tm* curtime = localtime(&_tm);
    log << "Create log file from : " << asctime(curtime) << "\n";

    return log;
}

void addToLog(ofstream& log)// , int nbr) 
{
    std::cout << "ergerdgfrf";
}