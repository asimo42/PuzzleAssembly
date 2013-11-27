#include "stdafx.h"
#include "Shape.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Shape::Shape(Mat* img)
{
	image = img;
	color = Scalar(0,0,255);
}


Shape::~Shape(void)
{
}

//------------Drawing Methods------------


//Circle
void Shape::Draw_Circle(Point middle, int radius, int thickness, int lineType)
{
	type = Circle;
	startingPoint = middle;
	width = radius * 2;
	height = radius * 2;
	line_thickness = thickness;
	start = Point(-1,-1);
	end = Point(-1,-1);

	circle(*image,
			middle,
			radius,
			color,
			thickness,
			lineType);
}

//Rectangle
void Shape::Draw_Rectangle(Point corner, int wid, int heig, int thickness, int lineType)
{
	type = Rectangular;
	startingPoint = corner;
	width = wid;
	height = heig;
	line_thickness = thickness;
	start = Point(-1,-1);
	end = Point(-1,-1);

	rectangle(*image,
			   startingPoint,
			   Point(corner.x+wid, corner.y+heig),
			   color,
			   thickness,
			   lineType);
}

//Square
void Shape::Draw_Square(Point corner, int wid, int thickness, int lineType)
{
	Draw_Rectangle(corner, wid, wid, thickness, lineType);
	type = Square;
}

//Triangle
// length is length of one side of equilateral triangle
void Shape::Draw_Triangle(Point top, int length, int thickness, int lineType)
{
	type=Triangle;
	startingPoint = top;
	width = length;
	height = length * (sqrt(3)/2);

	line_thickness = thickness;
	start = Point(-1,-1);
	end = Point(-1,-1);

	Point triangle_points[1][3];
	triangle_points[0][0] = Point(top.x, top.y);
	triangle_points[0][1] = Point(top.x - (length/2), top.y + height);
	triangle_points[0][2] = Point(top.x + (length/2), top.y + height);


	if (thickness == -1)
	{
		const Point* ppt[1] = {triangle_points[0]};
		int npt[] = {3};
		fillPoly(*image,
				  ppt,
				  npt,
				  1,
				  color,
				  lineType);
	}
	else
	{
		line(*image,
			  Point(triangle_points[0][0].x, triangle_points[0][0].y),
			  Point(triangle_points[0][1].x, triangle_points[0][1].y),
			  color,
			  thickness,
			  lineType);

		line(*image,
			  Point(triangle_points[0][1].x, triangle_points[0][1].y),
			  Point(triangle_points[0][2].x, triangle_points[0][2].y),
			  color,
			  thickness,
			  lineType);

		line(*image,
			  Point(triangle_points[0][2].x, triangle_points[0][2].y),
			  Point(triangle_points[0][0].x, triangle_points[0][0].y),
			  color,
			  thickness,
			  lineType);
	}
}

//Pentagon
void Shape::Draw_Pentagon(Point top, int length, int thickness, int lineType)
{

}

//Arrow
void Shape::Draw_Arrow(Point begin, Point end, int thickness, int lineType)
{

}
