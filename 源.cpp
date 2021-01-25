#include<opencv2/opencv.hpp>
using namespace cv;
//#include <iostream>  
using namespace std;
//�˶������⺯������  


 Mat Sobel(Mat & img) {
    Mat out;
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    
             //X����
             //Sobel(img, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
             //convertScaleAbs(grad_x, abs_grad_x);
     Sobel(img, img, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
     convertScaleAbs(img, out);
    
             //Y����
             //Sobel(img, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
             //convertScaleAbs(grad_y, abs_grad_y);
             //convertScaleAbs(img, out);
        
             //�ϲ�
             //addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, out);
        
     return out;
    
}

 Mat TwoValued(Mat & img) {
     Mat out;
     //threshold(img, out, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
     threshold(img, out, 100, 255, CV_THRESH_BINARY);
        
     return out;
    
}

 Mat Close(Mat & img) {
     Mat out;
     //Mat element(5, 5, CV_8U, cv::Scalar(1));
      Mat element = getStructuringElement(MORPH_RECT, Size(17, 5));
      morphologyEx(img, out, cv::MORPH_CLOSE, element);
    
      return out;
    
}




int main(){
    //������Ƶ
    VideoCapture cap("1.mp4");
    //ѭ����ʾÿһ֡
    while (1){
        Mat img,img1, img_gray;
        //����һ��Mat���������ڴ���ÿһ֡ͼ��
        cap >> img1;
        //resize(img, img, Size(0, 0), 0.5, 0.5, INTER_LINEAR);
        if (img1.empty()){
            printf("no images");
            return -1;
        }
        cvtColor(img1, img_gray, CV_RGB2GRAY);
        Mat mat_mean, mat_stddev;
        meanStdDev(img_gray, mat_mean, mat_stddev);
        double a = mat_mean.at<double>(0, 0);
        cout << a << endl;
        img1.copyTo(img);
        Mat img_gauss;
        GaussianBlur(img, img_gauss, Size(3, 3), 0, 0, BORDER_DEFAULT);
        Mat img_gray2;
        cvtColor(img_gauss, img_gray2, CV_RGB2GRAY);
        img = Sobel(img);
        //imshow("Sobel_X", img);
        img = TwoValued(img);
        //imshow("��ֵ��", img);
        img = Close(img);
        //imshow("�ղ���", img);

        //��������
        vector<vector<Point>>contours;
        findContours(img, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
        //drawContours(img1,contours,-1, Scalar(0, 0, 255), 3);
        //imshow("8.result",img);

        //ROI��ȡ
        Mat roi_img;
        vector<Rect> boundRect(contours.size());

        for (int i = 0; i < contours.size(); i++)
        {
            boundRect[i] = boundingRect(contours[i]);
            double area = contourArea(contours[i]);
            //if (boundRect[i].width > boundRect[i].height * 1.20){ //���Ƴߴ��ж�
            
                //if (area >= 450 && area <= 2000){
                    //��ԭͼ�ϻ��ƾ���
                
                    rectangle(img, Rect(boundRect[i].x, boundRect[i].y, boundRect[i].width, boundRect[i].height), Scalar(0, 0, 255), 2);
                    // ROI��ȡ
                    roi_img = img(Rect(boundRect[i].x, boundRect[i].y, boundRect[i].width, boundRect[i].height));
                    imshow("9.ROI", roi_img);
                //}
             //}
        }



        imshow("��ȡ��Ƶ", img);
        //��ʾ��ǰ֡
        if (waitKey(30) >= 0);
    }

    return 0;
}
