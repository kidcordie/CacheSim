#pragma once

struct tagNode
{
	unsigned long long int tag = 0;
	int valid = 0;
	int dirty = 0;
	tagNode* next = nullptr;
};
class LRU
{
public:
	LRU(int ind_size, int assoc, int index_bits, int block_offset);
	~LRU();
	bool check_addr(unsigned long long int index, unsigned long long int in_tag, bool write);
	void mov_tagNode(tagNode* current, tagNode* dummy);
	tagNode* makeVictim();
	unsigned long long int vcHit_cnt=0;
	unsigned long long int vc_trans=0;
private:
	void add_tagNode(tagNode* prev);
	int index_size;
	int index_bit_size;
	int bo_size;
	tagNode** lru_array;
	tagNode* vic_dummy;
};
