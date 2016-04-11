#pragma once

class VictimCache
{
public:
	VictimCache(int bo);
protected:
	int bo_size;
	int tag_size;
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
	int* cache;
	VictimCache* VC;
};

class L1Cache : public Cache
{
public:
	L1Cache(int cs, int bs, int assoc, int ht, int mt);
	bool parseRequest(char ref, unsigned long long int address, unsigned int bytes);
protected:
	int* i_cache;
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
