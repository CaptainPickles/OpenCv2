#pragma once
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <string>

std::ofstream createLog();
void addToLog(std::ofstream& log, int nbr);// , int nbr);

int closeApp();
void showLog();

std::string average(std::string dateBegin);
