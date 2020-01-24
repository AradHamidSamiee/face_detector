#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	//loading cascade
	CascadeClassifier face_cascade, eye_cascade;
	if (!face_cascade.load("haarcascade_frontalface_default.xml")) {
		cout << "unable to load face cascade xml" << endl;
		return 1;
	}
	if (!eye_cascade.load("haarcascade_eye.xml")) {
		cout << "unable to load eye cascade xml" << endl;
		return 1;
	}

	//checking if camera works or nah (._ .)
	VideoCapture videocapture(0);
	if (!videocapture.isOpened()) {
		cout << "Oops.. seems like camera needs to get a life" << endl;
		return 1;
	}

	Mat videocaptue_image, gray_image;
	String window_title = "face_detection";
	vector<Rect> eye, face;
	namedWindow(window_title, CV_WINDOW_FREERATIO);
	while (waitKey(33) != 27)
	{
		//get one frame
		videocapture >> videocaptue_image;
		//convert frame into a grayscale format
		cvtColor(videocaptue_image, gray_image, CV_RGB2GRAY);
		//
		equalizeHist(gray_image, gray_image);

		face_cascade.detectMultiScale(gray_image, face, 1.1, 3, 0, cvSize(0, 0), cvSize(300, 300));
		if (face.size()) {
			putText(videocaptue_image, "a Face is detected", Point(20, 40), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(51, 71, 91), 2, CV_AA, false);
		}

		for (int i = 0; i < face.size(); i++) {
			Point p1(face[i].x, face[i].y);
			Point p2(face[i].x + face[i].width, face[i].y + face[i].height);
			rectangle(videocaptue_image, p1, p2, CV_RGB(255, 40, 50), 2, 8, 0);

			Mat eye_image = gray_image(face[i]);
			eye_cascade.detectMultiScale(eye_image, eye, 1.1, 3, 0, cvSize(0, 0), cvSize(50, 50));
			for (int j = 0; j < eye.size(); j++) {
				Point p3(face[i].x + eye[j].x, face[i].y + eye[j].y);
				Point p4(face[i].x + eye[j].x + eye[j].width, face[i].y + eye[j].y + eye[j].height);
				rectangle(videocaptue_image, p3, p4, CV_RGB(40, 255, 50), 2, 8, 0);
			}
		}
		imshow(window_title, videocaptue_image);
	}
	return 0;
}
