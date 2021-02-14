/*
 * Algorithm Steps:
 *
 * 1- Convert image to grayscale
 * 2- Apply median filter to eliminate noise
 * 3- Apply canny to get binary image
 * 4- Find contours with the efficient parameters
 * 5- Apply minAreaRect function to get the fitted rectangles for each contour
 * 6- Filter contours by their length not to get small contours(noisy contours)
 * 7- Get the center of fitted recttangles
 * 8- Compare each contour's point with the center of fitted rectangles
 * 9- Make a comparison and get the results
 *
 * Requirements
 *
 * This algorithm works well in these conditions:
 *
 * 1- The pictures should be taken parallel to surface(camera should be parallel to target circles)
 * 2- Shadows shouldn't exist or they should be eliminated
 * 3- Occlusion
*/

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

cv::RNG rng(12345);

int main()
{
    cv::namedWindow("Input",0);
    cv::namedWindow("Output",0);
    cv::namedWindow("Median",0);
    cv::namedWindow("Canny",0);
    cv::namedWindow("inRange",0);

    cv::Mat cannyOutput,medianImg,output;

    cv::Mat img = cv::imread("/home/code/Documents/images/circles/c9.jpeg");
    output = img.clone();
    cv::imshow("Input",img);

    //Step 1
    cv::cvtColor(img,img,cv::COLOR_BGR2GRAY);

    //Step 2
    cv::medianBlur(img,medianImg,5);
    cv::imshow("Median",medianImg);

    //Step 3
    cv::Canny(medianImg,cannyOutput,80,240,3,0);
    cv::imshow("Canny",cannyOutput);

    //Step 4
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(cannyOutput,contours,hierarchy,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_SIMPLE);

    std::vector<cv::RotatedRect> minRect( contours.size() );

    int counter = 1;
    for( size_t i = 0; i< contours.size(); i++ )
    {
        //Step 5
        minRect[i] = cv::minAreaRect( contours[i] );
        cv::Point2f rect_points[4];
        minRect[i].points( rect_points );

        //Step 6
        if(contours[i].size()>50)
        {
            //Step 7
            int centerX = (rect_points[0].x + rect_points[2].x)/2;
            int centerY = (rect_points[0].y + rect_points[2].y)/2;
            cv::Point2f a(centerX,centerY);

            //Step 8 and Step 9
            int sum = 0;
            std::vector<int> storeLength;
            for(int j=0; j<(int)contours[i].size(); j++)
            {
                cv::Point2f b(contours[i][j].x,contours[i][j].y);
                int res = cv::norm(cv::Mat(a),cv::Mat(b));
                sum += res;
                storeLength.push_back(res);
            }
            int meanLength = sum / (int)storeLength.size();
            int countBads = 0;
            for(int u:storeLength)
                if(abs(u-meanLength)>3)
                    countBads++;

            if(countBads<5)
            {
                for ( int j = 0; j < 4; j++ )
                {
                    line( output, rect_points[j], rect_points[(j+1)%4], cv::Scalar(0,0,255),3 );
                    cv::putText(output,std::to_string(counter),cv::Point(centerX,centerY),cv::FONT_HERSHEY_SIMPLEX,1.0,cv::Scalar(0,255,255),3);
                }
                counter++;
            }
        }
    }

    cv::imshow("Output",output);

    cv::waitKey(0);



    return 0;
}
