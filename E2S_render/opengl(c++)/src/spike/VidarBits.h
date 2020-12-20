/*
	从图像模拟信号 到脉冲阵列数据的 简单实现

	主要参考黄老师的文章。

	关键思想： 

	1.   “积分---发放---复位”
	2.   脉冲阵列数据的输出 采取高速轮询的方式
		

	在第一版本实现中，我们做一个简单假设：

	1. 一个灰度值为 float normalized 到 (0.0, 1.0 ) 之间
	2. 积分 满值 为 float (1.0), 也就是满足当前积分为， 1.0 后

	脉冲信号存储/发放 
	按照 从左上到右下的空间顺序，以及由先及后的时间顺序，每 8 个脉冲组成一个字节。

*/

#pragma once


#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <vector>
#include <iostream>

#ifdef  _WIN32

#include <sys/types.h>
#include <Shlwapi.h>
#include <shlobj.h>
#include <Commdlg.h>

#ifndef arraysize
#define arraysize(a) (sizeof(a)/sizeof(a[0]))
#endif
#ifndef offsetof
#define offsetof(s, m) (size_t)( (ptrdiff_t)&reinterpret_cast<const volatile char&>((((s *)0)->m)) )
#endif
bool openFileDialog(const char* pFilters, std::string& filename);
bool saveFileDialog(const char* pFilters, std::string& filename);
#endif


#ifndef  __FSM_H__
#define __FSM_H__
#include "SImageData.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <complex>
#include "bitbuffer.h"

typedef bool PulseType;
class ImageToPulseSignal 
{
public :
	/*
		FSM settings
	*/

	int width;
	int height;

	int total_frames;
	int query_times_perframe;
	
	int threshold_to_send;
	bool keepResidual;
	   	 
	int frequency;
	int total_secs;

	::std::vector<int> accumulateor;
	::std::vector<int> accumulateorR;
	::std::vector<int> accumulateorG;
	::std::vector<int> accumulateorB;
	ImageToPulseSignal() 
	{
		width = 400;
		height = 250;
		query_times_perframe = 51; //  一个图片 给的光能  中间会轮询 255次
		total_frames = 5000;
		threshold_to_send = 5;
		keepResidual = true;

		frequency = 3;
		total_secs = 1;
		resetBuffer(width, height);
	}

	void resetBuffer(int width, int height)
	{
		accumulateor.resize(width*height);
		accumulateorR.resize(width * height);
		accumulateorG.resize(width * height);
		accumulateorB.resize(width * height);
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				accumulateor [i*height + j] = 0;
				accumulateorR[i * height + j] = 0;
				accumulateorG[i * height + j] = 0;
				accumulateorB[i * height + j] = 0;
			}
	}
	inline int Clamp(int A, int min, int max)
	{
		if (A < min)
			return min;
		else if (A > max)
			return max;
		else return A;
	}

	int SpikeSimulatorFromImage3(SImageData& input, ::std::ofstream& outfile)
	{
		SImageData& r_img = input;
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				SColor  C = r_img.GetPixel(i, j);				
				accumulateorR[i * height + j] += C.R; // 积分形式
				accumulateorG[i * height + j] += C.G; // 积分形式
				accumulateorB[i * height + j] += C.B; // 积分形式
				//if (i == 100 && j == 100)	std::cout << accumulateor[i*height + j] <<std::endl;
			}
		}
		for (int k = 0; k < query_times_perframe; k++)
		{
			bit_buffer RedBits;
			bit_buffer GreenBits;
			bit_buffer BlueBits;

			int e = 0;
			for (int j = 0; j < height; j++)
			{
				for (int i = 0; i < width - 7; i += 8)
				{
					for (int e = 7; e >= 0; e--)  // 倒排
					{
						int real_i = i + e;
						if (accumulateorR[real_i * height + j] > threshold_to_send)
						{
							RedBits.write_bits(true, 1);
							if (keepResidual) accumulateorR[real_i * height + j] -= threshold_to_send;
							else accumulateorR[real_i * height + j] = 0;
						}
						else RedBits.write_bits(false, 1);	

						if (accumulateorG[real_i * height + j] > threshold_to_send)
						{
							GreenBits.write_bits(true, 1);
							if (keepResidual) accumulateorG[real_i * height + j] -= threshold_to_send;
							else accumulateorG[real_i * height + j] = 0;
						}
						else GreenBits.write_bits(false, 1);

						if (accumulateorB[real_i * height + j] > threshold_to_send)
						{
							BlueBits.write_bits(true, 1);
							if (keepResidual) accumulateorB[real_i * height + j] -= threshold_to_send;
							else accumulateorB[real_i * height + j] = 0;
						}
							else BlueBits.write_bits(false, 1);
					}
				}
			}
			// 轮询存储文件
			int t_num = 0;

			for (auto& byte : RedBits.get_bytes())
			{
				outfile << (uint8)byte;
			}
			for (auto& byte : GreenBits.get_bytes())
			{
				outfile << (uint8)byte;
			}
			for (auto& byte : BlueBits.get_bytes())
			{
				outfile << (uint8)byte;
			}
		}
		return 0;
	}

#define DEBUG_OUT 

	int SpikeSimulatorFromImage(SImageData& input, ::std::ofstream &outfile,int  current_num = 0)
	{
		SImageData& r_img = input;
		//图像调整大小
		// 简单编码
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				SColor  C = r_img.GetPixel(i, j);
				uint8 _gray = C.LumaU8();				
				//uint8_accumulate[i*height + j] = _gray;				
				int add_I = Clamp(_gray, 0, 255);
				accumulateor[i*height + j] += add_I; // 积分形式
				
				//if (i == 100 && j == 100)	std::cout << accumulateor[i*height + j] <<std::endl;
			}
		}
		for (int k = 0; k < query_times_perframe; k++)
		{
			bit_buffer tmpBB;
			int e = 0;
			for (int j = 0; j < height; j++)
			{
				for (int i = 0; i < width - 7; i += 8)
				{
					for (int e = 7; e >= 0; e--)  // 倒排
					{						
						int real_i = i + e;
						if (accumulateor[real_i*height + j] > threshold_to_send)
						{
							tmpBB.write_bits(true, 1);
							// uint8_accumulateor[real_i*height + j] --;  //  原始策略
							if (keepResidual)
								accumulateor[real_i*height + j] -= threshold_to_send;
							else
								accumulateor[real_i*height + j] = 0;
							//if (real_i == 100 && j == 100)	std::cout << accumulateor[real_i*height + j] << std::endl;
						}
						else
							tmpBB.write_bits(false, 1);
					}
				}
			}
			// 轮询存储文件
			int t_num = 0;
			for (auto& byte : tmpBB.get_bytes())
			{
				outfile << (uint8)byte;
			}
		}
		return 0;
	}
};


#endif