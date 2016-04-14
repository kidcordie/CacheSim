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
	LRU(int ind_size, int assoc);
	bool check_addr(unsigned long long int index, unsigned long long int in_tag, bool write);
	void mov_tagNode(tagNode* current, tagNode* dummy);
private:
	void add_tagNode(tagNode* prev);
	tagNode** lru_array;
	tagNode* vic_dummy;
};
