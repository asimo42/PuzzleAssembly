#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "Shape.h"
#include "Functions.h"

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

void Shape::setImage(Mat* img) {
	image = img;
	color = Scalar(0,0,255);
}

// close puzzle board window
void Shape::endImage() {
	//cv::destroyAllWindows();
	//cvReleaseImage(this->image);
	this->image->release();
}

//------------Drawing Methods------------

// Pick which shape to draw
void Shape::Draw_Shape(TrackedPiece piece, int dim_factor)
{
	std::string shapeType = piece.getName();
	if (shapeType == "Circle") {
		setColor(Scalar(0, 0, 255/dim_factor));
		Draw_Circle(Point(piece.getShapePointX(),piece.getShapePointY()), piece.getShapeRadius(), -1);
	}
	else if (shapeType == "Rectangle") {
		setColor(Scalar(0, 255/dim_factor, 0));
		Draw_Rectangle(Point(piece.getShapePointX(),piece.getShapePointY()), piece.getShapeWidth(),piece.getShapeHeight(), -1);
	}
	else if (shapeType == "Square") {
		setColor(Scalar(255/dim_factor, 0, 0));
		Draw_Square(Point(piece.getShapePointX(),piece.getShapePointY()), piece.getShapeWidth(), -1);
	}
	else if (shapeType == "Triangle") {
		setColor(Scalar(255/dim_factor, 0, 255/dim_factor));
		Draw_Triangle(Point(piece.getShapePointX(),piece.getShapePointY()), piece.getShapeLength(), -1);
	}
	else if (shapeType == "Pentagon") {
		setColor(Scalar(0, 255/dim_factor, 255/dim_factor));
		Draw_Pentagon(Point(piece.getShapePointX(),piece.getShapePointY()), piece.getShapeLength(), -1);
	}
	else { 
		System::String^ str = "Error: cannot draw piece \"" + stdStringToSystemString(shapeType) + "\". Not a recognized shape.";
		//System::Windows::Forms::MessageBox::Show(str);
		System::Console::WriteLine(str);
	}
}


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
	type = Pentagon;
	startingPoint = top;
	width = 1.61803398875*length;
	height = 1.538909039*length;
	start = Point(-1,-1);
	end = Point(-1,-1);

	line_thickness = thickness;

	Point p1 = Point(top.x + (0.80901699437*length), top.y + (0.58778525229*length));
	Point p2 = Point(p1.x - (0.30901699436*length), top.y + height);
	Point p3 = Point(p2.x - length, p2.y);
	Point p4 = Point(top.x - (0.80901699437*length), p1.y);

	Point pentagon_points[1][5];
	pentagon_points[0][0] = top;
	pentagon_points[0][1] = p1;
	pentagon_points[0][2] = p2;
	pentagon_points[0][3] = p3;
	pentagon_points[0][4] = p4;

	if (thickness == -1)
	{
		const Point* ppt[1] = {pentagon_points[0]};
		int npt[] = { 5 };
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
			  Point(pentagon_points[0][0].x, pentagon_points[0][0].y),
			  Point(pentagon_points[0][1].x, pentagon_points[0][1].y),
			  color,
			  thickness,
			  lineType);

		line(*image,
			  Point(pentagon_points[0][1].x, pentagon_points[0][1].y),
			  Point(pentagon_points[0][2].x, pentagon_points[0][2].y),
			  color,
			  thickness,
			  lineType);

		line(*image,
			  Point(pentagon_points[0][2].x, pentagon_points[0][2].y),
			  Point(pentagon_points[0][3].x, pentagon_points[0][3].y),
			  color,
			  thickness,
			  lineType);

		line(*image,
			  Point(pentagon_points[0][3].x, pentagon_points[0][3].y),
			  Point(pentagon_points[0][4].x, pentagon_points[0][4].y),
			  color,
			  thickness,
			  lineType);

		line(*image,
			  Point(pentagon_points[0][4].x, pentagon_points[0][4].y),
			  Point(pentagon_points[0][0].x, pentagon_points[0][0].y),
			  color,
			  thickness,
			  lineType);
	}

}

//Star
void Shape::Draw_Star(Point top, int length, int thickness, int lineType)
{
	type = Star;
	startingPoint = top;
	width = 1.61803398875*length;
	height = 1.538909039*length;
	start = Point(-1,-1);
	end = Point(-1,-1);

	line_thickness = thickness;

	Point p1 = Point(top.x + (0.80901699437*length), top.y + (0.58778525229*length));
	Point p2 = Point(p1.x - (0.30901699436*length), top.y + height);
	Point p3 = Point(p2.x - length, p2.y);
	Point p4 = Point(top.x - (0.80901699437*length), p1.y);

	Point pentagon_points[1][5];
	pentagon_points[0][0] = top;
	pentagon_points[0][1] = p2;
	pentagon_points[0][2] = p4;
	pentagon_points[0][3] = p1;
	pentagon_points[0][4] = p3;

	if (thickness == -1)
	{
		const Point* ppt[1] = {pentagon_points[0]};
		int npt[] = { 5 };
		fillPoly(*image,
				  ppt,
				  npt,
				  1,
				  color,
				  lineType);
		Shape temp_shape = Shape(image);
		temp_shape.Draw_Pentagon( Point( top.x, top.y + (length * 1.175) ), -(length * 0.38), -1 );

	}
	else
	{
		line(*image,
			  Point(pentagon_points[0][0].x, pentagon_points[0][0].y),
			  Point(pentagon_points[0][1].x, pentagon_points[0][1].y),
			  color,
			  thickness,
			  lineType);

		line(*image,
			  Point(pentagon_points[0][1].x, pentagon_points[0][1].y),
			  Point(pentagon_points[0][2].x, pentagon_points[0][2].y),
			  color,
			  thickness,
			  lineType);

		line(*image,
			  Point(pentagon_points[0][2].x, pentagon_points[0][2].y),
			  Point(pentagon_points[0][3].x, pentagon_points[0][3].y),
			  color,
			  thickness,
			  lineType);

		line(*image,
			  Point(pentagon_points[0][3].x, pentagon_points[0][3].y),
			  Point(pentagon_points[0][4].x, pentagon_points[0][4].y),
			  color,
			  thickness,
			  lineType);

		line(*image,
			  Point(pentagon_points[0][4].x, pentagon_points[0][4].y),
			  Point(pentagon_points[0][0].x, pentagon_points[0][0].y),
			  color,
			  thickness,
			  lineType);
	}

}

//Arrow
void Shape::Draw_Arrow(Point begin, Point end, int thickness, int lineType)
{

}