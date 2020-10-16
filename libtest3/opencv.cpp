#include "Header.hpp"
using namespace std;
using namespace cv;

void detectAndDisplay(Mat frame, ofstream& logFile);
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
int main(int argc, const char** argv)
{
    CommandLineParser parser(argc, argv,
        "{help h||}"
        "{face_cascade|data/haarcascades/haarcascade_frontalface_alt.xml|Path to face cascade.}"
        "{eyes_cascade|data/haarcascades/haarcascade_eye_tree_eyeglasses.xml|Path to eyes cascade.}"
        "{camera|0|Camera device number.}");
    parser.about("\nThis program demonstrates using the cv::CascadeClassifier class to detect objects (Face + eyes) in a video stream.\n"
        "You can use Haar or LBP features.\n\n");
    parser.printMessage();
    String face_cascade_name = samples::findFile(parser.get<String>("face_cascade"));
    String eyes_cascade_name = samples::findFile(parser.get<String>("eyes_cascade"));
    //-- 1. Load the cascades
    if (!face_cascade.load(face_cascade_name))
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };
    if (!eyes_cascade.load(eyes_cascade_name))
    {
        cout << "--(!)Error loading eyes cascade\n";
        return -1;
    };
    int camera_device = parser.get<int>("camera");
    VideoCapture capture(0);
    //-- 2. Read the video stream
    capture.set(CAP_PROP_FRAME_WIDTH, 1);
    capture.set(CAP_PROP_FRAME_HEIGHT, 1);
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
    face_cascade.detectMultiScale(frame_gray, faces, 1.2);
    std::string nbrFaces = std::to_string(faces.size());
    std::string pers = "personne";

    addToLog(log , faces.size());// , faces.size() );

    if (faces.size() > 1) {
        pers = "personnes";
    }
    else {
        pers = "personne";
    }

    std::string textFaces = "Il y a actuellement : " + nbrFaces + " " + pers;
    putText(frame, textFaces, cv::Point(200, 450),
        FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 0, 0), 2, 8);
    for (size_t i = 0; i < faces.size(); i++)
    {
        Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
        Mat faceROI = frame_gray(faces[i]);
        //-- In each face, detect eyes
        std::vector<Rect> eyes;
        eyes_cascade.detectMultiScale(faceROI, eyes, 1.2);
        if (eyes.size() >= 2) {
            putText(frame, "Les deux yeux sont ouverts !", cv::Point(30, 30),
                FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 0), 1, 8);
        }
        else if (eyes.size() == 1) {
            putText(frame, "1 oeil est ouvert !", cv::Point(30, 30),
                FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 0, 0), 1, 8);
        }
        else if (eyes.size() == NULL)
        {
            putText(frame, "Les yeux sont fermer !", cv::Point(30, 30),
                FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 0, 255), 1, 8);
        }
        for (size_t j = 0; j < eyes.size(); j++)
        {
            Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
            int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
            circle(frame, eye_center, radius, Scalar(255, 0, 0), 4);
        }
    }
    //-- Show what you got
    imshow("Capture - Face detection", frame);
}