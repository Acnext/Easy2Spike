#include<cstdlib> 
#include "getopt.h"
#include<cstring>
#include<iostream>
#include<iomanip>
using std::string;
using std::setw;
using std::cout;
using std::endl;

extern int HEIGHT = 250;
extern int WIDTH = 400;
extern int CHANNELS = 1;//默认通道数
extern bool USEIMAGESIZE = false;
extern int FACTOR = 1;//要设置成1否则会出问题orz
extern int FACMAT[9] = {1, 2, 1, 2, 5, 2, 1, 2, 1};

extern int QUERYTIMES = 1;
extern int THRESHOLD = 350;//默认阈值
extern bool KEEPRESIDUAL = false;//默认每次释放后清空累积

enum filetype{IMG, FORMAT, EMPTY};
extern filetype type = EMPTY;
extern string input_filename = "";
extern string file_format = "";
extern string output_filename = "test.dat";

void show_help();
void parse_command(int argc, char** argv);

void parse_command(int argc, char** argv)
{
	/*
	 * parse command including:
	 * height && width && channels
	 * querytimes && threshold && whether keep residuals
	 *
	 * you can simulate spikes from a single image
	 * or select a folder with a list of images and point the format of the images
	 * maybe a video in the future
	 */
	int c;

	while (1)
	{
		int option_index = 0;
		static struct option long_options[] = {
			{"width", 			required_argument, 0, 'w'},
			{"height", 			required_argument, 0, 'h'},
			{"channels",  		required_argument, 0, 'c'},
			{"querytimes",  	required_argument, 0, 'q'},
			{"threshold",  		required_argument, 0, 't'},
			{"keepresidual",  	required_argument, 0, 'k'},
			{"useimgsize",		no_argument,	   0, 'u'},
			{"help",  			no_argument,	   0, '?'},
			{"input_file",  	required_argument, 0, 'i'},
			{"factor",			required_argument, 0, 'f'},
			{"output_file", 	required_argument, 0, 'o'},
		};

		c = getopt_long(argc, argv, "w:h:c:uq:t:k:i:f:o:?", long_options, &option_index);
		if (c == -1)
			break;
		switch (c)
		{
		case 'w':
			WIDTH = atoi(optarg);
			break;
		case 'h':
			HEIGHT = atoi(optarg);
			break;
		case 'c':
			CHANNELS = atoi(optarg);
			break;
		case 'u':
			USEIMAGESIZE = true;
			break;
		case 'q':
			QUERYTIMES = atoi(optarg);
			break;
		case 't':
			THRESHOLD = atoi(optarg);
			break;
		case 'f':
			FACTOR = atoi(optarg);
			break;
		case 'i':
			file_format = optarg;
			type = FORMAT;
			break;
		case 'o':
			output_filename = optarg;
			break;
		case 'k':
			KEEPRESIDUAL = atoi(optarg);
			break;
		case '?':
			show_help();
			exit(0);
			break;
		default:
			printf("getopt get undefined character code %c\n", c);
			show_help();
			exit(1);
			break;
		}
	}

	if (optind < argc) {
		cout << "not parsed arguments: " << endl;
		while (optind < argc)
			cout << argv[optind++] << endl;
	}
}

void show_help()
{
	/*
	 * help function
	 */

	cout << "Usage of spike simulator: " << endl
		<< "-w or --width:\t\tthe width of the image(s)." << endl
		<< "-h or --height:\t\tthe height of the image(s)." << endl
		<< "-c or --channels:\tthe channels of the image(s)." << endl
		<< "-u or --useimgsize:\tuse the w*h of the images(s)" << endl
		<< "-q or --querytimes:\tthe querytimes of the simulator." << endl
		<< "-t or --threshold:\tthe threshold of the simulator." << endl
		<< "-k or --keepresidual:\twhether to keep residuals in the simulator." << endl
		<< "-i or --input_file:\tinput a single image." << endl
		<< "-f or --factor:\t\tfactors for the pixel." << endl
		<< "-o or --output_file:\tname of output file." << endl
		<< "-? or --help:\t\tthis usage." << endl << endl
		<< "The option -i is exclusive with -f, and it's necessary to select -i or -f as input." << endl
		<< "It's not for other options, they have default arguments." << endl
		<< "If you choose -u for -f, the width and height depend on the first image" << endl;
}