#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace cv;
using namespace std;

/**
* @brief foreach_files
* @param pattern : "E:/0-irisian-database/0-image_tools/*.sh"
*/
void foreach_files(const std::string& pattern, std::vector<std::string> &filename_vec)
{
    std::vector<cv::String> files;
    cv::glob(pattern, files, true);
    for(std::vector<cv::String>::const_iterator it = files.begin(); it != files.end(); it++)
    {
        filename_vec.push_back(*it);
        std::cout << *it << std::endl;
    }
}

void get_sample_list(const std::string& image_dir, std::vector<std::string> &filename_vec)
{
   std::string pattern = image_dir + "*.bmp";
   foreach_files(pattern, filename_vec);
   pattern = image_dir + "*.jpg";
   foreach_files(pattern, filename_vec);
   pattern = image_dir + "*.png";
   foreach_files(pattern, filename_vec);
}

int main(int argc, char *argv[])
{
    std::string cascade_file = "model/cascade.xml";
    std::string test_image_dir = "images/test/";
    if(argc < 3)
    {
        printf("%s <cascade_file> <test_image_dir>\n", argv[0]);
	return -1;
    }
    else
    {
        cascade_file = argv[1];
        test_image_dir = argv[2];
    }


    CascadeClassifier cascade;
    if(!cascade.load(cascade_file))
    {
        cout << "cascade load failed." << endl;
        return -1;
    }

    std::vector<std::string> filename_vec;
    get_sample_list(test_image_dir, filename_vec);

    for(int i = 0; i < filename_vec.size(); i++)
    {
        Mat image;

        image = imread(filename_vec[i], 1);

        if(image.empty())
        {
           cout << "no image" << endl;
           continue;
        }

        cv::Mat gray;
        cvtColor(image, gray, CV_BGR2GRAY);
        vector<Rect> objects;
        cv::Size min_size(50, 50);
        cv::Size max_size(250, 250);

        int bt = cv::getTickCount();

        cascade.detectMultiScale(gray, objects, 1.1, 3, CASCADE_FIND_BIGGEST_OBJECT, min_size, max_size);

        int et = cv::getTickCount();
        int t = (et - bt) * 1000.0 / cv::getTickFrequency();

        printf("t = %d ms\n", t);

        for(int i = 0; i < objects.size(); i++)
        {
            rectangle(image, objects[i], Scalar(0,255,0), 2);
        }
        cv::imshow("test", image);
        cv::waitKey();
    }
    return 0;
}
