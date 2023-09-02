#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    char wndname[] = "OpenCV Example";
    int width = 1024;
    int height = 768;

    Mat image = Mat::zeros(height, width, CV_8UC3);
    Size textsize = getTextSize("Hello OpenCV!", FONT_HERSHEY_COMPLEX, 3, 5, 0);
    Point org((width - textsize.width)/2, (height - textsize.height)/2);

    putText(image, "Hello OpenCV!", org, FONT_HERSHEY_COMPLEX, 3,
            Scalar(0, 0, 255), 5, LINE_AA);

    imshow(wndname, image);

    waitKey();
    return 0;
}
