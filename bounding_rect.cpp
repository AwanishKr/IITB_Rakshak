#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

Mat src; Mat src_gray; Mat gray; Mat open; Mat close; Mat gradient_image;
Mat src_output; Mat element; Mat binary;   
int lowThreshold = 70;
int ratio = 3; 
//int thresh = 10;
//int max_thresh = 255;
RNG rng(12345);

float area = 0, maxArea = 0, variable = 0;
vector<float> top_ten(10) ;
int main( int argc, char** argv )
{
  src = imread(argv[1]); 
  //resize(src, src, Size(1080,820));  
  //imshow("Source", src);

  vector<vector<Point> > contours; 
  vector<Vec4i> hierarchy;  
  GaussianBlur( src, src, Size(3,3), 3, 3 );
  element = getStructuringElement(0, Size(3,3), Point(0,0));
  morphologyEx( src, open, 2, element );
  //imshow("open image", open);
  morphologyEx(open, close, 3, element);
  morphologyEx(close, gradient_image, 4, element);
  //imshow("gradient image", gradient_image);
  
  cvtColor( gradient_image, gray, COLOR_BGR2GRAY );
  //imshow("grayscale image", gray);
  //threshold( gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
  threshold( gray, binary, 15, 255, THRESH_BINARY);
  //imshow("binary image", binary);
  //Canny( gray, binary,lowThreshold, lowThreshold*ratio, 3 );

  findContours( binary, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
  
  for(size_t y = 0; y < contours.size(); y++)		
  {
  	variable = contourArea(contours[y]) ;
  	if(variable > maxArea)	
  	{
  		maxArea = variable ;
  	}
  }
  
  top_ten[0] = maxArea;
  maxArea = 0;
  cout<<top_ten[0]<<endl;

  for(size_t l = 1; l<10; l++)
  {		
  	for(size_t j =0; j < contours.size(); j++)	
  	{
  		variable = contourArea(contours[j]);
  		if(variable < top_ten[l-1])
  		{
  			if(variable > maxArea) {
  				maxArea = variable;
        }
  		}
  	}
  	top_ten[l] = maxArea;
  	maxArea = 0;
  //cout<<top_ten[l]<<endl;
  }  	
  //cout<< contours.size()<<endl;
  //Mat drawing = Mat::zeros( binary.size(), CV_8UC3 );
  Mat mask = Mat::zeros( src.size(), CV_8UC3 );
  Mat src_output = Mat::zeros( src.size(), CV_8UC3);
  vector<Rect> rectangles( contours.size() );
  vector<Mat> objects;
  //vector<Point> v;

  for(size_t t = 0; t< contours.size(); t++ )
     {
     	area = contourArea(contours[t]);	
    	if(area > top_ten[9])
        {
        	rectangles[t] = boundingRect(contours[t]) ;
         	rectangle(mask, rectangles[t].tl(), rectangles[t].br(), Scalar(255, 255, 255), -1, 8, 0 ) ;
            
          	objects.push_back(src(rectangles[t]));
            //imwrite("objects[i].jpg", objects[i]);
            //cout<<v[0].x<<" "<<v[0].y<<" "<<v[1].x<<" "<<v[1].y<<"\n";
            //imshow("testing", mask);
            //waitKey(0);
        } 
     }
 //resize(objects[0], objects[0], Size(640,480));
 //resize(objects[1], objects[1], Size(640,480));
for(int i = 0; i < 9; i++) {
 imwrite(argv[1]+to_string(i)+".jpg", objects[i]);
}
/* imwrite(argv[1]+"1.jpg", objects[1]);
 imwrite(argv[1]+"2.jpg", objects[2]);
 imwrite(argv[1]+"3.jpg", objects[3]);
 imwrite(argv[1]+"4.jpg", objects[4]);
 imwrite(argv[1]+"5.jpg", objects[5]);
 imwrite(argv[1]+"6.jpg", objects[6]);
 imwrite(argv[1]+"7.jpg", objects[7]);
 imwrite(argv[1]+"8.jpg", objects[8]);
 */ // vector<Point> v;
  // v.push_back(rectangles[1].tl());
  // v.push_back(rectangles[1].br());
  // cout<<v[0].x<<v[0].y<<v[1].x<<v[1].y;
     
  //cout<<top_ten[9];     
  //imshow("mask without threshold", mask);   
  bitwise_and(mask, src, src_output);
  //imshow("objects", src_output);
  //imwrite("objects.jpg", src_output);
  waitKey(0);
  return(0);
}
