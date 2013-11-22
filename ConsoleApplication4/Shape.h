#ifndef SHAPE_H
#define SHAPE_H

#include "Shape.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

enum Type{	Circle,
			Square,
			Triangle,
			Pentagon,
			Rectangle,
			Arrow,
			Star};

class Shape
{
public:
	//-----Constructors & Destructor-----
	Shape(Mat* img);
	~Shape(void);

	//-----Accessors
	inline Mat* get_image() const {return image;}
	inline Point get_start() const {return start;}
	inline Point get_end() const {return end;}
	inline Point get_startingPoint() const {return startingPoint;}
	inline int get_height() const {return height;}
	inline int get_width() const {return width;}


	//-----Mutators-----
	//THIS IS NOT DELETE SHAPE; it delets all images and leaves image black 
	inline void Clear_To_Black() {*image = Mat::zeros(480, 640, CV_8UC3);}

	//-----Drawing Functions------
	void Draw_Circle(Point middle, int radius, int thickness = 1, int lineType = 8);
	void Draw_Rectangle(Point corner, int wid, int heig, int thinkness = 1, int lineType = 8);
	void Draw_Square(Point corner, int wid, int thickness = 1, int lineType = 8);
	void Draw_Triangle(Point top, int length, int thickness = 1, int lineType = 8);
	void Draw_Pentagon(Point top, int length, int thickness = 1, int lineType = 8);
	void Draw_Arrow(Point begin, Point end, int thickness = 1, int lineType = 8);

	//-----Other Methods------


private:
	Mat* image;
	Point start;
	Point end;
	Point startingPoint;
	int height;
	int width;
	int line_thickness;
	Scalar color;
	Type type;


};

#endif //#ifndef SHAPE_H
