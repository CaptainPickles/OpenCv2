#include "Header.hpp"
using namespace std;
using namespace cv;
#pragma warning(disable : 4996)
void detectAndDisplay(Mat frame, ofstream& logFile);
CascadeClassifier face_cascade;
int main(int argc, const char** argv)
{
    CommandLineParser parser(argc, argv,
        "{help h||}"
        "{face_cascade|data/haarcascades/haarcascade_frontalface_alt.xml|Path to face cascade.}"
        "{camera|0|Camera device number.}");
    parser.about("\nThis program demonstrates using the cv::CascadeClassifier class to detect objects (Face + eyes) in a video stream.\n"
        "You can use Haar or LBP features.\n\n");
    parser.printMessage();
    String face_cascade_name = samples::findFile(parser.get<String>("face_cascade"));
    //-- 1. Load the cascades
    if (!face_cascade.load(face_cascade_name))
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };
    int camera_device = parser.get<int>("camera");
    VideoCapture capture(0);
    //-- 2. Read the video stream
    capture.open(camera_device);
    //create log file
    std::ofstream logFile = createLog();

    string dateBegin = "e";
    string dateEnd = "e";
    time_t _tm = time(NULL);
    struct tm* curtime = localtime(&_tm);
    dateBegin = asctime(curtime);

    if (!capture.isOpened())
    {
        cout << "--(!)Error opening video capture\n";
        return -1;
    }
    Mat frame;
    while (capture.read(frame))
    {
        if (frame.empty())
        {
            cout << "--(!) No captured frame -- Break!\n";
            break;
        }
        //-- 3. Apply the classifier to the frame
        detectAndDisplay(frame, logFile);
        if (closeApp() == 1)
            break;
    }

    logFile << average(dateBegin);
    logFile.close();

    return 0;
}
void detectAndDisplay(Mat frame, ofstream& log)
{
    Mat frame_gray;
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);
    //-- Detect faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale(frame_gray, faces, 1.3);
    std::string nbrFaces = "";
    nbrFaces = returnFaceToString(faces.size());

    addToLog(log, faces.size());// , faces.size() );
    putText(frame, nbrFaces, cv::Point(200, 450),
        FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 0, 0), 2, 8);
    for (size_t i = 0; i < faces.size(); i++)
    {
        Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
        Mat faceROI = frame_gray(faces[i]);
    }
    //-- Show what you got
    imshow("Capture - Face detection", frame);
}