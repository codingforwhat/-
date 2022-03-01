锘?include<opencv2/opencv.hpp>
#include"opencv2/highgui/highgui.hpp"
#include<stdio.h>
#include<string>
#include<stdint.h>
#include<fstream>
#include<cmath>
using namespace std;
using namespace cv;
Mat search_x_path(Mat energy_map, int object_x)
{
    cv::transpose(energy_map, energy_map);
    const int r = energy_map.rows;
    const int c = energy_map.cols;
    int part_num = c - object_x;
    if (part_num < 0) part_num = -part_num;
    int y_part = c / part_num;//鍖哄煙澶у皬
    //cout << y_part << endl;
    Mat carver_image = Mat::ones(energy_map.size(), CV_8UC1);
    Mat path_map = Mat::zeros(energy_map.size(), CV_32SC1);
    Mat dp_map;
    energy_map.convertTo(dp_map, CV_32SC1);
    int now_end, now_begin;
    int min_data, min_data_coordinate, now_value;
    for (int j = 1; j < r; j++)//閫愯鎿嶄綔
    {
        int* energy = dp_map.ptr<int>(j - 1);
        int* dp = dp_map.ptr<int>(j);
        int* path = path_map.ptr<int>(j);
        now_begin = 0;
        for (int i = 1; i <= part_num; i++)//姣忎釜鍖哄煙
        {
            now_end = now_begin + y_part - 1;
            if (i <= (c % part_num)) now_end++;
            for (int u = now_begin; u <= now_end; u++)//鍖哄煙鍐呯殑姣忎釜鐐?
            {
                min_data_coordinate = u;
                min_data = energy[u];
                for (int k = now_begin; k <= now_end; k++)//瀵绘壘鏈€灏忚矾寰?
                {
                    if (k == u) continue;
                    now_value = k - u;
                    if (now_value < 0) now_value = -now_value;
                    //now_value *= now_value * now_value;
                    //now_value *= now_value;//
                    now_value = pow(8, now_value);
                    now_value += energy[k];
                    if (now_value < min_data)
                    {
                        min_data = now_value;
                        min_data_coordinate = k;
                    }
                }
                dp[u] += min_data;
                path[u] = min_data_coordinate;
            }
            now_begin = now_end + 1;

        }
        //cout << now_end << endl;
    }
    int* dp = dp_map.ptr<int>(r - 1);
    now_begin = 0;
    int now_c;
    for (int i = 1; i <= part_num; i++)
    {
        now_end = now_begin + y_part - 1;
        if (i <= (c % part_num)) now_end++;
        min_data_coordinate = now_begin;
        min_data = dp[now_begin];
        for (int k = now_begin + 1; k <= now_end; k++)
        {
            if (dp[k] < min_data)
            {
                min_data = dp[k];
                min_data_coordinate = k;
            }
        }
        //cout << min_data << endl;
        now_c = min_data_coordinate;
        for (int j = r - 1; j > 0; j--)
        {
            carver_image.at<uchar>(j, now_c) = 255;
            now_c = path_map.at<int>(j, now_c);
        }
        carver_image.at<uchar>(0, now_c) = 255;
        now_begin = now_end + 1;
        //cout << i <<" "<<now_end << endl;
    }
    //fstream file1("123.txt");
    //file1 << path_map << endl;
    //file1.close();
    //cv::transpose(carver_image,carver_image);
    return carver_image;
}
Mat search_y_path(Mat energy_map,int object_y)
{
    const int r = energy_map.rows;
    const int c = energy_map.cols;
    int part_num = c - object_y;
    if (part_num < 0) part_num = -part_num;
    int y_part = c / part_num;//鍖哄煙澶у皬
    //cout << y_part << endl;
    Mat carver_image = Mat::ones(energy_map.size(), CV_8UC1);
    Mat path_map = Mat::zeros(energy_map.size(), CV_32SC1);
    Mat dp_map;
    energy_map.convertTo(dp_map, CV_32SC1);
    int now_end, now_begin;
    int min_data, min_data_coordinate, now_value;
    for (int j = 1; j < r; j++)//閫愯鎿嶄綔
    {
        int* energy = dp_map.ptr<int>(j - 1);
        int* dp = dp_map.ptr<int>(j);
        int* path = path_map.ptr<int>(j);
        now_begin = 0;
        for (int i = 1; i <= part_num; i++)//姣忎釜鍖哄煙
        {
            now_end = now_begin+y_part-1;
            if (i <= (c % part_num)) now_end ++;
            for (int u = now_begin; u <= now_end; u++)//鍖哄煙鍐呯殑姣忎釜鐐?
            {
                min_data_coordinate = u;
                min_data = energy[u];
                for (int k = now_begin; k <= now_end; k++)//瀵绘壘鏈€灏忚矾寰?
                {
                    if (k == u) continue;
                    now_value = k - u;
                    if (now_value < 0) now_value = -now_value;
                    //now_value *= now_value * now_value;
                    //now_value *= now_value;//
                    now_value = pow(8, now_value);
                    now_value += energy[k];
                    if (now_value < min_data)
                    {
                        min_data = now_value;
                        min_data_coordinate = k;
                    }
                }
                dp[u] += min_data;
                path[u] = min_data_coordinate;
            }
            now_begin = now_end + 1;
            
        }
        //cout << now_end << endl;
    }


    int* dp = dp_map.ptr<int>(r - 1);
    now_begin = 0;
    int now_c;
    for (int i = 1; i <= part_num; i++)
    {
        now_end = now_begin + y_part-1;
        if (i <= (c % part_num)) now_end++;
        min_data_coordinate = now_begin;
        min_data = dp[now_begin];
        for (int k = now_begin + 1; k <= now_end; k++)
        {
            if (dp[k] < min_data)
            {
                min_data = dp[k];
                min_data_coordinate = k;
            }
        }
        //cout << min_data << endl;
        now_c = min_data_coordinate;
        for (int j = r - 1; j > 0; j--)
        {
            carver_image.at<uchar>(j, now_c) = 255;
            now_c = path_map.at<int>(j, now_c);
        }
        carver_image.at<uchar>(0, now_c) = 255;
        now_begin = now_end + 1;
        //cout << i <<" "<<now_end << endl;
    }
    //fstream file1("123.txt");
    //file1 << path_map << endl;
    //file1.close();
    return carver_image;
}
Mat enlarge_y(Mat image,Mat carver_image,int object_y)
{
    const int r = image.rows;
    const int c = image.cols;
    //cout << r << " " << c << endl;
    Mat object_image = Mat::zeros(r, object_y, CV_8UC3);
    for (int j = 0; j < r; j++)
    {
        cv::Vec3b* data1 = image.ptr<cv::Vec3b>(j);
        cv::Vec3b* data2 = object_image.ptr<cv::Vec3b>(j);
        uchar* data3 = carver_image.ptr<uchar>(j);
        int ii = 0;
        for (int i = 0; i < c; i++)
        {
            //*/
            if (data3[i] == 1)
            {
                data2[ii] = data1[i];
                ii++;
            }
            else
            {
                data2[ii] = data1[i];
                ii++;
                data2[ii] = data1[i];
                ii++;
            }
            //*/
        }
        //cout << ii << endl;
    }
    return object_image;
}
Mat shrinkage_y(Mat image, Mat carver_image, int object_y)
{
    const int r = image.rows;
    const int c = image.cols;
    //cout << r << " " << c << endl;
    Mat object_image = Mat::zeros(r, object_y, CV_8UC3);
    for (int j = 0; j < r; j++)
    {
        cv::Vec3b* data1 = image.ptr<cv::Vec3b>(j);
        cv::Vec3b* data2 = object_image.ptr<cv::Vec3b>(j);
        uchar* data3 = carver_image.ptr<uchar>(j);
        int ii = 0;
        for (int i = 0; i < c; i++)
        {
            if (data3[i] == 1)
            {
                data2[ii] = data1[i];
                ii++;
            }
        }
        //cout << ii << endl;
    }
    return object_image;
}
Mat enlarge_x(Mat image, Mat carver_image, int object_x)
{
    cv::transpose(image, image);
    const int r = image.rows;
    const int c = image.cols;
    //cout << r << " " << c << endl;
    Mat object_image = Mat::zeros(r, object_x, CV_8UC3);
    for (int j = 0; j < r; j++)
    {
        cv::Vec3b* data1 = image.ptr<cv::Vec3b>(j);
        cv::Vec3b* data2 = object_image.ptr<cv::Vec3b>(j);
        uchar* data3 = carver_image.ptr<uchar>(j);
        int ii = 0;
        for (int i = 0; i < c; i++)
        {
            //*/
            if (data3[i] == 1)
            {
                data2[ii] = data1[i];
                ii++;
            }
            else
            {
                data2[ii] = data1[i];
                ii++;
                data2[ii] = data1[i];
                ii++;
            }
            //*/
        }
        //cout << ii << endl;
    }
    cv::transpose(object_image, object_image);
    return object_image;
}
Mat shrinkege_x(Mat image, Mat carver_image, int object_x)
{
    cv::transpose(image, image);
    const int r = image.rows;
    const int c = image.cols;
    //cout << r << " " << c << endl;
    Mat object_image = Mat::zeros(r, object_x, CV_8UC3);
    for (int j = 0; j < r; j++)
    {
        cv::Vec3b* data1 = image.ptr<cv::Vec3b>(j);
        cv::Vec3b* data2 = object_image.ptr<cv::Vec3b>(j);
        uchar* data3 = carver_image.ptr<uchar>(j);
        int ii = 0;
        for (int i = 0; i < c; i++)
        {
            if (data3[i] == 1)
            {
                data2[ii] = data1[i];
                ii++;
            }
        }
        //cout << ii << endl;
    }
    cv::transpose(object_image, object_image);
    return object_image;
}
Mat energy_(Mat image)
{
    Mat energy_map, sobel_x_map_, sobel_y_map_, image_gray;
    //SeamCarvercomputeFullEnergy(image, energy);
    cv::cvtColor(image, image_gray, cv::COLOR_BGR2GRAY);

    cv::Sobel(image_gray, sobel_x_map_, CV_32F, 1, 0, 3);
    cv::convertScaleAbs(sobel_x_map_, sobel_x_map_);

    cv::Sobel(image_gray, sobel_y_map_, CV_32F, 0, 1, 3);
    cv::convertScaleAbs(sobel_y_map_, sobel_y_map_);

    cv::addWeighted(sobel_x_map_, 0.5, sobel_y_map_, 0.5, 0, energy_map);
    return energy_map;
}
Mat scale(string filepath,string new_file_name, int object_x, int object_y)
{
    Mat image = imread(filepath, 1);
    Mat energy_map = energy_(image);
    const int r = energy_map.rows;
    const int c = energy_map.cols;
    Mat carver_image, object_image;
    if (object_x > r)
    {
        while (object_x > r * 2)
        {
            carver_image = search_x_path(energy_map, r*2);
            object_image = enlarge_x(image, carver_image, r*2);
            object_image.convertTo(image, CV_8UC3);
            energy_map = energy_(image);
            const int r = energy_map.rows;
            const int c = energy_map.cols;
        }
        carver_image = search_x_path(energy_map, object_x);
        object_image = enlarge_x(image, carver_image, object_x);
        object_image.convertTo(image,CV_8UC3);
        energy_map = energy_(image);
        const int r = energy_map.rows;
        const int c = energy_map.cols;
    }
    if (object_y > c)
    {
        while (object_y > c * 2)
        {
            carver_image = search_y_path(energy_map, c * 2);
            object_image = enlarge_y(image, carver_image, c * 2);
            object_image.convertTo(image, CV_8UC3);
            energy_map = energy_(image);
            const int r = energy_map.rows;
            const int c = energy_map.cols;
        }
        carver_image = search_y_path(energy_map, object_y);
        object_image = enlarge_y(image, carver_image, object_y);
        object_image.convertTo(image, CV_8UC3);
        energy_map = energy_(image);
        const int r = energy_map.rows;
        const int c = energy_map.cols;
    }
    if (object_x < r)
    {
        while (object_x * 2 < r)
        {
            carver_image = search_x_path(energy_map, r/2);
            object_image = shrinkege_x(image, carver_image, r/2);
            object_image.convertTo(image, CV_8UC3);
            energy_map = energy_(image);
            const int r = energy_map.rows;
            const int c = energy_map.cols;
        }
        carver_image = search_x_path(energy_map, object_x);
        object_image = shrinkege_x(image, carver_image, object_x);
        object_image.convertTo(image, CV_8UC3);
        energy_map = energy_(image);
        const int r = energy_map.rows;
        const int c = energy_map.cols;
    }
    if (object_y < c)
    {
        while (object_y * 2 < c)
        {
            carver_image = search_y_path(energy_map, c / 2);
            object_image = shrinkage_y(image, carver_image, c / 2);
            object_image.convertTo(image, CV_8UC3);
            energy_map = energy_(image);
            const int r = energy_map.rows;
            const int c = energy_map.cols;
        }
        carver_image = search_y_path(energy_map, object_y);
        object_image = shrinkage_y(image, carver_image, object_y);
    }
    //*/
    //Mat carver_image = search_x_path(energy_map, object_x);
    //imwrite("511c.jpg", carver_image);
    //imshow("carver", carver_image);
    //Mat object_image = enlarge_x(image, carver_image, object_x);
    imwrite(new_file_name, object_image);
    imshow("object", object_image);
    //*/
    waitKey();
    return object_image;
}

int main()
{
    Mat image, energy_map, sobel_x_map_, sobel_y_map_, image_gray;
    //int object_x = 4839, object_y = 4839;
    // 828 1792
    //cin >> object_x >> object_y;
    scale("irelan.jpg","irelan_.jpg", 2509, 4608);
    //scale("irelan1.jpg","irelan2.jpg", 2788, 5120);

}
