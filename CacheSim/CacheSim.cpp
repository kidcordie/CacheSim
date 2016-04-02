// CacheSim.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "usage: please enter cachesize and block size at commmand line" << endl;
		exit(-1);
	}
	int cs = atoi(argv[1]);
	Cache L1 = Cache(cs, 1, 1, 1, 1);
	L2Cache L2 = L2Cache(cs, 1, 1, 1, 1, 1, 1);
	cout << L2.getCacheSize() << endl;
	int wait = 0;
	cin >> wait;
    return 0;
}
