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
	int wait = 0;
	/*
	ifstream myfile;
	myfile.open("C:\\Users\\Alex\\ecen4593-sp16\\traces-short\\tr1");
	string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << endl;
		}
		myfile.close();
	}
	*/
	//while (scanf_s("%c %Lx %d\n",&op, &address, &bytesize) == 3)
	string input_line;
	//ofstream myfile;
	//myfile.open("C:\\Users\\Alex\\ecen4593-sp16\\traces-short\\trlog");
	cout << "Stuck" << endl;
	//%I64u needs to be changed when running in a linux environment
	//cout << scanf("%c %I64u %u\n", &op, &address, &bytesize) << endl;
	/*
	while (scanf("%c %s %u\n", &op, &input_line, &bytesize) == 2) {
		if (input_line.length() < 10)
		{
			break;
		}
		address = stoull(input_line);
		cout << op << " " << address << " " << bytesize << endl;
	}
	*/
	string new_string = "";
	unsigned i = 0;
	while (getline(cin, input_line))
	{
		//cout << "found" << endl;
		op = input_line[0];
		new_string = "";
		for (i = 2; i < 15; i++)
		{
			new_string += input_line[i];
		}
		address = stoull(new_string);
		new_string = "";
		while (!isspace(input_line[i]))
		{
			new_string += input_line[i];
			i++;
		}
		//s to unsigned
		bytesize = stoi(new_string);
		cout << op << " " << address << " " << bytesize << endl;
	}
    return 0;
}
