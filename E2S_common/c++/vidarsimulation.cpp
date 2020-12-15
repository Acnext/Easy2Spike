#include "vidarsimulation.h"
#define M_PI 3.14159265358979323846
static std::default_random_engine generatorI, generatorC, generatorU;
static std::normal_distribution<double> distributionI(10, 2);
static std::normal_distribution<double> distributionU(0, 5);
static std::normal_distribution<double> distributionC(1.0, 0.04);
void SImagetoSpike::setSimulator(int query, int thres, bool keep)
{
	/* 
	 * reset arguments of simulator
	 * in case the initalized ones are not suitable
	 */
	if(query <= 0 || thres <= 0)
	{
		::std::cout << "Bad arguments for the simulator!" << ::std::endl;
		return;
	}
	query_times_perframe = query;
	threshold = thres;
	keepResidual = keep;
}

void SImagetoSpike::resetAccumulator(int width, int height, int channels)
{
	/*
	 * reset the accumulators to fit a new size of image
	 * caution: all value saved will be erased 
	 */
	if(channels != 1 && channels != 3)
	{
		::std::cout << "Error to reset with channels" << channels << ::std::endl;
		return;
	}
	if(width <= 0 || height <= 0)
	{
		::std::cout << "Bad width or height" << width << " " << height << ::std::endl;
		return;
	}
	if(channels == 1)
	{
		accumulatorR.resize(0);
		accumulatorG.resize(0);
		accumulatorB.resize(0);
		accumulator.resize(width * height, 0);
	}
	if(channels == 3)
	{
		accumulatorR.resize(width * height, 0);
		accumulatorG.resize(width * height, 0);
		accumulatorB.resize(width * height, 0);
		accumulator.resize(0);
	}
	accumulateI.resize(width * height, 0);
	thresalpha.resize(width * height, 1);
	thresbiasU.resize(width * height, 0);
	for (int i = 0; i < width * height; i++)
	{
		accumulateI[i] = distributionI(generatorI);
		thresalpha[i] = distributionC(generatorC);
		thresbiasU[i] = distributionU(generatorU);
	}
}

int SImagetoSpike::SimulateSpikeFromImage(SImageData& img, ::std::ofstream& outstream, int factor, int* facmat, int flag_dog)
{
	/* 
	 * simulate spikes from a given image
	 * 1. resize the image
	 * 2. add the value of each pixel (accumulator for channel==1 && accumulatorR,G,B for channel==3)
	 * 3. compare with the 
	 and generate spikes! 
	 */

	//SImageData r_img;
	//ImageResize(img, r_img, width, height);
	if(channels == 1)
	{
		SimulateoneChannel(img, outstream, factor, facmat);
		//printf("asdasdasdasdasd\n");
		return 0;
	}

	else if(channels == 3)
	{
		//printf("zzzzzzzzzzzzz\n");
		SimulatethreeChannel(img, outstream, factor, facmat);
		return 0;
	}

	else
	{
		::std::cout << "Error to simulate image with channels " << channels << ::std::endl
					<< "Please reset the simulator." << ::std::endl;
		return 1;
	}
}
void SImagetoSpike::SimulateoneChannel(SImageData& img, ::std::ofstream& outstream, int factor, int* facmat)
{
	
 	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			int idx = i * height + j;
			for (int ii = i * factor; ii < (i + 1) * factor; ii++)
			{
				for (int jj = j * factor; jj < (j + 1) * factor; jj++)
				{
					SColor  C = img.GetPixel(ii, jj);
					uint8 _gray = C.LumaU8();
					int add_I = Clamp((unsigned int)_gray, 0, 255) * facmat[(ii - factor * i) * factor + (jj - factor * j)];
					//accumulator[idx] += (add_I + accumulateI[idx]);
					accumulator[idx] += Clamp((unsigned int)_gray, 0, 255);
				}
			}
			//accumulator[i * height + j] += add_I;
		}
	}

	for (int k = 0; k < query_times_perframe; k++)
	{
		bit_buffer grayBits;
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i+=8)
			{
				for (int e = 7; e >= 0; e--)
				{
					if(i + e >= width)
						continue;				
					int idx = (i + e) * height + j;
					//if (accumulator[idx] > (int)((threshold + thresbiasU[idx]) * thresalpha[idx]))
					if (accumulator[idx] > threshold)
					{
						grayBits.write_bits(true, 1);
						if (keepResidual)
							accumulator[idx] -= (int)((threshold + thresbiasU[idx]) * thresalpha[idx]);
							//accumulator[idx] -= threshold;
						else
							accumulator[idx] = 0;
					}
					else
						grayBits.write_bits(false, 1);
				}
			}
		}

		for (auto& byte : grayBits.get_bytes())
		{
			outstream << (uint8)byte;
		}
	}
}

void SImagetoSpike::SimulatethreeChannel(SImageData& img, ::std::ofstream& outstream, int factor, int* facmat)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			int idx = i * height + j;
			for (int ii = i * factor; ii < (i + 1) * factor; ii++)
			{
				for (int jj = j * factor; jj < (j + 1) * factor; jj++)
				{
					SColor  C = img.GetPixel(ii, jj);
					accumulatorR[idx] += C.R * facmat[(ii - factor * i) * factor + (jj - factor * j)]; 
					accumulatorG[idx] += C.G * facmat[(ii - factor * i) * factor + (jj - factor * j)]; 
					accumulatorB[idx] += C.B * facmat[(ii - factor * i) * factor + (jj - factor * j)]; 
				}
			}			
			
		}
	}
	for (int k = 0; k < query_times_perframe; k++)
	{
		bit_buffer RedBits;
		bit_buffer GreenBits;
		bit_buffer BlueBits;
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i += 8)
			{
				for (int e = 7; e >= 0; e--)
				{
					if(i + e >= width)
						continue;
					int idx = (i + e) * height + j;
					if (accumulatorR[idx] > threshold)
					{
						RedBits.write_bits(true, 1);
						if (keepResidual) accumulatorR[idx] -= threshold;
						else accumulatorR[idx] = 0;
					}
					else RedBits.write_bits(false, 1);

					if (accumulatorG[idx] > threshold)
					{
						GreenBits.write_bits(true, 1);
						if (keepResidual) accumulatorG[idx] -= threshold;
						else accumulatorG[idx] = 0;
					}
					else GreenBits.write_bits(false, 1);

					if (accumulatorB[idx] > threshold)
					{
						BlueBits.write_bits(true, 1);
						if (keepResidual) accumulatorB[idx] -= threshold;
						else accumulatorB[idx] = 0;
					}
						else BlueBits.write_bits(false, 1);
				}
			}
		}

		//write into bitstream
		for (auto& byte : RedBits.get_bytes())
			outstream << (uint8)byte;
		for (auto& byte : GreenBits.get_bytes())
			outstream << (uint8)byte;
		for (auto& byte : BlueBits.get_bytes())
			outstream << (uint8)byte;
	}
}

bit_buffer::bit_buffer(const size_t size) :	pos_(0), bit_index_(0)
{
	this->buffer_.reserve(size);
}

bit_buffer::~bit_buffer() {}