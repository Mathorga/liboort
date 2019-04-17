#include "opencv2/opencv.hpp"

using namespace cv;

int main(int argc, char const *argv[]) {
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
        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty()) {
            break;
        }

        // Crop the frame.
        Rect rectCrop(20, 0, 140, 120);
        frame = frame(rectCrop);

        // Resize the frame.
        resize(frame, frame, Size(50, 50));

        // Display the resulting frame
        imshow("Frame", frame);

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
