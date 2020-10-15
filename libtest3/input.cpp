#include "Header.hpp"

using namespace std;
using namespace cv;


void showLog() {

    int keyPressed = waitKey(10);
    if (103 == keyPressed) {
        cout << "G! ";
    }

}

int closeApp() {
    if (waitKey(10) == 27)
        return 1;
    else
        return 0;
}