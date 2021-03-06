#ifndef SHAPE_H
#define SHAPE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1024

using namespace cv;
using namespace std;

enum shapeType{        Circle,
                        Square,
                        Triangle,
                        Pentagon,
                        Rectangular,        //"Rectangle" was previously defined in some Windows file...
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
        inline void Clear_To_Black() {*image = Mat::zeros(SCREEN_HEIGHT, SCREEN_WIDTH, CV_8UC3);}
        inline void set_color(Scalar new_color) {color = new_color;}

        //-----Drawing Functions------
        void Draw_Circle(Point middle, int radius, int thickness = 1, int lineType = 8);
        void Draw_Rectangle(Point corner, int wid, int heig, int thinkness = 1, int lineType = 8);
        void Draw_Square(Point corner, int wid, int thickness = 1, int lineType = 8);
        void Draw_Triangle(Point top, int length, int thickness = 1, int lineType = 8);
        void Draw_Pentagon(Point top, int length, int thickness = 1, int lineType = 8);
        void Draw_Star(Point top, int length, int thickness = 1, int lineType = 8);
        void Draw_Arrow(Point begin, Point end, int thickness = 1, int lineType = 8);

        //-----Other Methods------
        void setColor(Scalar BGR_val) {color = BGR_val;}


private:
        Mat* image;
        Point start;
        Point end;
        Point startingPoint;
        int height;
        int width;
        int line_thickness;
        Scalar color;
        shapeType type;


};

#endif //#ifndef SHAPE_H