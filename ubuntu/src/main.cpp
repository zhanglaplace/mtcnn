#include "mtcnn.h"

#define landmark_n 68



/******************************************************
// 函数名:testCamera
// 说明:摄像头接口
// 作者:张峰
// 时间:
// 备注:
/*******************************************************/
void testCamera(){
	VideoCapture cap(0);
    if(!cap.isOpened()){
        cout<<"opencv Camera failed.\n";
        return ;
    }
    Mat image;
	MTCNN detector("../model");
	float factor = 0.709f;
	float threshold[3] = { 0.7f, 0.6f, 0.6f };
	int minSize = 40;
	double t = (double)cv::getTickCount();
	while(true){
		cap >> image;
		vector<FaceInfo> faceInfo = detector.Detect(image, minSize, threshold, factor, 3);
		for (int i = 0; i < faceInfo.size(); i++){
			int x = (int)faceInfo[i].bbox.xmin;
			int y = (int)faceInfo[i].bbox.ymin;
			int w = (int)(faceInfo[i].bbox.xmax - faceInfo[i].bbox.xmin + 1);
			int h = (int)(faceInfo[i].bbox.ymax - faceInfo[i].bbox.ymin + 1);
			cv::rectangle(image, cv::Rect(x, y, w, h), cv::Scalar(255, 0, 0), 2);
		}
		for (int i = 0; i < faceInfo.size(); i++){
			float *landmark = faceInfo[i].landmark;
			for (int j = 0; j < 5; j++){
				cv::circle(image, cv::Point((int)landmark[2 * j], (int)landmark[2 * j + 1]), 2, cv::Scalar(255, 255, 0), 2);
			}
		}
     
		cv::imshow("image", image);
		cv::waitKey(1);
	}
  // std::cout <<" time," << (double)(cv::getTickCount() - t) / cv::getTickFrequency() << "s"<<std::endl;
	
}

/******************************************************
// 函数名:testImage
// 说明:单个图像接口
// 作者:张峰
// 时间:
// 备注:
/*******************************************************/
void testImage(const string imgname){
	
	MTCNN detector("../model");
	float factor = 0.709f;
	float threshold[3] = { 0.7f, 0.6f, 0.6f };
	int minSize = 40;
	Mat image = imread(imgname);
	double t = (double)cv::getTickCount();
	
		
	vector<FaceInfo> faceInfo = detector.Detect(image, minSize, threshold, factor, 3);
	
	for (int i = 0; i < faceInfo.size(); i++){
		int x = (int)faceInfo[i].bbox.xmin;
		int y = (int)faceInfo[i].bbox.ymin;
		int w = (int)(faceInfo[i].bbox.xmax - faceInfo[i].bbox.xmin + 1);
		int h = (int)(faceInfo[i].bbox.ymax - faceInfo[i].bbox.ymin + 1);
		cv::rectangle(image, cv::Rect(x, y, w, h), cv::Scalar(255, 0, 0), 2);
	}
	for (int i = 0; i < faceInfo.size(); i++){
		float *landmark = faceInfo[i].landmark;
		for (int j = 0; j < 5; j++){
			cv::circle(image, cv::Point((int)landmark[2 * j], (int)landmark[2 * j + 1]), 2, cv::Scalar(255, 255, 0), 2);
		}
	}   
	cv::imshow("image", image);
	cv::waitKey(0);
}

/******************************************************
// 函数名:testImageList
// 说明:文件列表的接口
// 作者:张峰
// 时间:
// 备注:
/*******************************************************/
void testImageList(const string imageListname){
	ifstream fin(imageListname.c_str(),ios_base::in);
	MTCNN detector("../model");
	float factor = 0.709f;
	float threshold[3] = { 0.7f, 0.6f, 0.6f };
	int minSize = 40;
   // int count = 0;
	string imgName;
	Mat image;
	double t = (double)cv::getTickCount();
	while(getline(fin,imgName)){
		image = imread(imgName);
		vector<FaceInfo> faceInfo = detector.Detect(image, minSize, threshold, factor, 3);
		for (int i = 0; i < faceInfo.size(); i++){
			int x = (int)faceInfo[i].bbox.xmin;
			int y = (int)faceInfo[i].bbox.ymin;
			int w = (int)(faceInfo[i].bbox.xmax - faceInfo[i].bbox.xmin + 1);
			int h = (int)(faceInfo[i].bbox.ymax - faceInfo[i].bbox.ymin + 1);
			cv::rectangle(image, cv::Rect(x, y, w, h), cv::Scalar(255, 0, 0), 2);
		}
		for (int i = 0; i < faceInfo.size(); i++){
			float *landmark = faceInfo[i].landmark;
			for (int j = 0; j < 5; j++){
				cv::circle(image, cv::Point((int)landmark[2 * j], (int)landmark[2 * j + 1]), 2, cv::Scalar(255, 255, 0), 2);
			}
		}
		cv::imshow("image", image);
		cv::waitKey(60);
	}
	fin.close();
}

/******************************************************
// 函数名:testVideo
// 说明:视频接口，需要提供视频
// 作者:张峰
// 时间:
// 备注:
/*******************************************************/
void testVideo(const string videoname){
	VideoCapture cap(videoname);
    if(!cap.isOpened()){
        cout<<"opencv Camera failed.\n";
        return ;
    }
    Mat image;
	MTCNN detector("../model");
	float factor = 0.709f;
	float threshold[3] = { 0.7f, 0.6f, 0.6f };
	int minSize = 40;
   // int count = 0;
	double t = (double)cv::getTickCount();
	while(true){
        cap >> image;
        if(image.empty())
            break;
		vector<FaceInfo> faceInfo = detector.Detect(image, minSize, threshold, factor, 3);
		for (int i = 0; i < faceInfo.size(); i++){
			int x = (int)faceInfo[i].bbox.xmin;
			int y = (int)faceInfo[i].bbox.ymin;
			int w = (int)(faceInfo[i].bbox.xmax - faceInfo[i].bbox.xmin + 1);
			int h = (int)(faceInfo[i].bbox.ymax - faceInfo[i].bbox.ymin + 1);
			cv::rectangle(image, cv::Rect(x, y, w, h), cv::Scalar(255, 0, 0), 2);
		}
		for (int i = 0; i < faceInfo.size(); i++){
			float *landmark = faceInfo[i].landmark;
			for (int j = 0; j < 5; j++){
				cv::circle(image, cv::Point((int)landmark[2 * j], (int)landmark[2 * j + 1]), 2, cv::Scalar(255, 255, 0), 2);
			}
		}
		cv::imshow("image", image);
		cv::waitKey(1);
	}
  // std::cout <<" time," << (double)(cv::getTickCount() - t) / cv::getTickFrequency() << "s"<<std::endl;
	
}


cv::Rect getBBox(Mat& img,vector<FaceInfo>& faceInfo,vector<cv::Point2d>&pts){
	vector<Rect> rects;
	if (faceInfo.size() == 0) return Rect(-1, -1, -1, -1);
	double center_x, center_y, x_min, x_max, y_min, y_max;
	center_x = center_y = 0;
	x_min = x_max = pts[0].x;
	y_min = y_max = pts[0].y;
	for (int i = 0; i < landmark_n; i++) {
		center_x += pts[i].x;
		center_y += pts[i].y;
		x_min = min(x_min, pts[i].x);
		x_max = max(x_max, pts[i].x);
		y_min = min(y_min, pts[i].y);
		y_max = max(y_max, pts[i].y);
	}
	center_x /= landmark_n;
	center_y /= landmark_n;

	for (int i = 0; i < faceInfo.size(); i++) {
		int x = (int)faceInfo[i].bbox.xmin;
		int y = (int)faceInfo[i].bbox.ymin;
		int w = (int)(faceInfo[i].bbox.xmax - faceInfo[i].bbox.xmin + 1);
		int h = (int)(faceInfo[i].bbox.ymax - faceInfo[i].bbox.ymin + 1);
		Rect r = Rect(x, y, w,h); // 人脸检测的框

		//shape超出了目标 或者对人脸问题
		if (x_max - x_min > r.width*1.5) continue; 
		if (y_max - y_min > r.height*1.5) continue;
		if (abs(center_x - (r.x + r.width / 2)) > r.width / 2) continue;
		if (abs(center_y - (r.y + r.height / 2)) > r.height / 2) continue;
		return r; // 一个pts只对应一个人脸
	}
	return Rect(-1, -1, -1, -1);
}


/******************************************************
// 函数名:getpts
// 说明:解析pts文件
// 作者:张峰
// 时间:
// 备注:
/*******************************************************/
void getpts(const string ptsName,vector<cv::Point2d>& gt_shape){
	char line[256];
	FILE *tmp = fopen(ptsName.c_str(), "r");// 打开点文件
	assert(tmp);
	fgets(line, sizeof(line), tmp); //version:1
	fgets(line, sizeof(line), tmp); // n_points:68
	fgets(line, sizeof(line), tmp); //{
	for (int i = 0; i < landmark_n; i++) {
		fscanf(tmp, "%lf", &gt_shape[i].x);
		fscanf(tmp, "%lf", &gt_shape[i].y);
	}
	fclose(tmp);
}


/******************************************************
// 函数名:准备特征点预测的接口
// 说明:特征点检测的样本准备
// 作者:张峰
// 时间:
// 备注:imagename图像list和pts点list
/*******************************************************/
void pairlandmark(const string imagename,const string ptsname){
	ifstream fim(imagename.c_str(),ios_base::in); // 图像列表 
	ifstream fpt(ptsname.c_str(),ios_base::in); // pts列表
	ofstream fou("rect_pts.txt",ios_base::out); // 最终保存的crop_file和pts相对值

	const string root = "/home/zf/deeplearning/caffe/face_examples/facial_landmark/face-landmark-localization/"; 

	//人脸检测
	MTCNN detector("../model");
	int minSize = 15;
	float factor = 0.709f;
	float threshold[3] = { 0.7f, 0.6f, 0.6f };

	int count = 0,N = 0;
	string imgName,ptsName,pts;
	Mat image;
	while(getline(fim,imgName)){ // 读取当前图像名字
        getline(fpt,ptsName); //  读取当前点文件文件名
        //cout<<imgName<<"\t"<<ptsName<<endl;
        vector<cv::Point2d>pts(landmark_n,cv::Point2d(0.0,0.0));
	    getpts(root + ptsName,pts);
		image = imread(root + imgName);
		vector<FaceInfo> faceInfo = detector.Detect(image, minSize, threshold, factor, 3);
        Rect bbox = getBBox(image,faceInfo,pts);
		if (bbox.x != -1){ //找到了人脸
			N++;
			fou << imgName << " " << bbox.x << " " << bbox.y << " " << bbox.width << " " << bbox.height << " ";
			for (int i = 0; i < landmark_n; ++i){
				fou << pts[i].x << " " << pts[i].y << " ";
			}
			fou << endl;
		}
        if(N % 500 == 0)
            cout<<"processing images:"<<N<<endl;
    }
    cout<<"total face:"<<N<<endl;
	fou.close();
}




int main(int argc, char **argv)
{
	cout<<"method : mtcnn 0 (camera) ,1 (video) ,2 imageList ,3 image, 4 landmarkPts\n";
	cout<<"method 1 2 3 4 must get the filname\n";
	if(argc < 2){
		cout<<"input error\n";
		return -1;
	}
	char method = argv[1][0];
	switch(method){
		case '0':testCamera();break;
		case '1':testVideo(argv[2]);break;
		case '2':testImageList(argv[2]);break;
		case '3':testImage(argv[2]);break;
		case '4':pairlandmark(argv[2],argv[3]);break;
		default:
			break;
	}

	 
	return 1;
}
