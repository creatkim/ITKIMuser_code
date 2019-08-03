#include <opencv2\opencv.hpp>
#include <iostream>
#include <math.h>
#include "CharacterRecognition.h"
#include <windows.h>
using namespace cv;
using namespace std;
void Process(cv::Mat& src, cv::Mat& dst, cv::Scalar& s,float dis);


/****************************************************
/*		开发环境：vs2015 
/*		库	   : OpenCV3 或者 OpenCV4
/*		函数名  :FindName
/*		参数:	
		src			- 输入图像矩阵
/*		rects		- 传出图像中 所有目标坐标（左上角），以及目标的长宽，用std::vector存储
/*		s			- 选择目标的基准颜色(0BGR)  名字的颜色(220, 85, 210)，血条颜色是(255, 125, 245)
/*		dis			- 与目标颜色 相近距离  默认 50
/*		max_ratio	- 目标长宽比例的最大值  默认长比宽 10
/*		min_ratio	- 目标长宽比例的最小值  默认长比宽 5
/**/
void FindName(cv::Mat& src, vector<Rect>& rects,cv::Scalar& s,float dis=50,float max_ratio=10,float min_ratio=5);


int main()
{
	LARGE_INTEGER freq;
	LARGE_INTEGER start_t, stop_t;
	double exe_time=0.0;
	QueryPerformanceFrequency(&freq);
	Scalar cla(220, 85, 210);
	for (int t = 1; t < 10; t++)
	{
		string path = format("%d.bmp",t);
		Mat src = imread(path);
		if (src.empty())
			continue;
		Mat yt = src.clone();
		vector<Rect> rects;						//名字坐标
		vector<Rect> rects_b;					//血条坐标
		QueryPerformanceCounter(&start_t);		//计时
		FindName(src, rects, cla,50,10,5);		//找到名称坐标
		FindName(src, rects_b, Scalar(255, 125, 245) , 50, 10, 3);	//找到血条坐标
		QueryPerformanceCounter(&stop_t);		//结束
		exe_time = 1e3*(stop_t.QuadPart - start_t.QuadPart) / freq.QuadPart;  //计算时间
		for (int i = 0; i < rects.size(); i++)
		{	//对找到名称画矩形
			rectangle(yt, rects[i], Scalar(0, 0, 255), 1);
			std::string spoint = format("x:%d,y:%d", rects[i].x, rects[i].y);
			putText(yt, spoint, Point(rects[i].x+rects[i].width+10, rects[i].y+rects[i].height), FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 0, 255), 1);
		}
		for (int i = 0; i < rects_b.size(); i++)
		{	//对找到血条画矩形
			rectangle(yt, rects_b[i], Scalar(0, 255, 0), 1);
			std::string spoint = format("x:%d,y:%d", rects_b[i].x, rects_b[i].y);
			putText(yt, spoint, Point(rects_b[i].x + rects_b[i].width + 10, rects_b[i].y+rects_b[i].height), FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 255, 0), 1);
		}
		std::string time = format("time:%f", exe_time);
		putText(yt, time, cv::Point(10,10), FONT_HERSHEY_PLAIN, 1.0, Scalar(255, 0, 0), 1);
		imshow("识别结果", yt);
		waitKey(0);
	}
	return 0;

}

void Process(cv::Mat& src, cv::Mat& dst,cv::Scalar& s,float dis)
{
    int rows = src.rows;
    int cols = src.cols*src.channels();
	Mat temp;
	src.convertTo(temp, CV_32FC3);
	dst = Mat::zeros(src.size(), CV_8UC1);

	for (int i = 0; i < rows; i++)
	{
		float* data = temp.ptr<float>(i);
		uchar* dst_data = dst.ptr<uchar>(i);
		int k = 0;
		for (int j = 0; j < cols; j += 3)
		{
			float dst = sqrt(pow(data[j] - s[0], 2) + pow(data[j + 1] - s[1], 2) + pow(data[j + 2] - s[2], 2));
			if (dst < dis)
			{
				dst_data[k] = 255;
			}
			k++;
		}
	}
}

void FindName(cv::Mat& src, vector<Rect>& rects, cv::Scalar& s, float dis, float max_ratio, float min_ratio)
{
	Mat binary;
	Process(src, binary,s,dis);
	GaussianBlur(binary, binary, Size(15, 15), 0, 0);//X,Y偏移为0
	threshold(binary, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	vector<vector<Point>> contours;
	vector<Vec4i> hiearchy;
	findContours(binary.clone(), contours, hiearchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
	for (size_t t = 0; t < contours.size(); t++)
	{
		if (contours[t].size() < 15)
			continue;
		Rect rect = boundingRect(contours[t]);
		float ratio = rect.width / rect.height;
		if (ratio > min_ratio && ratio < max_ratio)
		{
			Mat roi;
			Process(src(rect), roi, s, dis);
			float k = 0;
			for (int i = 0; i < roi.rows; i++)
			{
				uchar* dst_data = roi.ptr<uchar>(i);
				for (int j = 0; j < roi.cols; j++)
				{
					if(dst_data[j] == 255)
						k++;
				}
			}
			double flag = k / roi.cols/roi.rows;
			if(flag > 0.2)
				rects.push_back(rect);
		}
	}
}


