#include<opencv2/opencv.hpp>
#include<iostream>
#include<fstream>
#include<cstdio>

#include "vidarsimulation.h"
#include "parse.h"

using namespace cv;
void test();
int main(int argc, char** argv)
{
	//test();
	//return 0;

	parse_command(argc, argv);
	if (type == EMPTY)
	{
		cout << "No input file, please select an image or a directory." << endl;
		show_help();
		return 0;
	}

	static Mat img;
	if (type == FORMAT)
	{
		/*
		* simulate spikes of a sequence of images
		* initalize simulator, continuously load images and simulate
		*/
		int file_idx = 1;
		char buffer[256];
		int symbolnum = 0;
		for (int i = 0; i < file_format.size(); i++)
		{
			if (file_format[i] == '%')
				symbolnum++;
			if (symbolnum >= 2)
			{
				cout << "Too many % in the format, fail to parse." << endl;
				return 0;
			}

		}
		if (symbolnum == 0)
		{
			cout << "Warning: no % in format, simulate may fail." << endl;
		}
		sprintf_s(buffer, 256, file_format.c_str(), file_idx);

		string input_file = buffer;
		//cout << ".//1920x1080//" + input_file << endl;
		img = imread(input_file);
		if (img.empty())
		{
			cout << "Failed to load file: " << input_file << endl;
			return 0;
		}
		if (USEIMAGESIZE)
		{
			WIDTH = img.cols;
			HEIGHT = img.rows;
			cout << WIDTH << endl;
			cout << HEIGHT << endl;
		}

		SImageData simg;
		ImageInit(simg, WIDTH * FACTOR, HEIGHT * FACTOR);

		SImagetoSpike* simulator = new SImagetoSpike();

		::std::ofstream outstream;
		outstream.open(output_filename, ::std::ios::binary);

		Size ResizeSize = Size(WIDTH * FACTOR, HEIGHT * FACTOR);

		while (1)
		{
			//resize(img, img, ResizeSize,0, 0, INTER_AREA);
			resize(img, img, ResizeSize);
			//printf("ok");
			//imwrite("E:\\image\\multi-objects80000\\VidarDatasetDemo\\vidar_png\\400x250\\" + std::to_string(file_idx) + ".png", img);
			//cout << "E:\\image\\multi-objects80000\\VidarDatasetDemo\\vidar_png\\400x250\\" + std::to_string(file_idx) + ".png" << endl;
			for (int i = 0; i < WIDTH * FACTOR; i++)
			{
				for (int j = 0; j < HEIGHT * FACTOR; j++)
				{
					SColor& targetC = simg.GetPixel(i, j);
					targetC.R = img.at<Vec3b>(j, i)[2];
					targetC.G = img.at<Vec3b>(j, i)[1];
					targetC.B = img.at<Vec3b>(j, i)[0];
				}
			}
			simulator -> SimulateSpikeFromImage(simg, outstream, FACTOR, FACMAT, 0);
			// load next image, break when empty
			file_idx++;
			sprintf_s(buffer, 256, file_format.c_str(), file_idx);
			input_file = buffer;
			img = imread(input_file);
			if (img.empty() || file_idx > 1000)//46000
			{
				cout << "Simulate end here." << endl;
				break;
			}

			if (file_idx % 50 == 0)
			{
				cout << file_idx << " frames finished!" << endl;
			}
		}
		outstream.close();
		cout << file_idx << " image(s) is(are) simulated in total." << endl;
		delete simulator;
		return 0;
	}

	cout << "Something strange occurs......" << endl;
	return 0;
}



void test()
{
	Mat bgrmat;
	Mat tmpmat;
	bgrmat = imread("D:\\work\\vidar-project\\Imgs2VidarBitsV2\\test.bmp");
	int thres[4] = { 255, 510, 1020, 2040 };
	for (int t = 0; t < 4; t++)
	{
		bgrmat.copyTo(tmpmat);
		for (int i = 0; i < tmpmat.rows; i++)
		{
			for (int j = 0; j < tmpmat.cols; j++)
			{
				tmpmat.at<Vec3b>(i, j)[0] = tmpmat.at<Vec3b>(i, j)[0] == 0 ? 0 : thres[t] / (thres[t] / tmpmat.at<Vec3b>(i, j)[0] + 1);
				tmpmat.at<Vec3b>(i, j)[1] = tmpmat.at<Vec3b>(i, j)[1] == 0 ? 0 : thres[t] / (thres[t] / tmpmat.at<Vec3b>(i, j)[1] + 1);
				tmpmat.at<Vec3b>(i, j)[2] = tmpmat.at<Vec3b>(i, j)[2] == 0 ? 0 : thres[t] / (thres[t] / tmpmat.at<Vec3b>(i, j)[2] + 1);
			}
		}
		imwrite("bgr" + std::to_string(thres[t]) + ".png", tmpmat);

		cvtColor(bgrmat, tmpmat, COLOR_BGR2YUV);
		for (int i = 0; i < tmpmat.rows; i++)
		{
			for (int j = 0; j < tmpmat.cols; j++)
			{
				tmpmat.at<Vec3b>(i, j)[0] = tmpmat.at<Vec3b>(i, j)[0] == 0 ? 0 : thres[t] / (thres[t] / tmpmat.at<Vec3b>(i, j)[0] + 1);
				tmpmat.at<Vec3b>(i, j)[1] = tmpmat.at<Vec3b>(i, j)[1] == 0 ? 0 : thres[t] / (thres[t] / tmpmat.at<Vec3b>(i, j)[1] + 1);
				tmpmat.at<Vec3b>(i, j)[2] = tmpmat.at<Vec3b>(i, j)[2] == 0 ? 0 : thres[t] / (thres[t] / tmpmat.at<Vec3b>(i, j)[2] + 1);
			}
		}
		cvtColor(tmpmat, tmpmat, COLOR_YUV2BGR);
		imwrite("yuv" + std::to_string(thres[t]) + ".png", tmpmat);

		cvtColor(bgrmat, tmpmat, COLOR_BGR2HSV);
		for (int i = 0; i < tmpmat.rows; i++)
		{
			for (int j = 0; j < tmpmat.cols; j++)
			{
				tmpmat.at<Vec3b>(i, j)[0] = tmpmat.at<Vec3b>(i, j)[0] == 0 ? 0 : thres[t] / (thres[t] / tmpmat.at<Vec3b>(i, j)[0] + 1);
				tmpmat.at<Vec3b>(i, j)[1] = tmpmat.at<Vec3b>(i, j)[1] == 0 ? 0 : thres[t] / (thres[t] / tmpmat.at<Vec3b>(i, j)[1] + 1);
				tmpmat.at<Vec3b>(i, j)[2] = tmpmat.at<Vec3b>(i, j)[2] == 0 ? 0 : thres[t] / (thres[t] / tmpmat.at<Vec3b>(i, j)[2] + 1);
			}
		}
		cvtColor(tmpmat, tmpmat, COLOR_HSV2BGR);
		imwrite("hsv" + std::to_string(thres[t]) + ".png", tmpmat);
	}

}