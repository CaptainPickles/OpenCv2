#include "Header.hpp"

using namespace std;
using namespace cv;


void showLog() {

    int keyPressed = waitKey(1);
    if (103 == keyPressed) {
        cout << "G! ";
    }

}

int closeApp() {
    if (waitKey(1) == 27)
        return 1;
    else
        return 0;
}