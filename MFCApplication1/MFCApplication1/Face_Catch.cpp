
#include "stdafx.h"
#include "Face_Catch.h"


Face_Catch::Face_Catch()
{
	standsize.height = 200;
	standsize.width = 200;
}

Face_Catch::~Face_Catch()
{

}


void Face_Catch::get_Face_Frame(Mat &img, Mat &face, VideoCapture &capture, CascadeClassifier& cascade, double scale)
{//从视频流中获取图像并划定人脸返回
	Mat frame,gray;
	vector<Rect> faces;

	if (capture.isOpened())
	{
		int times = 0;
		while(!capture.read(frame) && times == 2)
		{
			waitKey(100);
			times++;
		}


		faces = detect_Face(frame, cascade, scale);
		//cvtColor(frame, gray, COLOR_BGR2GRAY);//转化为灰度图像
		//进行人脸检测
		//cascade.detectMultiScale(gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

		int i, maxxsize = 0, id = -1, area;
		for (i = 0; i < faces.size(); i++)//寻找最大的人脸区保留下来，其他的舍弃
		{	
			area = faces[i].width*faces[i].height; 
			if (maxxsize < area)
			{
				maxxsize = area;
				id = i;
			}
		}
		if (id != -1)
		{
			//double aspect_ratio = (double)faces[id].width / faces[id].height;
			frame.copyTo(img);
			rectangle(img, cvPoint(cvRound(faces[id].x*scale), cvRound(faces[id].y*scale)),
				cvPoint(cvRound((faces[id].x + faces[id].width - 1)*scale), cvRound((faces[id].y + faces[id].height - 1)*scale)),
				CV_RGB(255, 0, 0), 3, 8, 0);
			Rect faceRect;//将原来缩小的图像按比例放大
			faceRect.x = cvRound(faces[id].x*scale);
			faceRect.y = cvRound(faces[id].y*scale);
			faceRect.height = cvRound((faces[id].width - 1)*scale);
			faceRect.width = cvRound((faces[id].height - 1)*scale);
			face = frame(faceRect);
			cvtColor(face, face, CV_BGR2GRAY);
		}
	}
}


vector<Rect> Face_Catch::detect_Face(Mat &frame, CascadeClassifier& cascade, double scale)
{
	Mat gray, smallImg(cvRound(frame.rows / scale), cvRound(frame.cols / scale), CV_8UC1);
	double t = 0;

	cvtColor(frame, gray, CV_BGR2GRAY);//在进行人脸检测之前要先将图像转化为灰度图
	resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);//通过缩小图片加快人脸检测的速度
	equalizeHist(smallImg, smallImg);//直方图均衡化

	//t = (double)cvGetTickCount();//计时，统计人脸检测时间
	cascade.detectMultiScale(smallImg, faces,
		1.1, 2, 0
		| CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		//|CV_HAAR_SCALE_IMAGE
		,
		Size(30, 30));
	//t = (double)cvGetTickCount() - t;
	//printf("detection time = %g ms\n", t / ((double)cvGetTickFrequency()*1000.));
	return faces;
}


void Face_Catch::face_Reco_Train(Ptr<FaceRecognizer> &model, vector<Mat> &trainFace, vector<int> &trainLabels, CvSize size)
{
	int i;
	for (i = 0; i < trainFace.size(); ++i)
	{
		resize_norm(trainFace[i], size);//进行图片对齐和归一化
	}
//	Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();//创建并初始化一个特征脸模型
	model->train(trainFace, trainLabels);//对图像和标签进行训练

}


void Face_Catch::face_Reco_Update(Ptr<FaceRecognizer> &model, vector<Mat> &newFaces, vector<int> &newLabels, CvSize size)
{
	int i;
	for (i = 0; i < newFaces.size(); ++i)
	{
		resize_norm(newFaces[i], size);
	}
	model->update(newFaces, newLabels);//更新分类器
}


bool Face_Catch::save_Reco_Data(Ptr<FaceRecognizer> &model)
{//保存人脸识别分类器的特征信息
	char path_dir_c[200];
	strcpy_s(path_dir_c, dir_path.c_str());

	if (CheckDir(path_dir_c) == 0 || CheckDir(path_dir_c) == 1)//检查文件夹是否存在
	{
		model->save(path);
		return true;
	}
	else
		return false;
}


bool Face_Catch::load_Reco_Data(Ptr<FaceRecognizer> &model)
{//读取人脸识别分类器的特征信息
//	Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
	FILE *fp = NULL;
	char path_c[100];
	strcpy_s(path_c, path.c_str());
	fopen_s(&fp, path_c, "r");
	if (fp)
	{
		fclose(fp);
		model->load(path);
		return true;
	}
	return false;
}


//检查文件夹是否存在，不存在则创建之
//文件夹存在返回 0
//文件夹创建失败返回-1
//文件夹创建失败返回1
int Face_Catch::CheckDir(char* Dir)
{
	FILE *fp = NULL;
	char TempDir[200];
	memset(TempDir, '\0', sizeof(TempDir));
	sprintf_s(TempDir, Dir);
	strcat_s(TempDir, "\\");
	strcat_s(TempDir, ".temp.fortest");
	fopen_s(&fp, TempDir, "w");
	if (!fp)
	{
		if (_mkdir(Dir) == 0)
		{
			return 1;//文件夹创建成功
		}
		else
		{
			return -1;//can not make a dir;
		}
	}
	else
	{
		fclose(fp);
	}
	return 0;
}


Mat Face_Catch::resize_norm(InputArray &_src, CvSize stand_size) 
{
	Mat dst;
	Mat src = _src.getMat();
	resize(_src, dst,stand_size);//尺寸对齐
	// 创建和返回归一化的图像:
	switch (src.channels()) {
	case 1:
		normalize(dst, dst, 0, 255, NORM_MINMAX, CV_8UC1);
		break;
	case 3:
		normalize(dst, dst, 0, 255, NORM_MINMAX, CV_8UC3);
		break;
	default:
		src.copyTo(dst);
		break;
	}
	return dst;
}



//字符串分割函数,str为源字符串，pattern为分隔符
vector< string> Face_Catch::split(string str, string pattern)
{
	vector<string> ret;
	if (pattern.empty()) return ret;
	size_t start = 0, index = str.find_first_of(pattern, 0);
	while (index != str.npos)
	{
		if (start != index)
			ret.push_back(str.substr(start, index - start));
		start = index + 1;
		index = str.find_first_of(pattern, start);
	}
	if (!str.substr(start).empty())//剩下的不为空，这将剩下的作为最后一个字段返回
		ret.push_back(str.substr(start));
	return ret;
}
