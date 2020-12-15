
#include <vector>
#include <iostream>
#include "SImageData.h"
#include "bitbuffer.h"
#include <fstream>
#include <random>

class SImagetoSpike{

private:
	/* defination of image */
	int width;
	int height;
	int channels;					//assert 1 or 3

	/* defination of simulator */
	int tr[10];
	int query_times_perframe;
	int threshold;
	bool keepResidual;				//reset after pulse?
	int set_zero;//用于清空累积值 否则会有重影效应
	double set_zero_delta;//用于判断是否清空 初次更新占总dog比例 到达set_zero_delta则全体清空
	::std::vector<double> thresalpha;//biased threshold caused by inductance deviation
	::std::vector<int> thresbiasU;	//biased threshold caused by voltage deviation
	::std::vector<int> accumulateI;	//biased accumulation caused by leakage current
	::std::vector<int> accumulator;	//accumulator for gray image
	::std::vector<int> accumulatorR, accumulatorG, accumulatorB;
	inline int Clamp(int target, int min, int max)
	{
		if(target < min)
			return min;
		else if(target > max)
			return max;
		else return target;
	}

	/*
	 * simulate different types of image, you can set your own here
	 * defination outside the class will not make it inline
	 */
	void SimulateoneChannel(SImageData& img, ::std::ofstream& outstream, int factor = 1, int* facmat = NULL);
	void SimulatethreeChannel(SImageData& img, ::std::ofstream& outstream, int factor = 1, int* facmat = NULL);
public:
	SImagetoSpike()
	{
		width = 400;
		height = 250;
		channels = 3;
		query_times_perframe = 1;
		threshold = 400;
		keepResidual = false;
		//dog set as follow
		resetAccumulator(width, height, channels);
		printf("hhh \n");
	}
	void resetAccumulator(int width, int height, int channels);
	void setSimulator(int query, int thres, bool keep);
	int SimulateSpikeFromImage(SImageData& img, ::std::ofstream& outstream, int factor = 1, int* facmat = NULL, int flag_dog = 0
	);	
};