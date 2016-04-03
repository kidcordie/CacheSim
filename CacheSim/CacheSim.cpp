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
	int bs = atoi(argv[2]);
	Cache L1 = Cache(cs, bs, 1, 1, 1);
	L2Cache L2 = L2Cache(cs, bs, 1, 1, 1, 1, 1);
	char op;
	unsigned long long int address;
	unsigned int bytesize;
	string input_line;
	string new_string = "";
	unsigned i = 0;
	while (getline(cin, input_line))
	{
		op = input_line[0];
		new_string = "0X";
		//gets address as string
		for (i = 2; i < 14; i++)
		{
			new_string += input_line[i];
		}
		//converts hex address string to unsigned long long int
		address = stoull(new_string, nullptr, 16);
		new_string = "";
		i++;
		//grab bytesize
		do
		{
			new_string += input_line[i];
			i++;
		}while (input_line[i] != '\0' && !isspace(input_line[i]));
		bytesize = stoi(new_string);
		cout << op << " " << hex << address << " " << bytesize << endl;
	}
    return 0;
}
