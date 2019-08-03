#include <opencv2\opencv.hpp>
#include <iostream>
#include <math.h>
#include "CharacterRecognition.h"
#include <windows.h>
using namespace cv;
using namespace std;
void Process(cv::Mat& src, cv::Mat& dst, cv::Scalar& s,float dis);


/****************************************************
/*		����������vs2015 
/*		��	   : OpenCV3 ���� OpenCV4
/*		������  :FindName
/*		����:	
		src			- ����ͼ�����
/*		rects		- ����ͼ���� ����Ŀ�����꣨���Ͻǣ����Լ�Ŀ��ĳ�����std::vector�洢
/*		s			- ѡ��Ŀ��Ļ�׼��ɫ(0BGR)  ���ֵ���ɫ(220, 85, 210)��Ѫ����ɫ��(255, 125, 245)
/*		dis			- ��Ŀ����ɫ �������  Ĭ�� 50
/*		max_ratio	- Ŀ�곤����������ֵ  Ĭ�ϳ��ȿ� 10
/*		min_ratio	- Ŀ�곤���������Сֵ  Ĭ�ϳ��ȿ� 5
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
		vector<Rect> rects;						//��������
		vector<Rect> rects_b;					//Ѫ������
		QueryPerformanceCounter(&start_t);		//��ʱ
		FindName(src, rects, cla,50,10,5);		//�ҵ���������
		FindName(src, rects_b, Scalar(255, 125, 245) , 50, 10, 3);	//�ҵ�Ѫ������
		QueryPerformanceCounter(&stop_t);		//����
		exe_time = 1e3*(stop_t.QuadPart - start_t.QuadPart) / freq.QuadPart;  //����ʱ��
		for (int i = 0; i < rects.size(); i++)
		{	//���ҵ����ƻ�����
			rectangle(yt, rects[i], Scalar(0, 0, 255), 1);
			std::string spoint = format("x:%d,y:%d", rects[i].x, rects[i].y);
			putText(yt, spoint, Point(rects[i].x+rects[i].width+10, rects[i].y+rects[i].height), FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 0, 255), 1);
		}
		for (int i = 0; i < rects_b.size(); i++)
		{	//���ҵ�Ѫ��������
			rectangle(yt, rects_b[i], Scalar(0, 255, 0), 1);
			std::string spoint = format("x:%d,y:%d", rects_b[i].x, rects_b[i].y);
			putText(yt, spoint, Point(rects_b[i].x + rects_b[i].width + 10, rects_b[i].y+rects_b[i].height), FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 255, 0), 1);
		}
		std::string time = format("time:%f", exe_time);
		putText(yt, time, cv::Point(10,10), FONT_HERSHEY_PLAIN, 1.0, Scalar(255, 0, 0), 1);
		imshow("ʶ����", yt);
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
	GaussianBlur(binary, binary, Size(15, 15), 0, 0);//X,Yƫ��Ϊ0
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


