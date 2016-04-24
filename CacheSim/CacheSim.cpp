// CacheSim.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

int main(int argc, char* argv[])
{
	int bs1 = 32;
	int cs1 = 8192;
	int assoc1 = 1;
	int ht1 = 1;
	int mt1 = 1;
	int bs2 = 64;
	int cs2 = 32768;
	int assoc2 = 1;
	int ht2 = 8;
	int mt2 = 10;
	int tt2 = 10;
	int bw2 = 16;
	int mm_chunk_size = 8;
	if (argc != 2)
	{
		cout << "usage: please enter config file location at commmand line" << endl;
		exit(-1);
	}
	string file_location = argv[1];
	cout << file_location;
	ifstream conf_file(file_location);

	string line;
	if (!conf_file.is_open()) {
		cout << "Config file could not be opened using default values" << endl;
	}
	else {
		while (getline(conf_file, line))
		{
			istringstream conf_line(line);
			string key;
			if (getline(conf_line, key, '='))
			{
				string value;
				if (getline(conf_line, value)) {
					//cout << "setting value: " << key << endl;
					if (key == "L1_block_size")
						bs1 = stoi(value);
					else if (key == "L1_cache_size")
						cs1 = stoi(value);
					else if (key == "L1_assoc")
						assoc1 = stoi(value);
					else if (key == "L1_hit_time")
						ht1 = stoi(value);
					else if (key == "L1_miss_time")
						mt1 = stoi(value);
					else if (key == "L2_block_size")
						bs2 = stoi(value);
					else if (key == "L2_cache_size")
						cs2 = stoi(value);
					else if (key == "L2_assoc")
						assoc2 = stoi(value);
					else if (key == "L2_hit_time")
						ht2 = stoi(value);
					else if (key == "L2_miss_time")
						mt2 = stoi(value);
					else if (key == "L2_transfer_time")
						tt2 = stoi(value);
					else if (key == "L2_bus_width")
						bw2 = stoi(value);
					else if (key == "MM_chunk_size")
						mm_chunk_size = stoi(value);
					else
						cout << "no key found " << key << endl;
				}
			}
		}
	}
	conf_file.close();
	L1Cache* L1 = new L1Cache(cs1, bs1, assoc1, ht1, mt1, mm_chunk_size);
	L2Cache* L2 = new L2Cache(cs2, bs2, assoc2, ht2, mt2, mm_chunk_size, tt2, bw2);
	char op;
	unsigned long long int address;
	unsigned long long int overflow_address;
	int overflow_bytes;
	unsigned int bytesize;
	string input_line;
	string new_string = "";
	unsigned i = 0;
	int L1hits = 0;
	int L2hits = 0;
	int MMaccess = 0;
	while (getline(cin, input_line))
	{
		op = input_line[0];
		new_string = "0X";
		//gets address as string
		i = 2;
		while (!isspace(input_line[i]))
		{
			new_string += input_line[i];
			++i;
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

		if(op == 'I')
		{
		    L1->inst_cnt++;
		}
		if (L1->parseRequest(op, address, bytesize))
		{
			L1hits++;
		}
		else if (L1->vc_hit)
		{
		    //time_count++;
			L1->vc_hit = false;
		}
		else
        {
            if (L1->dirtyKickout) //write request to L2
            {
                L1->dirtyKickout = false;
                L2->dirtyWrite(op, L1->dirtyAddress);
                if (L2->vc_hit)
                    L2->vc_hit = false;
            }
            if (L2->parseRequest(op,address,bytesize))
            {
                L2hits++;
            }
		}
		while (L1->address_overflow)
		{
			L1->address_overflow = false;
			overflow_address = L1->next_address;
			overflow_bytes = L1->next_bytes;
			if (!L1->parseRequest(op, overflow_address, overflow_bytes))
			{
				if (L1->vc_hit)
				{
					L1->vc_hit = false;
				}
				else
				{
					if (L1->dirtyKickout) {
						L1->dirtyKickout = false;
						L2->dirtyWrite(op, L1->dirtyAddress);
					}
					L2->parseRequest(op,overflow_address, overflow_bytes);
				}
			}
		}
	}
	unsigned long long int time_count = L1->wrt_cnt + L2->wrt_cnt + L1->read_cnt + L2->read_cnt + L1->inst_cnt + L2->inst_cnt;
    int single_L1cache_cost = (cs1/4096)*100*(log2f(assoc1)) + 100*(cs1/4096);
    int cache_costL2 = (cs2/16384)*50*(log2f(assoc2)) + 50*(cs2/16384);
    int mem_cost = 75 + 100*(log2f(mm_chunk_size) - 3);

	cout << endl << "L1_i hits: " << dec << L1->i_hitCnt << endl;
	cout << "L1_i misses: " << dec << L1->i_missCnt << endl;
	cout << "L1_i kickouts: " << dec << L1->i_cache->kickouts << endl;
	cout << "L1_i dirty kickouts: " << dec << L1->i_dirty_kickCnt << endl;
	cout << "L1_d hits: " << dec << L1->d_hitCnt << endl;
	cout << "L1_d misses: " << dec << L1->d_missCnt << endl;
	cout << "L1_d kickouts: " << dec << L1->cache->kickouts << endl;
	cout << "L1_d dirty kickouts: " << dec << L1->d_dirty_kickCnt << endl;
	cout << "L1 read refs: " << dec << L1->getReadRefs() << endl;
	cout << "L1 write refs: " << dec << L1->getWriteRefs() << endl;
	cout << "L1 inst refs: " << dec << L1->getInstRefs() << endl;
	cout << "L2 hits: " << dec << L2->hitCnt << endl;
	cout << "L2 misses: " << dec << L2->missCnt << endl;
	cout << "L2 kickouts: " << dec << L2->cache->kickouts << endl;
	cout << "L2 dirty kickouts: " << dec << L2->dirty_kickCnt << endl << endl;

	cout << "Total Time: " << dec << time_count << endl;
	cout << "Read Cycles: " << dec << (L1->read_cnt + L2->read_cnt) << endl;
	cout << "Write Cycles: " << dec << (L1->wrt_cnt + L2->wrt_cnt) << endl;
	cout << "Instruction Cycles: " << dec << (L1->inst_cnt + L2->inst_cnt) << endl << endl;

	cout << "L1i cost: $" << dec << single_L1cache_cost << endl;
	cout << "L2 cost: $" << dec << cache_costL2 << endl;
	cout << "Memory cost: $" << dec << mem_cost << endl;

	delete(L1);
	delete(L2);
    return 0;
}
