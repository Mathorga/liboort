#include "opencv2/opencv.hpp"
#include "utils.h"

using namespace cv;

int main(int argc, char const *argv[]) {
    double startTime = 0;
    double endTime = 0;
    double execTime = 0;
    VideoCapture cap(0);
    cap.set(CAP_PROP_FRAME_WIDTH, 160);
    cap.set(CAP_PROP_FRAME_HEIGHT, 120);

    // Check if VideoCapture opened successfully.
    if (!cap.isOpened()) {
        printf("Error opening video stream or file\n");
        return -1;
    }

    while (true) {
        Mat frame;

        startTime = getTime();

        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty()) {
            break;
        }

        // Crop the frame.
        // Rect rectCrop(20, 0, 140, 120);
        // frame = frame(rectCrop);

        // Turn frame to grayscale.
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        // Resize the frame.
        resize(frame, frame, Size(24, 18));

        // printf("A pixel of the frame: %d - %d - %d\n", frame.at<Vec3b>(10, 10).val[0], frame.at<Vec3b>(10, 10).val[1], frame.at<Vec3b>(10, 10).val[2]);

        // Display the resulting frame
        imshow("Frame", frame);

        endTime = getTime();
        execTime = endTime - startTime;
        printf("Time: %f s\n", execTime);

        // Press  ESC on keyboard to exit
        char c = (char) waitKey(25);
        if (c == 27) {
            break;
        }
    }
    // When everything done, release the video capture object.
    cap.release();

    // Closes all the frames.
    destroyAllWindows();

    return 0;
}
