
#include <iostream>

#include <opencv2\opencv.hpp>
#include <opencv2\core.hpp>
#include <opencv2\features2d.hpp>
#include <opencv2\highgui.hpp>

#include <vector>
#include <math.h>

#define pi 3.1415926;
using namespace std;
using namespace cv;

int xmin = 1200;
int xmax = 2600;
int ymin = 700;
int ymax = 2000;

int h = 320;
double th = (90.0 - 25.0) / 180.0*pi

double fx = 2857.38;
double fy = 2857.43;
double u0 = 1837.53;
double v0 = 1347.65;
int maxfun(int *p,int size)
{
	int max = p[0];
	
	for (int i = 0; i < size; i++)
	{
		if (max <= p[i])
			max = p[i];
	}
	return max;
}

int minfun(int *p,int size)
{
	int min = p[0];
	
	cout<<p[3];
	for (int i = 0; i < size; i++)
	{
		if (min >= p[i])
			min = p[i];
	}
	return min;
}
int main()
{
	Mat img = imread("ni2.jpg");
	Mat out;
	int col = img.cols;
	int row = img.rows;
	Point2f po[4] = { Point2f(xmin, ymin), Point2f(xmin, ymax), Point2f(xmax, ymin), Point2f(xmax, ymax) };
	Point2f pn[4];
	int x[4];
	int y[4];
	int size = sizeof(x) / sizeof(x[0]);
	for (int i = 0; i < 4; i++)
	{
		pn[i].y= int((-fy * sin(th)*h + (po[i].y - v0)*cos(th)*h) / (fy*cos(th) + (po[i].y - v0)*sin(th)));
		pn[i].x= int((po[i].x - u0)*(-sin(th)*pn[i].y + cos(th)*h) / fx);
		x[i] = (pn[i].x);
		y[i]= (pn[i].y);
	}
	
	int maxx = maxfun(x, size);
	int minx = minfun(x, size);
	int maxy = maxfun(y, size);
	int miny = minfun(y, size);

	int c = maxx - minx;
	int r = maxy - miny;
	int a = 2;
	for (int i = 0; i < 4; i++)
	{
		pn[i].y = (pn[i].y-miny);
		pn[i].x = (pn[i].x-minx);
		
	}

	Mat T = getPerspectiveTransform(po, pn);
	warpPerspective(img, out, T, Size(img.cols, img.rows), INTER_CUBIC);
	imwrite("map.jpg", out);
	
    return 0;
}

