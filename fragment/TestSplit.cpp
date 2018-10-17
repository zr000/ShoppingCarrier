// TestSplit.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class CRange
{
	int minNum;
	int maxNum;

	struct _s_range* nextRange = NULL;
	struct _s_range* preRange = NULL;

	CRange(int min, int dis):
		minNum(min),
		distance(dis) {

	}
};

int genMetadata(ifstream &fileStream)
{

	return 0;
}

int main(int argc, char** argv)
{
	if (argc != 2) {
		cout << argv[0] << " metaFile.txt" << endl;
		exit(1);
	}

	ifstream ifs(argv[1]);
	
	if (!ifs.is_open()) {
		cout << argv[1] << " not found" << endl;
		exit(1);
	}

	genMetadata(ifs);


    return 0;
}

