#include "register.h"
#include "mtcnn.h"
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace cv;

MTCNN detector("../model");
float factor = 0.709f;
float thresholds[3] = { 0.7f, 0.6f, 0.6f };
int minSize = 40;


int video(){

	// ´ò¿ªÉãÏñÍ·
	VideoCapture cap(0);
	if (!cap.isOpened()){
		cout << "Open camera failed\n";
		return -1;
	}
	Mat frame;
	int frame_count = 0, fps = 10;
	std::chrono::time_point<std::chrono::system_clock> p1, p0 = std::chrono::system_clock::now();
	for (;;){
		
		cap >> frame;
		if (frame.empty()){
			cout << "get frame error \n";
			return -1;
		}
		vector<FaceInfo> faceInfo = detector.Detect(frame, minSize, thresholds, factor, 3);
		if (faceInfo.size() == 0)
			continue;
		for (int i = 0; i < faceInfo.size(); ++i){
			int x = (int)faceInfo[i].bbox.xmin;
			int y = (int)faceInfo[i].bbox.ymin;
			int w = (int)(faceInfo[i].bbox.xmax - faceInfo[i].bbox.xmin);
			int h = (int)(faceInfo[i].bbox.ymax - faceInfo[i].bbox.ymin);
			rectangle(frame, Rect(x, y, w, h), Scalar(0, 255, 0), 1);
		}
		frame_count++;
		if (frame_count % 10 == 0)
		{
			p1 = std::chrono::system_clock::now();
			fps = 10.0 / (float)std::chrono::duration_cast<std::chrono::microseconds>(p1 - p0).count();
			p0 = p1;
			frame_count = 0;
		}
		string fpsSt = "FPS:" + to_string(fps);
		cv::putText(frame, fpsSt.c_str(), cv::Point(10, 20), CV_FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(255, 0, 0), 1, CV_AA);
		imshow("landmark", frame);
		if ('q' == waitKey(1)){
			return -1;
		}
	}
	return 1;
}


int testImg(char* pImgName){

	std::chrono::time_point<std::chrono::system_clock> p0 = std::chrono::system_clock::now();
	Mat img = imread(pImgName);
	if (img.empty()){
		cout << "read img failed\n";
		return -1;
	}
	vector<FaceInfo> faceInfo = detector.Detect(img, minSize, thresholds, factor, 3);
	for (int i = 0; i < faceInfo.size(); ++i){
		int x = (int)faceInfo[i].bbox.xmin;
		int y = (int)faceInfo[i].bbox.ymin;
		int w = (int)(faceInfo[i].bbox.xmax - faceInfo[i].bbox.xmin);
		int h = (int)(faceInfo[i].bbox.ymax - faceInfo[i].bbox.ymin);
		rectangle(img, Rect(x, y, w, h), Scalar(0, 255, 0), 1);
	}
	std::chrono::time_point<std::chrono::system_clock> p1 = std::chrono::system_clock::now();
	cout << "detection time:" << (float)std::chrono::duration_cast<std::chrono::microseconds>(p1 - p0).count() / 1000 << "ms" << endl;
	imshow("landmark", img);
	waitKey(0);
	return 1;
}
int main(int argc,char** argv){
	if (argc < 2 ){
		cout << "input param error.\n";
		return -1;
	}
	if (!strcmp(argv[1], "image")){
		return testImg(argv[2]);
	}
	if (!strcmp(argv[1],"video")){
		return video();
	}
	else{
		cout << "input param error\n";
		return -1;
	}
	return 1;
}