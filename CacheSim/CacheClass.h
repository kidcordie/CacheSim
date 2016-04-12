#pragma once

struct tagNode
{
    unsigned long long int tag;
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

class Cache
{
public:
	Cache(int cs, int bs, int assoc, int ht, int mt);
	int getCacheSize();
	int getBlockSize();
	int getAssociativity();
	int getHitTime();
	int getMissTime();
	~Cache();

protected:
	int cachesize;
	int blocksize;
	int associativity;
	int hittime;
	int misstime;
	int bo_size;
	int index_size;
	unsigned long long int bo_mask;
	unsigned long long int index_mask;
	unsigned long long int tag_mask;
<<<<<<< HEAD
	LRU* cache;
	VictimCache* VC;
=======
	int* cache;
	//VictimCache* VC;
>>>>>>> a7b90ca4329560936280b12ff6ba239aed625f99
};

class L1Cache : public Cache
{
public:
	L1Cache(int cs, int bs, int assoc, int ht, int mt);
	bool parseRequest(char ref, unsigned long long int address, unsigned int bytes);
protected:
	LRU* i_cache;
};

class L2Cache : public Cache
{
public:
	L2Cache(int cs, int bs, int assoc, int ht, int mt, int tt, int bw);
	int getTransferTime();
	int getBusWidth();
	bool parseRequest(unsigned long long int address, unsigned int bytes);
protected:
	int transfertime;
	int buswidth;
};
